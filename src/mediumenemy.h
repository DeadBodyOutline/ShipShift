#ifndef __MEDIUMENEMY_H__
#define __MEDIUMENEMY_H__

#include "ship.h"

class MediumEnemy : public Ship
{
public:
    MediumEnemy(int width, int height);
    virtual void attack();
    virtual void altAttack();

    virtual void update(sf::Time delta = sf::Time::Zero);
};

#endif // __MEDIUMENEMY_H__
