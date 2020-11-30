#ifndef ACTOR_HH
#define ACTOR_HH
#include "core/location.hh"
#include "interfaces/iactor.hh"
#include "errors/gameerror.hh"

#include <memory>



namespace StudentSide
{

class Actor : public Interface::IActor
{
public:
    Actor();
    virtual ~Actor();

    //ActorIF
    virtual Interface::Location giveLocation() const override;
    virtual void move(Interface::Location loc) override;
    virtual bool isRemoved() const override;
    virtual void remove() override;

    bool isMoved();


private:
    Interface::Location location_;
    bool isMoved_ = false;
    bool isRemoved_ = false;
    std::string name_;

};

}

#endif // ACTOR_HH
