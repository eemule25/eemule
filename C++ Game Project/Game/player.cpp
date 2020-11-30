#include "player.hh"

namespace StudentSide
{

Player::Player()

{

}

StudentSide::Player::~Player()
{

}

void StudentSide::Player::move(Interface::Location loc)
{
    playerLocation_ = loc;
}

Interface::Location StudentSide::Player::giveLocation() const
{
    return playerLocation_;
    
}

void Player::moveUp(ActorItem *playerItem)
{
    playerItem->setRotation(-90);

    if(playerLocation_.giveY()-MOVING_DISTANCE >= 0) {
        playerLocation_.setXY(playerLocation_.giveX(), playerLocation_.giveY() - MOVING_DISTANCE);
    }
}

void Player::moveRight(ActorItem *playerItem)
{
    playerItem->setRotation(0);

    if(playerLocation_.giveX()+MOVING_DISTANCE <= 985) {
        playerLocation_.setXY(playerLocation_.giveX() + MOVING_DISTANCE, playerLocation_.giveY());
    }
}

void Player::moveDown(ActorItem *playerItem)
{
    playerItem->setRotation(90);

    if(playerLocation_.giveY()+MOVING_DISTANCE <= 485) {
        playerLocation_.setXY(playerLocation_.giveX(), playerLocation_.giveY() + MOVING_DISTANCE);
    }
}

void Player::moveLeft(ActorItem *playerItem)
{
    playerItem->setRotation(180);

    if(playerLocation_.giveX()-MOVING_DISTANCE >= 0) {
        playerLocation_.setXY(playerLocation_.giveX() - MOVING_DISTANCE, playerLocation_.giveY());
    }
}

}
