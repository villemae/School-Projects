#ifndef PLAYER_HH
#define PLAYER_HH

#include "interfaces/iactor.hh"
#include "interfaces/icity.hh"
#include "core/location.hh"

namespace StudentSide {

class Player : public Interface::IActor
{
public:
    Player(Interface::Location& loc);

    //IActor Interface
    virtual Interface::Location giveLocation() const override;
    virtual void move(Interface::Location loc) override;
    virtual bool isRemoved() const override;
    virtual void remove() override;

    int giveBombs();
    void addBomb();
    void dropBomb();

private:
    std::shared_ptr<Interface::ICity> city_;
    Interface::Location location_;
    int bombs_ = 5;
    bool removed_ = false;
};

}//namespace

#endif // PLAYER_HH
