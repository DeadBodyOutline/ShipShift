#ifndef __BOID_H__
#define __BOID_H__

#include "ship.h"
#include "player.h"

class Boid : public Ship
{
public:
    Boid(int width, int height);

    void update(sf::Time delta = sf::Time::Zero);
    // TODO: limit maxSpeed and maxforce
    void seek(sf::Vector2f target, float weight = 1.f);
    void keepDistance(sf::Vector2f target, float distance, float weight = 1.f);
    void wander(float dt, sf::Vector2f wanderTopLeft, sf::Vector2f wanderBottomRight, float weight = 1.f);
    void applyForce(sf::Vector2f force, float weight = 1.f);
    void setMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }
    void setMaxAcceleration(float maxAcceleration) { m_maxAcceleration = maxAcceleration; }
    void setWanderTime(float wanderTime) { m_wanderTime = wanderTime; }
    void setFireTime(float fireTime) { m_fireTime = m_fireTimeAcc = fireTime; }

protected:
    sf::Vector2f m_boidVelocity;
    sf::Vector2f m_boidAcceleration;
    sf::Vector2f m_wanderTarget;
    float m_maxSpeed;
    float m_maxAcceleration;
    float m_wanderTime;
    float m_wanderTimeAcc;
    float m_fireTime;
    float m_fireTimeAcc;
    Player *m_player;
    sf::RenderWindow *m_game;
};

#endif // __BOID_H__
