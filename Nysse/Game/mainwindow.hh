#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "interfaces/iactor.hh"
#include "actoritem.hh"
#include "mainmenu.hh"


#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>

namespace Ui {
class MainWindow;
}

namespace StudentSide {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setSize(int w, int h);
    void setTick(int t);
    int getSeconds();

    virtual void addActor(std::shared_ptr<Interface::IActor> actor, int type);
    void removeActor(std::shared_ptr<Interface::IActor> actor);
    void updateActorCoords(std::shared_ptr<Interface::IActor> actor);
    void setPicture(QImage &img);

    void updateStats(int points, int nysses, int pass);
    void updateBombsLeft(int left);
    void updateGameOverText(QString text);

signals:
    void bomb();
    void moved(char direction);
    void moreBombs();
    void gameEnded();

private slots:
    void menuOptions(int min);

private:

    Ui::MainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;

    std::map<std::shared_ptr<Interface::IActor>, StudentSide::ActorItem*> actors_map_;


    QTimer* game_timer_;
    int seconds_ = 60;

    int width_ = 500; //pxls
    int height_ = 500;
    int tick_ = 500; //ms

    void secondsPassed();
    void keyPressEvent(QKeyEvent* event);


    void dropBomb();

};

}//namespace
#endif // MAINWINDOW_HH
