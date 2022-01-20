#include <QDebug>
#include "statistics.hh"
#include "player.hh"


namespace StudentSide {


Statistics::Statistics()
{   

}

void StudentSide::Statistics::morePassengers(int num)
{
    new_passengers_ += num;
}

void Statistics::nysseRemoved()
{
    ++destroyed_nysses_;
    addPoints(10);
}

void Statistics::newNysse()
{
    ++new_nysses_;
    qDebug() << "Nysses:" << new_nysses_;

}

void Statistics::nysseLeft()
{
    ++left_nysses_;
}

void Statistics::addPoints(int pts)
{
    points_ += pts;
    qDebug() << "Current points: " << points_;
}

int Statistics::getPoints()
{
    return points_;
}

void Statistics::passengerKilled()
{
    ++killed_passengers_;
    points_ = points_ - 1;
}

int Statistics::get_newNysses()
{
    return new_nysses_;
}

int Statistics::get_leftNysses()
{
    return left_nysses_;
}

int Statistics::get_destroyedNysses()
{
    return destroyed_nysses_;
}

int Statistics::get_newPassengers()
{
    return new_passengers_;
}

int Statistics::get_killedPassengers()
{
    return killed_passengers_;
}

}
