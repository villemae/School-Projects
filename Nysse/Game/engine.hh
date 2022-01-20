#ifndef ENGINE_HH
#define ENGINE_HH

#include "mainwindow.hh"
#include "city.hh"
#include "core/logic.hh"

#include <QObject>
#include <QDebug>

namespace StudentSide {

class Engine : public QObject
{
    Q_OBJECT
public:
    Engine();
    void createGame();


public slots:
    void dropBomb();
    void movePlayer(char direction);
    void addBombToPlayer();
    void gameOver();

private:
    MainWindow *window_;
    std::shared_ptr<City> city_;
    CourseSide::Logic logic_;
    std::shared_ptr<Player> player_;

    bool game_over_ = false;
};

}//namespace

#endif // ENGINE_HH
