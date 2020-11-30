#include "statistics.hh"

namespace StudentSide
{

Statistics::Statistics()
{

}

Statistics::~Statistics()
{

}

void Statistics::morePassengers(int num)
{
    Q_ASSERT(num >= 0);
    passengers_ = passengers_ + num;
}

void Statistics::nysseRemoved()
{
    nysses_--;
    nysses_destroyed++;
    playerScore_ = playerScore_ + 100;
}

void Statistics::newNysse()
{
    nysses_++;
}

void Statistics::nysseLeft()
{
    nysses_--;
    nysses_at_final_stop++;
}

void Statistics::passengerRemoved()
{
    passengers_destroyed++;
    playerScore_ = playerScore_ + 50;
}

void Statistics::bombDropped()
{
    if ( bombsLeft > 0){
        bombsLeft--;
    } else {
        bombsLeft = 0;
    }
}

void Statistics::addExtraBomb(int bombs)
{
    bombsLeft = bombsLeft + bombs;
}

int Statistics::giveNyssesRemoved()
{
    return nysses_destroyed;
}

int Statistics::givePassengersRemoved()
{
    return passengers_destroyed;
}

int Statistics::giveNyssesLeft()
{
    return nysses_at_final_stop;
}

int Statistics::giveCurrentNysses()
{
    return nysses_;
}

int Statistics::giveCurrentBombs() const
{
    return bombsLeft;
}

int Statistics::givePlayerScore()
{
    return playerScore_;
}

int Statistics::giveCurrentPassengers()
{
    return passengers_;
}

}
