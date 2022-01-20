#include "city.hh"
#include "statistics.hh"

#include "actors/nysse.hh"
#include <QDebug>

namespace StudentSide {

City::City(MainWindow* window):
    window_(window)
{

}

City::~City()
{
    
}

void City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    window_->setPicture(basicbackground);
}

void City::setClock(QTime clock)
{
    time_ = clock;
}

void City::addStop(std::shared_ptr<Interface::IStop> stop)
{
    std::shared_ptr<CourseSide::Stop> s = std::dynamic_pointer_cast<CourseSide::Stop>(stop);
    stops_.push_back(s);
}

void City::startGame()
{
}

void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    std::shared_ptr<CourseSide::Passenger> passenger = std::dynamic_pointer_cast<CourseSide::Passenger>(newactor);

    if (passenger != nullptr) {
        passengers_.push_back(newactor);
        window_->addActor(newactor, PASSENGER);
        stats_.morePassengers(1);
        return;
    }

    std::shared_ptr<CourseSide::Nysse> nysse = std::dynamic_pointer_cast<CourseSide::Nysse>(newactor);

    if (nysse != nullptr) {
        nysses_.push_back(newactor);
        window_->addActor(nysse, NYSSE);
        stats_.newNysse();
        return;
    }

    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(newactor);

    if (player != nullptr) {
        window_->addActor(newactor, PLAYER);
    }
}


void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    for (int i = 0; i < nysses_.size(); ++i) {
        if (nysses_.at(i) == actor) {
            nysses_.remove(i);
            actorRemoved(actor);
            return;
        }
    }

    for (int i = 0; i < passengers_.size(); ++i) {

        if (passengers_.at(i) == actor) {
            passengers_.remove(i);
            actorRemoved(actor);
            return;
        }
    }
}

void City::destroyActor(std::shared_ptr<Interface::IActor> actor)
{
    std::shared_ptr<CourseSide::Passenger> passenger = std::dynamic_pointer_cast<CourseSide::Passenger>(actor);
    if (passenger != nullptr) {
        stats_.passengerKilled();
        qDebug() << "Passenger killed";
    }

    std::shared_ptr<CourseSide::Nysse> nysse = std::dynamic_pointer_cast<CourseSide::Nysse>(actor);
    if (nysse != nullptr) {
        stats_.nysseRemoved();
    }
    window_->updateStats(stats_.getPoints(), stats_.get_destroyedNysses(), stats_.get_killedPassengers());
    removeActor(actor);
}

Statistics &City::giveStats()
{
    return stats_;
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
    actor->remove();
    window_->removeActor(actor);



}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    for (int i = 0; i < passengers_.size(); ++i) {
        if (passengers_.at(i) == actor) {
            return true;
        }
    }

    for (int i = 0; i < nysses_.size(); ++i) {
        if (nysses_.at(i) == actor) {
            return true;
        }
    }
    return false;
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    window_->updateActorCoords(actor);
}

std::vector<std::shared_ptr<Interface::IActor> > City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor>> nearby_actors;
    for (auto nysse : nysses_) {
        if (loc.isClose(nysse->giveLocation())) {
            nearby_actors.push_back(nysse);
        }
    }
    for (auto passenger : passengers_) {
        if (loc.isClose(passenger->giveLocation())) {
            nearby_actors.push_back(passenger);
        }
    }
    return nearby_actors;
}

bool City::isGameOver() const
{
    if (window_->getSeconds() == 0) {
        return true;
    }
    else {
        return false;
    }
}

}//namespace
