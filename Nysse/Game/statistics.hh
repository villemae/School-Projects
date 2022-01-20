#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "interfaces/istatistics.hh"
#include "mainwindow.hh"

namespace StudentSide {


class Statistics : public Interface::IStatistics
{
public:
    Statistics();

    //IStatistics Interface
    virtual void morePassengers(int num) override;
    virtual void nysseRemoved() override;
    virtual void newNysse() override;
    virtual void nysseLeft() override;

    void addPoints(int pts);
    int getPoints();

    void passengerKilled();
    int get_newNysses();
    int get_leftNysses();
    int get_destroyedNysses();
    int get_newPassengers();
    int get_killedPassengers();

private:
    int points_ = 0;
    int left_nysses_ = 0;
    int destroyed_nysses_ = 0;
    int new_nysses_ = 0;
    int new_passengers_ = 0;
    int killed_passengers_ = 0;
};

}

#endif // STATISTICS_HH
