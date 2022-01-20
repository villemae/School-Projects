#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>


const int PADDING = 10;

namespace StudentSide {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow),
    game_timer_(new QTimer(this)),
    seconds_(0)
{
    ui->setupUi(this);
    ui->gameView->setFixedSize(width_+2, height_+2);
    ui->centralwidget->setFixedSize(width_ + ui->exitButton->width() + 10*PADDING, height_ + PADDING);

    ui->bombLabel->move(width_ + PADDING, 5*PADDING);
    ui->bombAmountLabel->move(width_ + 10*PADDING, 5*PADDING);
    ui->gameTimer->move(width_ + PADDING, 10*PADDING);
    ui->gameTimer->setStyleSheet("background-color: black");
    ui->exitButton->move(width_ + PADDING, height_ - 2*PADDING);
    ui->pointsLabel->move(width_ + PADDING, 15*PADDING);
    ui->pointAmountLabel->move(width_ + 7*PADDING, 15*PADDING);
    ui->nysseLabel->move(width_ + PADDING, 20*PADDING);
    ui->destroyedNyssesLabel->move(width_ + 15*PADDING, 20*PADDING);
    ui->passengerLabel->move(width_ + PADDING, 25*PADDING);
    ui->kPassengersLabel->move(width_ + 15*PADDING, 25*PADDING);
    ui->gameOverLabel->move(width_ + PADDING, 30*PADDING);

    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);
    map->setSceneRect(0,0,width_,height_);

    MainMenu mainMenu(this);
    connect(&mainMenu, &MainMenu::startGame, this, &MainWindow::menuOptions);
    mainMenu.exec();

    resize(minimumSizeHint());
    //ui->gameView->fitInView(0,0, MAPWIDTH, MAPHEIGHT, Qt::KeepAspectRatio);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, map, &QGraphicsScene::advance);
    timer->start(tick_);
        
    connect(game_timer_, &QTimer::timeout, this, &MainWindow::secondsPassed);
    ui->gameTimer->display(seconds_);

    //Statistics p;
    //ui->lcdNumberPoints->display(p.get_points());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSize(int w, int h)
{
    width_ = w;
    height_ = h;
}

void MainWindow::setTick(int t)
{
    tick_ = t;
    
}

void MainWindow::secondsPassed()
{
    --seconds_;
    ui->gameTimer->display(seconds_);
    if (seconds_%10 == 0) {
        emit moreBombs();
    }
    if (seconds_ == 0) {
        game_timer_->stop();
        emit gameEnded();
    }
}

int MainWindow::getSeconds()
{
    return seconds_;
}

void MainWindow::addActor(std::shared_ptr<Interface::IActor> actor, int type)
{
    int locX = actor->giveLocation().giveX();
    int locY = actor->giveLocation().giveY();
    StudentSide::ActorItem* nActor = new StudentSide::ActorItem(locX, locY, type);
    if (type == NYSSE) {
        nActor->setZValue(1);
    }
    if (type == PLAYER) {
        nActor->setZValue(2);
    }
    actors_map_[actor] = nActor;
    map->addItem(nActor);

}

void MainWindow::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    if (actors_map_.find(actor) != actors_map_.end()) {
        map->removeItem(actors_map_.at(actor));
        actors_map_.erase(actor);
    }
}

void MainWindow::updateActorCoords(std::shared_ptr<Interface::IActor> actor)
{
    if (actors_map_.find(actor) != actors_map_.end()) {
        actors_map_.at(actor)->setCoord(actor->giveLocation().giveX(), actor->giveLocation().giveY());

    }
}

void MainWindow::setPicture(QImage &img)
{
    map->setBackgroundBrush(img);
}

void MainWindow::updateStats(int points, int nysses, int pass)
{
    ui->pointAmountLabel->setText(QString::number(points));
    ui->destroyedNyssesLabel->setText((QString::number(nysses)));
    ui->kPassengersLabel->setText(QString::number(pass));
}

void MainWindow::updateBombsLeft(int left)
{
    ui->bombAmountLabel->setText(QString::number(left));
}

void MainWindow::updateGameOverText(QString text)
{
    ui->gameOverLabel->setText(text);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{


    if (event->key() == Qt::Key_A) {
        emit moved('a');
    }

    else if (event->key() == Qt::Key_S) {
        emit moved('s');
    }

    else if (event->key() == Qt::Key_D) {
        emit moved('d');
    }

    else if (event->key() == Qt::Key_W) {
        emit moved('w');
    }

    else if (event->key() == Qt::Key_Space) {
        emit bomb();
    }

}

void MainWindow::menuOptions(int min)
{
    seconds_ = 60*min;

     //toisen pelaajan lisääminen?

    game_timer_->start(1000);
}


}//namespace
