/* Tetris:
 *
 * Desc:
 * This project code includes a tetris game
 * where the user controls various tetrominos on the game board.
 *
 * Program author:
 * Name: Eemil Määttä
 * Student number: 284283
 * UserID: maatta5
 * E-Mail: eemil.maatta@tuni.fi
 * */

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    game_time_(new QTimer),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // We need a graphics scene in which to draw rectangles.
    scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates, but if you want
    // different placement, you can change their values.
    int left_margin = 100; // x coordinate
    int top_margin = 150; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(left_margin, top_margin,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a tetromino is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // Create new grid on scene
    create_grid();

    // Hide unnecessary elements that are not currently needed
    hide_elements();

    // Setting random engine ready for the first real call.
    int seed = time(0); // You can change seed value for testing purposes
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng);
    // Wiping out the first random number (which is almost always 0)
    // After the above settings, you can use randomEng to draw the next falling
    // tetromino by calling: distr(randomEng) in a suitable method.

    // A non-singleshot timer fires every interval (300) milliseconds,
    // which makes rectangle_move function to be called,
    // until the timer is stopped
    timer_.setSingleShot(false);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::tetromino_move);
    connect(game_time_, &QTimer::timeout, this, &MainWindow::update_game_time);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete game_time_;
}


void MainWindow::tetromino_move()
{
    QRectF rect = scene_->sceneRect();
    qreal x = tetromino_.at(3)->x();
    qreal y = tetromino_.at(3)->y();
    y += SQUARE_SIDE;

   if(rect.contains(x, y) and (check_y_direction() == true)) {
        tetromino_.at(0)->moveBy(0, SQUARE_SIDE);
        tetromino_.at(1)->moveBy(0, SQUARE_SIDE);
        tetromino_.at(2)->moveBy(0, SQUARE_SIDE);
        tetromino_.at(3)->moveBy(0, SQUARE_SIDE);
    } else {
       timer_.stop();
       ui->start_button->setDisabled(true);
       if(not tetromino_stopped_) {
            tetromino_stopped_ = true;
            // 2 second delay so tetromino can be move while stop
            QTimer::singleShot(2000, this, SLOT(on_start_button_clicked()));
        }
    }
}


bool MainWindow::check_y_direction()
// Check if it is possible to move square down
{
    for(auto p : played_squares_) {
        for(auto t : tetromino_) {
            if((p->x()==t->x() and p->y() == t->y()+SQUARE_SIDE)) {
                return false;
            }
        }
    }
    return true;
}


bool MainWindow::check_right_direction()
// Check if it is possible to move square to the right
{
    for(auto p : played_squares_) {
        if(tetromino_ == right_corner_tetromino_) {
            if((p->x()-SQUARE_SIDE==tetromino_.at(0)->x() and
                p->y() == tetromino_.at(0)->y())) {
                return false;
            }

        } else if(tetromino_ == square_tetromino_ or
                  tetromino_ == step_up_right_tetromino_) {
            if((p->x()-SQUARE_SIDE==tetromino_.at(1)->x() and
                p->y() == tetromino_.at(1)->y())) {
                return false;
            }
        }
        if((p->x()-SQUARE_SIDE == tetromino_.at(3)->x() and
            p->y() == tetromino_.at(3)->y())) {
            return false;
        }
    }
    return true;
}


bool MainWindow::check_left_direction()
// Check if it is possible to move square to the left
{
    for(auto p : played_squares_) {
        if(tetromino_ == pyramid_tetromino_ or tetromino_ ==
           left_corner_tetromino_ or tetromino_ == right_corner_tetromino_) {
            if((p->x()+SQUARE_SIDE==tetromino_.at(1)->x() and
                p->y() == tetromino_.at(1)->y())) {
                return false;
            }

        } else if(tetromino_ == square_tetromino_ or
                  tetromino_ == step_up_left_tetromino_ or
                  tetromino_ == step_up_right_tetromino_) {
            if((p->x()+SQUARE_SIDE==tetromino_.at(2)->x() and
                p->y() == tetromino_.at(2)->y())) {
                return false;
            }
        }
        if((p->x()+SQUARE_SIDE==tetromino_.at(0)->x() and
            p->y() == tetromino_.at(0)->y())) {
            return false;
        }
    }
    return true;
}


bool MainWindow::check_full_lines()
// Check all played squares if full rows are found
{
    y_line_ = 0;
    int pointer = 0;
    while(y_line_ <= 500) {
        for(auto p_square : played_squares_) {
            if(p_square->y() == y_line_) {
                pointer++;
                if(pointer == 12) {
                    // Full line will be deleted
                    remove_full_line();

                    //  Move the lines down
                    move_lines_down();

                    // Update player's score
                    player_score_ += 100;
                    ui->score_number->display(player_score_);
                    return false;
                    }
                }
            }
    pointer = 0;
    y_line_ += SQUARE_SIDE;
    }
    return true;
}


void MainWindow::remove_full_line()
{
    int length = played_squares_.size();
    for(int i=0; i<length; i++) {
        if(played_squares_.at(i)->y()==y_line_) {
            scene_->removeItem(played_squares_.at(i));
        }
    }
}


void MainWindow::move_lines_down()
{
    std::vector<QGraphicsRectItem*> copy;
    for(auto p_square : played_squares_) {
        if(p_square->y() != y_line_) {
            copy.push_back(p_square);
        }
    }
    for(auto copied_square : copy) {
        if(copied_square->y() < y_line_) {
            copied_square->moveBy(0, SQUARE_SIDE);
        }
    }
    played_squares_ = copy;
}

void MainWindow::tetromino_stop()
{
    // When tetromino stops, the squares will be added to played squares vector
    if(tetromino_.size() != 0) {
        for(auto i : tetromino_) {
             played_squares_.push_back(i);
             player_score_ += 1;
             ui->score_number->display(player_score_);
        }
        if(played_squares_.size() != 0) {
            check_full_lines();
        }
    }
}

void MainWindow::game_end()
{
    // Game ends if the game area runs out
    if(played_squares_.size() != 0) {
        for(auto square : played_squares_) {
            if(square->y() == 0) {
                save_leaderboard();
                game_ended_ = true;
                game_time_->stop();
                ui->pause_button->setDisabled(true);
                ui->the_end_widget->show();
                ui->the_end_text->show();
                break;
            }
        }
    }
}

void MainWindow::change_level_buttons(bool command)
{
    ui->easy_level_button->setDisabled(command);
    ui->normal_level_button->setDisabled(command);
    ui->hard_level_button->setDisabled(command);
}


void MainWindow::place_tetromino(std::vector<QGraphicsRectItem*>
                                 current_tetromino)
{
    // Place tetromino in the middle of the top
    for(auto square : current_tetromino) {
        square->moveBy(4*SQUARE_SIDE, 0);
    }
    tetromino_ = current_tetromino;
}


void MainWindow::update_game_time()
{
    sec_ += 1;
    if(sec_ % 30 == 0) {
        if(min_ < 2) {
            drop_time_ -= 30;
        } else {
            drop_time_ -= 10;
        }
        level_ += 1;
    }
    if(sec_ == 60) {
        min_ += 1;
        sec_ = 0;
    }
    ui->level_display->display(level_);
    ui->lcd_number_min->display(min_);
    ui->lcd_number_sec->display(sec_);
}


void MainWindow::keyPressEvent(QKeyEvent* event)
{
    // moving tetromino to south (down) by SQUARE_SIDE
    if(event->key() == Qt::Key_S and ui->start_button->isEnabled() == false) {
        if(scene_->sceneRect().contains(tetromino_.at(3)->x(),
        tetromino_.at(3)->y() + 2*SQUARE_SIDE) and check_y_direction()==true) {
            tetromino_.at(0)->moveBy(0, SQUARE_SIDE);
            tetromino_.at(1)->moveBy(0, SQUARE_SIDE);
            tetromino_.at(2)->moveBy(0, SQUARE_SIDE);
            tetromino_.at(3)->moveBy(0, SQUARE_SIDE);
        }
        return;
    }

    // moving tetromino to right by SQUARE_SIDE
    if(event->key() == Qt::Key_D and ui->start_button->isEnabled() == false) {
        int right_value = SQUARE_SIDE;
        if(tetromino_ == step_up_right_tetromino_) {
            right_value = 2*SQUARE_SIDE; // So tetromino stay inside game area
        }
        if(scene_->sceneRect().contains(tetromino_.at(3)->x() + right_value,
        tetromino_.at(3)->y()) and check_right_direction() == true) {
            tetromino_.at(0)->moveBy(+SQUARE_SIDE, 0);
            tetromino_.at(1)->moveBy(+SQUARE_SIDE, 0);
            tetromino_.at(2)->moveBy(+SQUARE_SIDE, 0);
            tetromino_.at(3)->moveBy(+SQUARE_SIDE, 0);
        }
        if(tetromino_stopped_ == true) {
            timer_.start(0);
            tetromino_move();
        }
        return;
    }

    // moving tetromino to left by SQUARE_SIDE
    if(event->key() == Qt::Key_A and ui->start_button->isEnabled() == false) {
        int left_value = SQUARE_SIDE;
        if(tetromino_ == step_up_right_tetromino_ or
                tetromino_ == pyramid_tetromino_) {
            left_value = 2*SQUARE_SIDE;
        } else if (tetromino_ == right_corner_tetromino_) {
            left_value = 3*SQUARE_SIDE;
        }
        if(scene_->sceneRect().contains(tetromino_.at(0)->x() - left_value,
        tetromino_.at(3)->y()) and check_left_direction() == true) {
            tetromino_.at(0)->moveBy(-SQUARE_SIDE, 0);
            tetromino_.at(1)->moveBy(-SQUARE_SIDE, 0);
            tetromino_.at(2)->moveBy(-SQUARE_SIDE, 0);
            tetromino_.at(3)->moveBy(-SQUARE_SIDE, 0);
        }
        if(tetromino_stopped_ == true) {
            timer_.start(0);
            tetromino_move();
        }
        return;
    }

    // moving tetromino to down
    if(event->key() == Qt::Key_Space and
            ui->start_button->isEnabled() == false) {
        timer_.start(0);
        return;
    }
}

void MainWindow::horizontal()
{
    horizontal_tetromino_.clear();
    QBrush redBrush(Qt::cyan);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    // Horizontal tetromino
    int x = 0;
    for(int i=1; i<5; i++) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE,
                                  blackPen, redBrush);
        square_->setX(x);
        square_->setY(0);
        horizontal_tetromino_.push_back(square_);
        x += SQUARE_SIDE;
    }
    // Place tetromino in the center and prepare for move.
    place_tetromino(horizontal_tetromino_);
}

void MainWindow::left_corner()
{
    left_corner_tetromino_.clear();
    QBrush redBrush(Qt::blue);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    // Left corner tetromino
    int x = 0;
    square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE,
                              blackPen, redBrush);
    square_->setX(x);
    square_->setY(0);
    left_corner_tetromino_.push_back(square_);
    for(int i=1; i<4; i++) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE,
                                  blackPen, redBrush);
        square_->setX(x);
        square_->setY(SQUARE_SIDE);
        left_corner_tetromino_.push_back(square_);
        x += SQUARE_SIDE;
    }
    place_tetromino(left_corner_tetromino_);
}

void MainWindow::right_corner()
{
    right_corner_tetromino_.clear();
    QBrush redBrush(Qt::darkRed);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    // Right corner tetromino
    int x = 0;
    square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE,
                              blackPen, redBrush);
    square_->setX(2*SQUARE_SIDE);
    square_->setY(0);
    right_corner_tetromino_.push_back(square_);
    for(int i=1; i<4; i++) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE,
                                  blackPen, redBrush);
        square_->setX(x);
        square_->setY(SQUARE_SIDE);
        right_corner_tetromino_.push_back(square_);
        x += SQUARE_SIDE;
    }
    place_tetromino(right_corner_tetromino_);
}

void MainWindow::square()
{
    square_tetromino_.clear();
    QBrush redBrush(Qt::yellow);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    // Square tetromino
    int x = 0;
    for(int i=1; i<3; i++) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE,
                                  blackPen, redBrush);
        square_->setX(x);
        square_->setY(0);
        square_tetromino_.push_back(square_);
        x += SQUARE_SIDE;
    }
    x = 0;
    for(int i=1; i<3; i++) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE,
                                  blackPen, redBrush);
        square_->setX(x);
        square_->setY(SQUARE_SIDE);
        square_tetromino_.push_back(square_);
        x += SQUARE_SIDE;
    }
    place_tetromino(square_tetromino_);
}

void MainWindow::step_up_right()
{
    step_up_right_tetromino_.clear();
    QBrush redBrush(Qt::green);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    // Step-up right tetromino
    int x = SQUARE_SIDE;
    for(int i=1; i<3; i++) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE,
                                  blackPen, redBrush);
        square_->setX(x);
        square_->setY(0);
        step_up_right_tetromino_.push_back(square_);
        x += SQUARE_SIDE;
    }
    x=0;
    for(int i=1; i<3; i++) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE,
                                  blackPen, redBrush);
        square_->setX(x);
        square_->setY(SQUARE_SIDE);
        step_up_right_tetromino_.push_back(square_);
        x += SQUARE_SIDE;
    }
    place_tetromino(step_up_right_tetromino_);
}

void MainWindow::pyramid()
{
    pyramid_tetromino_.clear();
    QBrush redBrush(Qt::magenta);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    // Pyramid tetromino
    int x = 0;
    square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE,
                              blackPen, redBrush);
    square_->setX(SQUARE_SIDE);
    square_->setY(0);
    pyramid_tetromino_.push_back(square_);
    for(int i=1; i<4; i++) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE,
                                  blackPen, redBrush);
        square_->setX(x);
        square_->setY(SQUARE_SIDE);
        pyramid_tetromino_.push_back(square_);
        x += SQUARE_SIDE;
    }
    place_tetromino(pyramid_tetromino_);
}

void MainWindow::step_up_left()
{
    step_up_left_tetromino_.clear();
    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    // Step-up left tetromino
    int x = 0;
    for(int i=1; i<3; i++) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE,
                                  blackPen, redBrush);
        square_->setX(x);
        square_->setY(0);
        step_up_left_tetromino_.push_back(square_);
        x += SQUARE_SIDE;
    }
    x=SQUARE_SIDE;
    for(int i=1; i<3; i++) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE,
                                  blackPen, redBrush);
        square_->setX(x);
        square_->setY(SQUARE_SIDE);
        step_up_left_tetromino_.push_back(square_);
        x += SQUARE_SIDE;
    }
    place_tetromino(step_up_left_tetromino_);
}

void MainWindow::read_leaderboard()
{
    // Read input file (leaderboard file) and set data to text_browser
    QString all_scores = " PLAYED GAMES\n";
    all_scores += "\n PLAYER | SCORE\n";
    std::ifstream read_file("leaderboard");
        std::string row = "";
        std::string name;
        std::string score;
        std::string level;
        while(getline(read_file, row)) {
            std::string delimiter = ":";
            std::string level_delimiter = "-";
            name = row.substr(0, row.find(delimiter));
            int vali = row.find(delimiter) + 1;
            score = row.substr(vali);
            level = row.substr(row.find(level_delimiter)+1);

            all_scores += "\n ";
            all_scores += QString::fromStdString(name);
            all_scores += " | ";
            all_scores += QString::fromStdString(score);
        }
        ui->text_browser->setText(all_scores);
        read_file.close();
}

void MainWindow::save_leaderboard()
{
    // Save player's name and score to leaderboard file
    std::ifstream open_file("leaderboard");
    std::ofstream write_file("leaderboard", std::ios_base::app);
    std::string name = player_name_.toStdString();
    write_file << name << ":" << player_score_ << std::endl;
    open_file.close();
    write_file.close();
}

void MainWindow::hide_elements()
{
    ui->the_end_widget->hide();
    ui->the_end_text->hide();
    ui->pause_button->setDisabled(true);
    ui->text_browser->hide();
    ui->close_push_button->hide();
}

void MainWindow::create_grid()
{
    for (int x=0; x<=240; x+=20) {
        scene_->addLine(x,0,x,480, QPen(Qt::darkGray));
    }
    for (int y=0; y<=480; y+=20) {
        scene_->addLine(0,y,240,y, QPen(Qt::darkGray));
    }
}

void MainWindow::on_start_button_clicked()
{
    on_player_name_button_clicked();
    change_level_buttons(true);
    tetromino_stop();
    game_end();

    if(game_ended_ == false) {
        ui->level_display->display(level_);
        ui->pause_button->setDisabled(false);
        game_time_->start(1000);
        switch(distr(randomEng)) // New tetromino is drawn
        {
            case HORIZONTAL : horizontal(); break;
            case LEFT_CORNER : left_corner(); break;
            case RIGHT_CORNER : right_corner(); break;
            case SQUARE : square(); break;
            case STEP_UP_RIGHT : step_up_right(); break;
            case PYRAMID : pyramid(); break;
            case STEP_UP_LEFT : step_up_left(); break;
        }
        tetromino_stopped_ = false;
        ui->start_button->setDisabled(true);
        timer_.start(drop_time_);
    }
    game_ended_ = false;
}

void MainWindow::on_pause_button_clicked()
{
    if(ui->pause_button->text() == "PAUSE") {
        timer_.stop();
        game_time_->stop();
        ui->pause_button->setText("RESUME");
        ui->pause_button->move(170, 280);
        ui->pause_button->resize(100, 200);
    } else {
        if(game_ended_ == false) {
            timer_.start(drop_time_);
            game_time_->start(1000);
            ui->pause_button->setText("PAUSE");
            ui->pause_button->move(520, 210);
            ui->pause_button->resize(111, 31);
        }
    }
}

void MainWindow::on_reset_button_clicked()
{
    hide_elements();
    change_level_buttons(false);
    scene_->clear();
    played_squares_.clear();
    tetromino_.clear();
    create_grid();

    timer_.stop();
    game_time_->stop();
    min_ = 0;
    sec_ = 0;
    player_score_ = 0;
    level_ = 1;
    drop_time_ = 300;

    ui->score_number->display(player_score_);
    ui->lcd_number_min->display(min_);
    ui->lcd_number_sec->display(sec_);
    ui->level_display->display(0);

    ui->pause_button->setText("PAUSE");
    ui->pause_button->move(520, 210);
    ui->pause_button->resize(111, 31);

    ui->player_name_line_edit->setText("");
    ui->player_name_line_edit->setDisabled(false);
    ui->player_name_button->setDisabled(false);
    ui->start_button->setDisabled(false);
    tetromino_stopped_ = false;
    game_ended_ = true;
}


void MainWindow::on_leaderboard_push_button_clicked()
{
    ui->text_browser->show();
    read_leaderboard();
    ui->close_push_button->show();
}

void MainWindow::on_close_push_button_clicked()
{
    ui->text_browser->hide();
    ui->close_push_button->hide();
}

void MainWindow::on_player_name_line_edit_editingFinished()
{
    player_name_ = ui->player_name_line_edit->text();
}

void MainWindow::on_player_name_button_clicked()
{
    if(ui->player_name_line_edit->text() == "") {
        player_name_ = "Unknown";
    }
        ui->player_name_line_edit->setDisabled(true);
        ui->player_name_button->setDisabled(true);
}

void MainWindow::on_easy_level_button_clicked()
{
    drop_time_ = 600;
    change_level_buttons(true);
}

void MainWindow::on_normal_level_button_clicked()
{
    drop_time_ = 300;
    change_level_buttons(true);
}

void MainWindow::on_hard_level_button_clicked()
{
    drop_time_ = 100;
    change_level_buttons(true);
}
