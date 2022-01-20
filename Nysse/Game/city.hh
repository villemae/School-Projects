#ifndef CITY_HH
#define CITY_HH

#include "interfaces/icity.hh"
#include "actors/nysse.hh"
#include "mainwindow.hh"
#include "player.hh"
#include "actors/stop.hh"
#include "statistics.hh"

#include <QMainWindow>
#include <QTime>
#include <vector>

namespace StudentSide {

class City : public Interface::ICity
{
public:
    City(MainWindow* window);
    ~City();
    
    //ICity Interface
    virtual void setBackground(QImage &basicbackground, QImage &bigbackground) override;
    virtual void setClock(QTime clock) override;
    virtual void addStop(std::shared_ptr<Interface::IStop> stop) override;
    virtual void startGame() override;
    virtual void addActor(std::shared_ptr<Interface::IActor> newactor) override;
    virtual void removeActor(std::shared_ptr<Interface::IActor> actor) override;
    virtual void actorRemoved(std::shared_ptr<Interface::IActor> actor) override;
    virtual bool findActor(std::shared_ptr<Interface::IActor> actor) const override;
    virtual void actorMoved(std::shared_ptr<Interface::IActor> actor) override;
    virtual std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const override;
    virtual bool isGameOver() const override;

    void destroyActor(std::shared_ptr<Interface::IActor> actor);
    StudentSide::Statistics &giveStats();

private:
    MainWindow* window_;
    QTime time_;

    QVector<std::shared_ptr<CourseSide::Stop>> stops_;
    QVector<std::shared_ptr<Interface::IActor>> nysses_;
    QVector<std::shared_ptr<Interface::IActor>> passengers_;
    Statistics stats_;

    Statistics statistics_;



};

}

#endif // CITY_HH
