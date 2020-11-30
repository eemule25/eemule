#ifndef CITY_HH
#define CITY_HH

#include "interfaces/icity.hh"
#include "actors/nysse.hh"
#include "actors/passenger.hh"
#include "actors/stop.hh"
#include "actor.hh"
#include "mainwindow.hh"
#include "player.hh"
#include "statistics.hh"

#include <QString>
#include <QTime>
#include <QMainWindow>


namespace StudentSide
{

class City : public Interface::ICity
{
public:
    City(StudentSide::MainWindow* window);
    ~City();

    //CityIF
    virtual void setBackground(QImage &basicbackground, QImage &bigbackground) override;
    virtual void setClock(QTime clock) override;
    virtual void addStop(std::shared_ptr<Interface::IStop> stop) override;
    virtual void startGame() override;
    virtual void addActor(std::shared_ptr<Interface::IActor> newactor) override;
    virtual void removeActor(std::shared_ptr<Interface::IActor> actor) override;
    virtual void actorMoved(std::shared_ptr<Interface::IActor> actor) override;
    virtual void actorRemoved(std::shared_ptr<Interface::IActor> actor) override;
    virtual bool findActor(std::shared_ptr<Interface::IActor> actor) const override;
    virtual std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const override;
    virtual bool isGameOver() const override;

    /**
     * @brief Adds a bomb to the map
     * @param locX, x-coordinate of a bomb
     * @param loxY, y-coordinate of a bomb
     * @param loc, location of player object
     */
    void addBomb(int locX, int locY, Interface::Location loc);

    /**
     * @brief Check Actors (Nysses, Passengers) at coordinates of player
     * @param loc, location of player object
     */
    void checkNearbyActors(Interface::Location loc);

    /**
     * @brief Set type of the player
     * @param x, int from the aircraft icon of dialog.
     */
    void selectPlayerType(int x);
    int playerScore();

private:
    StudentSide::MainWindow* window_;
    StudentSide::Statistics statistics_;
    QVector<std::shared_ptr<Interface::IActor>> actors_;
    QVector<std::shared_ptr<Interface::IStop>> stops_;
    QVector<std::shared_ptr<Interface::IActor>> buses_;
    QVector<std::shared_ptr<Interface::IActor>> passengers_;
    QVector<std::shared_ptr<Interface::IActor>> players_;
    QTime time_;

    int playerType_;
    bool allExtraBombsUsed = false;

};

}

#endif // CITY_HH
