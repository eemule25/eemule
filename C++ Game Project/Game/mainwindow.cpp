#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>



const int PADDING = 10;

namespace StudentSide {

int const MainWindow::EXIT_CODE_REBOOT = -123456789;
QAction* actionReboot;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gameView->setFixedSize(500, height_);
    ui->centralwidget->setFixedSize(fixedWidth_ + PADDING, height_ + PADDING);
    ui->bombsLeftLcdNumber->display(10);
    ui->shopWidget->hide();

    //Scrollable map
    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);
    map->setSceneRect(0,0,width_,height_);
    resize(minimumSizeHint());
    ui->gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, map, &QGraphicsScene::advance);
    timer->start(tick_);

    // Restart
    actionReboot = new QAction(this);
    actionReboot->setText(tr("Restart"));
    actionReboot->setStatusTip(tr("Restarts the application"));
    connect(actionReboot, SIGNAL(triggered()),this,SLOT(slotReboot()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSize(int w, int h)
{
    width_ = w;
    height_ = h;
}

void MainWindow::setTick(int t)
{
    tick_ = t;
}

void MainWindow::addActor(int locX, int locY, int type)
{
    ActorItem* nActor = new ActorItem(locX, locY, type);
    actors_.push_back(nActor);
    if(type == 1 or type == 2 or type == 3) {
        nActor->setZValue(1); // set the player higher than other actors
        player_ = nActor;
    }
    map->addItem(nActor);
    last_ = nActor;
}

void MainWindow::updateCoords(int nX, int nY)
{
    last_->setCoord(nX, nY);
}

void MainWindow::setPicture(QImage &img)
{
    map->setBackgroundBrush(img);
}

void MainWindow::showClock(QTime clock)
{
    ui->clockLcdNumber->display(clock.toString("hh:mm"));
}

void MainWindow::updateNysseCoords(std::shared_ptr<Interface::IActor> nysse)
{
    for(auto object : nysses_) {
        if(object.first == nysse) {
            object.second->setCoord(nysse->giveLocation().giveX(),
                                    nysse->giveLocation().giveY());
        }
    }
}

void MainWindow::updatePassengerCoords(std::shared_ptr<Interface::IActor> passenger)
{
    for(auto object : passengers_) {
        if(object.first == passenger) {
            object.second->setCoord(passenger->giveLocation().giveX(),
                                    passenger->giveLocation().giveY());
        }
    }
}

void MainWindow::addNysse(int locX, int locY, std::shared_ptr<Interface::IActor> nysse)
{
    ActorItem* nActor = new ActorItem(locX, locY, 50);
    actors_.push_back(nActor);
    if((locX <= width_+20) and (locY <= height_+20)) {
        map->addItem(nActor);
        nysses_.insert({nysse, nActor});
    }
}

void MainWindow::addPassenger(int locX, int locY, std::shared_ptr<Interface::IActor> passenger)
{
    ActorItem* nActor = new ActorItem(locX, locY, 249);
    actors_.push_back(nActor);
    if((locX <= width_+20) and (locY <= height_+20)) {
        map->addItem(nActor);
        passengers_.insert({passenger, nActor});
    }
}

void MainWindow::addBomb(int locX, int locY, std::string type)
{
    if (type == "fire") {
        QTimer *bombTimer = new QTimer(this);
        bombTimer->setSingleShot(true);
        ActorItem* nActor = new ActorItem(locX, locY, 10);
        bombs_.push_back(nActor);
        map->addItem((nActor));

        connect(bombTimer, SIGNAL(timeout()), this, SLOT(removeBomb()));
        bombTimer->start(1000);

    } else if (type == "smoke") {
        ActorItem* nActor = new ActorItem(locX, locY, 15);
        map->addItem((nActor));
    }
}

void MainWindow::removeBomb()
{
    for(auto bomb : bombs_) {
        map->removeItem(bomb);
        addBomb(bomb->x(), bomb->y(), "smoke");
    }
    bombs_.clear();
}

void MainWindow::removeActor(int locX, int locY)
{
    for(auto actor : actors_) {
        if((actor->x() == locX) and (actor->y() == locY)) {
            QVector<QGraphicsItem*>::iterator it = actors_.begin();
                for ( ; it != actors_.end(); ) {
                  if (*it == actor) {
                    it = actors_.erase(it);
                    } else {
                    ++it;
                  }
                }
                map->removeItem(actor);
        }
    }
}

void MainWindow::updateStatistics(int nysses, int passengers, int score)
{
    ui->nyssesDestroyedLcdNumber->display(nysses);
    ui->passengersDestroyedlcdNumber->display(passengers);
    ui->scoreLcdNumber->display(score);
}

void MainWindow::updateNyssesRemoved(int nysses)
{
    ui->nyssesFinalStopLcdNumber->display(nysses);
}

void MainWindow::updateCurrentNysses(int currentNysses)
{
    ui->nyssesInTrafficlcdNumber->display(currentNysses);
}

void MainWindow::updateCurrentBombs(int bombsLeft)
{
    ui->bombsLeftLcdNumber->display(bombsLeft);
    if (bombsLeft == 0){
        ui->bombsLeftLcdNumber->setStyleSheet(QString("background-color: red"));
    }

}

void MainWindow::setLeaderboard(QString scores)
{
    ui->textBrowser->setText(scores);
}

ActorItem *MainWindow::givePlayerActorItem()
{
    return player_;
}

bool MainWindow::findActorInMap(std::string actorName,
                                std::shared_ptr<Interface::IActor> actor)
{
    if (actorName == "nysses") {
        auto it = nysses_.find(actor);
        if(it == nysses_.end()) {
            return false;
        }
    } else if (actorName == "passengers") {
        auto it = passengers_.find(actor);
        if(it == passengers_.end()) {
            return false;
        }
    }
    return true;
}

void MainWindow::spotViewToPlayer()
{
    ui->gameView->fitInView(last_, Qt::IgnoreAspectRatio);
    QMatrix matrix;
    matrix.scale(2,2);
    ui->gameView->setMatrix(matrix);
}

int MainWindow::getExtraBombs()
{
    return extraBombs_;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W) {
        emit buttonPressed('w');
    } else if (event->key() == Qt::Key_D) {
        emit buttonPressed('d');
    } else if (event->key() == Qt::Key_S) {
        emit buttonPressed('s');
    } else if (event->key() == Qt::Key_A) {
        emit buttonPressed('a');
    } else if (event->key() == Qt::Key_Shift) {
        emit buttonPressed('g');
    }
}

}


void StudentSide::MainWindow::on_exitPushButton_clicked()
{
    this->close();
}

void StudentSide::MainWindow::on_restartPushButton_clicked()
{
    actionReboot->trigger();
}


void StudentSide::MainWindow::slotReboot()
{
    qDebug() << "Performing application reboot...";
    qApp->exit(MainWindow::EXIT_CODE_REBOOT);
}

void StudentSide::MainWindow::on_extraBombPushButton_clicked()
{
    extraBombs_++;
    ui->extraBombPushButton->setDisabled(true);
}

void StudentSide::MainWindow::on_shopClosePushButton_clicked()
{
    extraBombs_ = 0;
}
