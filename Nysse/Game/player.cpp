#include "player.hh"

namespace StudentSide {

Player::Player(Interface::Location& loc): location_(loc)
{
    
}

Interface::Location Player::giveLocation() const
{
    return location_;
}

void Player::move(Interface::Location loc)
{
    location_ = loc;
}

bool Player::isRemoved() const
{
    return removed_;
}

void Player::remove()
{
    removed_ = true;
}

int Player::giveBombs()
{
    return bombs_;
}

void Player::addBomb()
{
    ++bombs_;
}

void Player::dropBomb()
{
    --bombs_;
}


}//namespace
