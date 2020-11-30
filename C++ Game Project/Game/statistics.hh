#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "interfaces/istatistics.hh"
#include "mainwindow.hh"

#include <QString>
#include <cassert>

namespace StudentSide
{


class Statistics : public Interface::IStatistics
{

    // IStatistics interface
public:
    Statistics();
    ~Statistics();

    virtual void morePassengers(int num) override;
    virtual void nysseRemoved() override;
    virtual void newNysse() override;
    virtual void nysseLeft() override;

    /**
     * @brief Gives points from removed passengers
     */
    void passengerRemoved();

    /**
     * @brief Reduces number of bombs from the use
     */
    void bombDropped();
    void addExtraBomb(int bomb);


    int giveNyssesRemoved();
    int givePassengersRemoved();
    int giveNyssesLeft();
    int giveCurrentNysses();
    int giveCurrentBombs() const;
    int givePlayerScore();
    int giveCurrentPassengers();

private:
    int nysses_ = 0;
    int nysses_destroyed = 0;
    int passengers_destroyed = 0;
    int nysses_at_final_stop = 0;
    int passengers_ = 0;
    int bombsLeft = 10;
    int playerScore_ = 0;
};

}

#endif // STATISTICS_HH
