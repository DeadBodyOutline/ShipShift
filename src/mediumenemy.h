#ifndef __MEDIUMENEMY_H__
#define __MEDIUMENEMY_H__

#include <SFML/Graphics.hpp>

#include "boid.h"
#include "player.h"

class MediumEnemy : public Boid
{
public:
    MediumEnemy(int width, int height);
    virtual void attack();
    virtual void altAttack();

    virtual void update(sf::Time delta = sf::Time::Zero);
protected:
    Player *m_player;
    sf::RenderWindow *m_game;
};

#endif // __MEDIUMENEMY_H__
