#ifndef __BOID_H__
#define __BOID_H__

#include "ship.h"

class Boid : public Ship
{
public:
    Boid(int width, int height);

    void update(sf::Time delta = sf::Time::Zero);
    void seek(sf::Vector2f target);
    void applyForce(sf::Vector2f force);
    void setMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }
    void setMaxForce(float maxForce) { m_maxForce = maxForce; }

protected:
    sf::Vector2f m_boidVelocity;
    sf::Vector2f m_boidAcceleration;
    float m_maxSpeed;
    float m_maxForce;
};

#endif // __BOID_H__
