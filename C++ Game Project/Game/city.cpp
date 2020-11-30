#include "interfaces/icity.hh"
#include "city.hh"

namespace StudentSide
{

City::City(StudentSide::MainWindow* window):
    window_(window)
{

}

City::~City()
{
    
}

void City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    window_->setPicture(bigbackground);
}

void City::setClock(QTime clock)
{
    time_ = clock;
    window_->showClock(clock);
}

void City::addStop(std::shared_ptr<Interface::IStop> stop)
{
    std::shared_ptr<CourseSide::Stop> stop1  =
            std::dynamic_pointer_cast<CourseSide::Stop>(stop);

    if ( stop1 != 0){
        stops_.push_back(stop);
    }
}

void City::startGame()
{

   for(auto stop : stops_) {
        window_->addActor(stop->getLocation().giveX(),
                          stop->getLocation().giveY(),125);
    }
    for(auto bus : buses_) {
        window_->addNysse(bus->giveLocation().giveX(),
                          bus->giveLocation().giveY(),bus);
    }

    for (auto passenger : passengers_){
        window_->addPassenger(passenger->giveLocation().giveX(),
                              passenger->giveLocation().giveY(),passenger);
    }

    for (auto player : players_){
      window_->addActor(player->giveLocation().giveX(),
                        player->giveLocation().giveY(),playerType_);

    }
}

void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    std::shared_ptr<CourseSide::Nysse> nysse  =
            std::dynamic_pointer_cast<CourseSide::Nysse>(newactor);

    if (nysse != 0){
        actors_.push_back(newactor);
        buses_.push_back(newactor);
        statistics_.newNysse();
        window_->updateCurrentNysses(statistics_.giveCurrentNysses());

    }
    std::shared_ptr<CourseSide::Passenger> passenger  =
            std::dynamic_pointer_cast<CourseSide::Passenger>(newactor);

    if (passenger != 0){
        actors_.push_back(newactor);
        passengers_.push_back(newactor);
        statistics_.morePassengers(1);
    }

    std::shared_ptr<StudentSide::Player> player  =
            std::dynamic_pointer_cast<StudentSide::Player>(newactor);

    if (player != 0){
        players_.push_back(newactor);
    }
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    QVector<std::shared_ptr<Interface::IActor>>::iterator it = actors_.begin();
        for ( ; it != actors_.end(); ) {
          if (*it == actor) {
            it = actors_.erase(it);
            std::shared_ptr<CourseSide::Nysse> nysse  =
                    std::dynamic_pointer_cast<CourseSide::Nysse>(*it);
            if(nysse != 0) {
                statistics_.nysseLeft(); // Nysse arrived at the final stop
                window_->updateNyssesRemoved(statistics_.giveNyssesLeft());
            }
            actor->remove();
            } else {
            ++it;

          }
        }
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    std::shared_ptr<CourseSide::Nysse> nysse  = std::dynamic_pointer_cast<CourseSide::Nysse>(actor);
    if (nysse != 0 and (nysse->giveLocation().giveX() <= 1020) and (nysse->giveLocation().giveY() <= 520) and
            (nysse->giveLocation().giveX() >= -20) and (nysse->giveLocation().giveY() >= -20)) {

        if(window_->findActorInMap("nysses", actor) == false) {
            window_->addNysse(actor->giveLocation().giveX(),actor->giveLocation().giveY(),actor);
        } // Nysse moves in the map and it is added to nysses_ - vector of mainwindow, if it is not included there

        window_->updateNysseCoords(actor);
    }


    if(allExtraBombsUsed == false) {
        int extraBombs = window_->getExtraBombs();
        if(extraBombs != 0) {
        statistics_.addExtraBomb(extraBombs);
        window_->updateCurrentBombs(statistics_.giveCurrentBombs());
        allExtraBombsUsed = true;
        }
    }
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
    actor->isRemoved();
}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    if ( std::find(actors_.begin(), actors_.end(), actor) != actors_.end() )
           return true;
        else
           return false;

}

std::vector<std::shared_ptr<Interface::IActor> > City::getNearbyActors(Interface::Location loc) const
{
    // Toteutettiin oma funktio tarpeisiimme sopivammaksi
}

bool City::isGameOver() const
{
    if((statistics_.giveCurrentBombs() == 0) or (playerType_ == 0)) {
        return true;
    } else {
        return false;
    }
}

void City::addBomb(int locX, int locY, Interface::Location loc)
{
    if(isGameOver() == false) {
        window_->addBomb(locX, locY, "fire");
        checkNearbyActors(loc);
        statistics_.bombDropped();
        window_->updateCurrentBombs(statistics_.giveCurrentBombs());
    }
}


void City::checkNearbyActors(Interface::Location loc) {
    QVector<std::shared_ptr<Interface::IActor>>::iterator it = actors_.begin();
        for ( ; it != actors_.end(); ) {
            int actorLocX = it->get()->giveLocation().giveX();
            int actorLocY = it->get()->giveLocation().giveY();
          if (it->get()->giveLocation().isClose(loc) == true) {
            window_->removeActor(actorLocX, actorLocY);
            std::shared_ptr<CourseSide::Nysse> nysse  =
                    std::dynamic_pointer_cast<CourseSide::Nysse>(*it);
            if(nysse != 0) {
                statistics_.nysseRemoved(); // Nysse destroyed by player
            }
            std::shared_ptr<CourseSide::Passenger> passenger  =
                    std::dynamic_pointer_cast<CourseSide::Passenger>(*it);
            if(passenger != 0) {
                statistics_.passengerRemoved(); // Passenger killed
            }
            it = actors_.erase(it);
            } else {
            ++it;
          }
        }
        window_->updateStatistics(statistics_.giveNyssesRemoved(), statistics_.givePassengersRemoved(), statistics_.givePlayerScore());
        window_->updateCurrentNysses(statistics_.giveCurrentNysses());
}

void City::selectPlayerType(int x)
{
    playerType_ = x;
}


int City::playerScore()
{
    return statistics_.givePlayerScore();
}

}
