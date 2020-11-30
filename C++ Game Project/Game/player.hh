#ifndef PLAYER_HH
#define PLAYER_HH
#include "core/location.hh"
#include "interfaces/icity.hh"
#include "actor.hh"
#include "city.hh"

#include <QTime>
#include <memory>
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>

#include <QGraphicsItemAnimation>
#include <QTimeLine>

namespace StudentSide
{
/**
 * @brief Player class is responsible of moving the player to the given direction
 */
class Player : public StudentSide::Actor
{

public:
    Player();
    ~Player();

    void move(Interface::Location loc) override;
    Interface::Location giveLocation() const override;

    /**
     * @brief following four methods rotates and moves player to given direction
     * @param playerItem, pointer to player that is controlled
     */
    void moveUp(ActorItem *playerItem);
    void moveRight(ActorItem *playerItem);
    void moveDown(ActorItem *playerItem);
    void moveLeft(ActorItem *playerItem);

private:
    Interface::Location playerLocation_;
    std::shared_ptr <Interface::IActor> player;

    int MOVING_DISTANCE = 10;
};
}

#endif // PLAYER_HH
