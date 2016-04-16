#ifndef __MEDIUMENEMY_H__
#define __MEDIUMENEMY_H__

#include "boid.h"

class MediumEnemy : public Boid
{
public:
    MediumEnemy(int width, int height);
    virtual void attack();
    virtual void altAttack();

    virtual void update(sf::Time delta = sf::Time::Zero);
};

#endif // __MEDIUMENEMY_H__
