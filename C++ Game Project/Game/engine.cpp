#include "engine.hh"



namespace StudentSide
{

Engine::Engine()

{
    connect(window_, &StudentSide::MainWindow::buttonPressed,
            this, &Engine::movePlayer);
    createGame();
}


void Engine::movePlayer(char button)
{
    ActorItem *playerItem = window_->givePlayerActorItem();
    playerItem->setTransformOriginPoint(7.5,7.5);
    window_->spotViewToPlayer();

    if(city->isGameOver() == false) {
        if(button == 'w') {
            player_->moveUp(playerItem);
        } else if (button == 'd') {
            player_->moveRight(playerItem);
        } else if (button == 's') {
            player_->moveDown(playerItem);
        } else if (button == 'a') {
            player_->moveLeft(playerItem);
        } else if (button == 'g') {
            city->addBomb(player_->giveLocation().giveX(),
                          player_->giveLocation().giveY(), player_->giveLocation());
            if(city->isGameOver() == true) {
                saveLeaderboard();
            }
        }

        window_->updateCoords(player_->giveLocation().giveX(),
                              player_->giveLocation().giveY());
    }
}


void Engine::start()
{
    city->startGame();

}

void Engine::setName(QString name)
{
    playerName_ = name;
}

void Engine::setPlayerIcon(int x)
{
    playerIcon_ = x;
    city->selectPlayerType(x);
}

void Engine::createGame()
{
    initCity();

    Dialog *dialog  = new Dialog (window_);
    connect(dialog, &Dialog::playerIconValue,
            this, &StudentSide::Engine::setPlayerIcon);
    connect(dialog, &Dialog::setNamePbtnClicked,
            this, &StudentSide::Engine::setName);

    initPlayer();
    dialog->exec();

    if(playerIcon_ == 0) {
        city->selectPlayerType(0);
    } else {
        window_->show();
    }

    readLeaderboard();
    showTopScores();

    logic.finalizeGameStart();
    window_->spotViewToPlayer();
}

void Engine::initCity()
{
    QImage BASIC_BACKGROUND =
            QImage( ":/offlinedata/offlinedata/kartta_pieni_500x500.png");
    QImage BIG_BACKGROUND  =
            QImage(":/offlinedata/offlinedata/kartta_iso_1095x592.png");


    city = std::make_shared<StudentSide::City>(window_);
    city->setBackground(BASIC_BACKGROUND,BIG_BACKGROUND);
    logic.fileConfig();
    logic.takeCity(city);

}

void Engine::initPlayer()
{
    player_ = std::make_shared<StudentSide::Player>();
    Interface::Location loc;
    loc.setXY(PLAYER_X_COORD, PLAYER_Y_COORD);
    player_->move(loc);
    city->addActor(player_);
}

void Engine::readLeaderboard()
{
    // Read input file (leaderboard file) and set data to text_browser
    std::ifstream read_file("leaderboard");
        std::string row = "";
        std::string name = playerName_.toStdString();
        std::string score;
        std::string level;
        while(getline(read_file, row)) {
            std::string delimiter = ":";
            name = row.substr(0, row.find(delimiter));
            int point = row.find(delimiter) + 1;
            score = row.substr(point);
            
            Highscore highscore;
            highscore.name = name;
            highscore.score = std::stoi(score);

            highscores_.push_back(highscore);
            scores_.push_back(std::stoi(score));
            std::sort(scores_.rbegin(), scores_.rend());
        }
        read_file.close();
}

void Engine::showTopScores()
{
    // Show highscores in mainwindow
    QString all_scores = "PLAYER | SCORE\n";
    std::string score;
    std::string name;
    int length;
    if(scores_.size() <= 10) {
        length = scores_.size();
    } else {
        length = 10;
    }
    for(int i=0; i<length; i++) {
        score = std::to_string(scores_[i]);

        for(auto player : highscores_) {
            if(score == std::to_string(player.score)) {
                name = player.name;
            }
        }
        all_scores += "\n" + QString::fromStdString(std::to_string(i+1)) + ". ";
        all_scores += QString::fromStdString(name);
        all_scores += " | ";
        all_scores += QString::fromStdString(score);
    }
    window_->setLeaderboard(all_scores);
}

void Engine::saveLeaderboard()
{
    // Save player's name and score to leaderboard file
    std::ifstream open_file("leaderboard");
    std::ofstream write_file("leaderboard", std::ios_base::app);
    std::string name = playerName_.toStdString();
    write_file << name << ":" << city->playerScore() << std::endl;
    open_file.close();
    write_file.close();

    highscores_.clear();
    scores_.clear();
    readLeaderboard();
    showTopScores();
}

}

