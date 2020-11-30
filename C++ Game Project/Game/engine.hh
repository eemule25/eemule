#ifndef ENGINE_HH
#define ENGINE_HH

#include "../Course/CourseLib/core/logic.hh"
#include "core/location.hh"
#include "core/logic.hh"
#include "mainwindow.hh"
#include "dialog.hh"
#include "city.hh"
#include "player.hh"
#include "qapplication.h"

#include <QWidget>
#include <QObject>
#include <QImage>
#include <QMainWindow>
#include <QDialog>
#include <QTime>


namespace StudentSide

{

/**
 * @brief Engine runs the gamelogic
 * Dialog object and pointers to city and player are created in this class
 */
class Engine : public QObject
{
     Q_OBJECT

public:
    Engine();
    StudentSide::MainWindow* window_ = new StudentSide::MainWindow();
    //static const int EXIT_CODE_REBOOT;

public slots:
    void movePlayer(char button);


private slots:
    void start();
    void setPlayerIcon(int x);
    void setName(QString name);

signals:
    void exited();

private:

    /**
     * @brief Create pointer to city and start game logic.
     * Create Dialog objects, and set pointers to player and city
     *
     */
    void createGame();

    /**
     * @brief Initialize pointer to city
     */
    void initCity();

    /**
     * @brief Initialize pointer to player and set it to city
     */
    void initPlayer();


    /**
     * @brief Read file where scores are stored in form "name:score"
     * and set scores to top-10 form.
     */
    void readLeaderboard();

    /**
     * @brief Shwow scores in mainwindow
     */
    void showTopScores();

    /**
     * @brief Scores and names are saved to file
     */
    void saveLeaderboard();    

    CourseSide::Logic logic;
    std::shared_ptr<StudentSide::City> city;
    std::shared_ptr<StudentSide::ActorItem> actorItem;
    std::shared_ptr<StudentSide::Player> player_;
    QString playerName_;
    
    int PLAYER_X_COORD = 0;
    int PLAYER_Y_COORD = 0;
    int playerIcon_ = 0;

    struct Highscore{
       std::string name;
       int score;
    };

    std::vector<Highscore> highscores_;
    std::vector<int> scores_;



};

}

#endif // ENGINE_HH
