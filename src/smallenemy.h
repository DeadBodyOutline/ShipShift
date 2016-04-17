#ifndef __SMALLENEMY_H__
#define __SMALLENEMY_H__

#include "boid.h"

class SmallEnemy : public Boid
{
public:
    SmallEnemy(int width, int height);
    virtual void attack();
    virtual void altAttack();

    virtual void update(sf::Time delta = sf::Time::Zero);
};

#endif // __SMALLENEMY_H__
