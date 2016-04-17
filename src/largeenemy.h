#ifndef __LARGEENEMY_H__
#define __LARGEENEMY_H__

#include <SFML/Graphics.hpp>

#include "boid.h"
#include "player.h"

class LargeEnemy : public Boid
{
public:
    LargeEnemy(int width, int height);
    virtual void attack();
    virtual void altAttack();

    virtual void update(sf::Time delta = sf::Time::Zero);
};

#endif // __LARGEENEMY_H__
