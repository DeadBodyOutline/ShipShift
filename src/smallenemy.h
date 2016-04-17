#ifndef __SMALLENEMY_H__
#define __SMALLENEMY_H__

#include <SFML/Graphics.hpp>

#include "boid.h"
#include "player.h"

class SmallEnemy : public Boid
{
public:
    SmallEnemy(int width, int height);
    virtual void attack();
    virtual void altAttack();

    virtual void update(sf::Time delta = sf::Time::Zero);
protected:
    Player *m_player;
    sf::RenderWindow *m_game;
};

#endif // __SMALLENEMY_H__
