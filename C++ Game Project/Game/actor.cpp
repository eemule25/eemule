#include "actor.hh"


namespace StudentSide
{

Actor::Actor()
{

}

Actor::~Actor()
{

}

Interface::Location Actor::giveLocation() const
{
    if(isRemoved_ == true) {
        throw Interface::GameError("Actor wasn't given a location");
    }
    return location_;

}

void Actor::move(Interface::Location loc)
{
    location_ = loc;
}

bool Actor::isRemoved() const
{
    return isRemoved_;
}

void Actor::remove()
{
    isRemoved_ = true;
}

bool Actor::isMoved()
{
    return isMoved_;
}

}

