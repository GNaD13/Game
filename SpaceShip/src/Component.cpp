#include "Component.hpp"
#include "Actor.hpp"

Component::Component(Actor* owner, int updateOrder)
    :   mOwner(owner),
        mUpdateOrder(mUpdateOrder)
{

}

Component::~Component()
{
    mOwner->RemoveComponents(this);
}