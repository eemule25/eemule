#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "interfaces/iactor.hh"
#include "actoritem.hh"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>
#include <QTime>
#include <map>
#include <QKeyEvent>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <fstream>
#include <QAction>



namespace Ui {
class MainWindow;
}

namespace StudentSide {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

    virtual void addActor(int locX, int locY, int type = 0);


    /**
     * @brief Sets size of the width_ and height_ of given values
     * @param w
     * @param h
     */
    void setSize(int w, int h);

    /**
     * @brief Sets t to the tick_ -variable
     * @param t
     */
    void setTick(int t);



    /**
     * @brief Updates coordinates of the actor in the mainwindow
     * @param nX
     * @param nY
     */
    void updateCoords(int nX, int nY);

    /**
     * @brief Set picture of the map in the mainwindow
     * @param img
     */
    void setPicture(QImage &img);

    /**
     * @brief Shows time in form "hh:mm" in the mainwindow
     * @param time
     */
    void showClock(QTime time);

    /**
     * @brief Updates nysses coordinates
     * @param nysse, pointer of the nysse in the map
     */
    void updateNysseCoords(std::shared_ptr<Interface::IActor> nysse);

    /**
     * @brief Updates passengers coordinates
     * @param passenger, pointer of the passenger in the map
     */
    void updatePassengerCoords(std::shared_ptr<Interface::IActor> passenger);

    /**
     * @brief Add nysse to the given coordinates
     * @param locX
     * @param locY
     * @param nysse, pointer of the nysse in the map
     */
    void addNysse(int locX, int locY, std::shared_ptr<Interface::IActor> nysse);

    /**
     * @brief Add passenger to the given coordinates
     * @param locX
     * @param locY
     * @param passenger, pointer of the passenger in the map
     */
    void addPassenger(int locX, int locY, std::shared_ptr<Interface::IActor> passenger);

    /**
     * @brief Add bombs and smokes of the bomb to the given coordinates
     * @param locX
     * @param locY
     * @param type,
     */
    void addBomb(int locX, int locY, std::string type);

    /**
     * @brief Erase actors from the vector after comparing
     * whether coordinates of the actor are same as the params
     * @param locX
     * @param locY
     */
    void removeActor(int locX, int locY);

    /**
     * @brief Sets number of nysses, passengers and scores to mainwindow
     * @param nysses
     * @param passengers
     * @param scores
     */
    void updateStatistics(int nysses, int passengers, int scores);

    /**
     * @brief Sets number of nysses that are final stop to mainwindow
     * @param nysses
     */
    void updateNyssesRemoved(int nysses);

    /**
     * @brief Sets number of nysses in the map to mainwindow
     * @param currentNysses
     */
    void updateCurrentNysses(int currentNysses);

    /**
     * @brief Sets number of bombs to mainwindow
     * @param bombsLeft
     */
    void updateCurrentBombs(int bombsLeft);

    /**
     * @brief Sets scores to mainwindow top-10 board
     * @param scores, that are set to the board
     */
    void setLeaderboard(QString scores);

    ActorItem* givePlayerActorItem();

    /**
     * @brief Checks from the map whether the actor with actorName is included
     * @param actorName, a keyvalue of the map
     * @param actor, pointer of the actor in the map
     * @return false, if actor is not found from the vector, true
     */
    bool findActorInMap(std::string actorName, std::shared_ptr<Interface::IActor> actor);

    void spotViewToPlayer();
    static const int EXIT_CODE_REBOOT;
    int getExtraBombs();


public slots:
    void keyPressEvent(QKeyEvent* event) override;
    void removeBomb();
    void on_exitPushButton_clicked();

signals:
    void gameStarted();
    void buttonPressed(char button);

private slots:
    void on_restartPushButton_clicked();
    void slotReboot();

    void on_extraBombPushButton_clicked();

    void on_shopClosePushButton_clicked();

private:
    QDialog *dialog;
    Ui::MainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    QVector<QGraphicsItem*> actors_;
    ActorItem* last_;

    ActorItem* player_;

    int width_ = 1000; //pxls
    int height_ = 500;
    int tick_ = 500; //ms
    const int fixedWidth_ = 800;
    int extraBombs_ = 0;

    std::map<std::shared_ptr<Interface::IActor>,ActorItem*> nysses_;
    std::map<std::shared_ptr<Interface::IActor>,ActorItem*> passengers_;
    QVector<QGraphicsItem*> bombs_;

};
}

#endif // MAINWINDOW_HH
