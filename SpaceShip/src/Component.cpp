#include "Component.hpp"
#include "Actor.hpp"

Component::Component(Actor* owner, int updateOrder)
    :   mOwner(owner),
        mUpdateOrder(mUpdateOrder)
{
    mOwner->AddComponents(this);
}

Component::~Component()
{
    mOwner->RemoveComponents(this);
}