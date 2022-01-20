#include "engine.hh"


namespace StudentSide {

const int STEP = 5;

Engine::Engine()
{
    createGame();
}

void Engine::createGame()
{
    QImage small_map(":/offlinedata/offlinedata/kartta_pieni_500x500.png");
    QImage big_map(":/offlinedata/offlinedata/kartta_iso_1095x592.png");

    window_ = new MainWindow();

    city_ = std::make_shared<City>(window_);
    city_->setBackground(small_map, big_map);
    Interface::Location player_loc;
    player_ = std::make_shared<StudentSide::Player>(player_loc);

    logic_.fileConfig();
    logic_.takeCity(city_);
    logic_.finalizeGameStart();

    window_->addActor(player_, PLAYER);
    window_->show();

    connect(window_, &MainWindow::bomb, this, &Engine::dropBomb);
    connect(window_, &MainWindow::moved, this, &Engine::movePlayer);
    connect(window_, &MainWindow::moreBombs, this, &Engine::addBombToPlayer);
    connect(window_, &MainWindow::gameEnded, this, &Engine::gameOver);
}

void Engine::dropBomb()
{
    if (player_->giveBombs() > 0)
    {
        player_->dropBomb();
        window_->updateBombsLeft(player_->giveBombs());
        std::vector<std::shared_ptr<Interface::IActor>> actors_to_be_destroyed
                = city_->getNearbyActors(player_->giveLocation());
        for (auto actor : actors_to_be_destroyed) {
            city_->destroyActor(actor);
            window_->removeActor(actor);
        }
        qDebug() << "Bomb dropped";
    }
}

void Engine::movePlayer(char direction)
{
    Interface::Location new_loc = player_->giveLocation();

    if (!game_over_) {
        if (direction == 'w' and new_loc.giveY() > 0)
        {
            new_loc.setXY(new_loc.giveX(), new_loc.giveY()-STEP);
        }

        else if (direction == 'a' and new_loc.giveX() > 0)
        {
            new_loc.setXY(new_loc.giveX()-STEP, new_loc.giveY());
        }

        else if (direction == 's' and new_loc.giveY() < 490)
        {
            new_loc.setXY(new_loc.giveX(), new_loc.giveY()+STEP);
        }

        else if (direction == 'd' and new_loc.giveX() < 490)
        {
            new_loc.setXY(new_loc.giveX()+STEP, new_loc.giveY());
        }

        player_->move(new_loc);
        window_->updateActorCoords(player_);
        qDebug() << "Player moved:" << player_->giveLocation().giveX() << player_->giveLocation().giveY();
    }
}

void Engine::addBombToPlayer()
{
    player_->addBomb();
    window_->updateBombsLeft(player_->giveBombs());
}

void Engine::gameOver()
{
    game_over_ = true;
    if (city_->giveStats().getPoints() > 0) {
        window_->updateGameOverText("YOU WON");
    }
    else {
        window_->updateGameOverText("YOU LOSE");
    }
}
}//namespace
