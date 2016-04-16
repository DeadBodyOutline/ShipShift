#include "boid.h"

#include <Thor/Vectors/VectorAlgebra2D.hpp>
#include "stuffmath.h"

Boid::Boid(int width, int height)
    : Ship(width, height)
    , m_maxSpeed(0.f)
    , m_maxForce(0.f)
{
}

void Boid::update(sf::Time delta)
{
    m_boidVelocity += m_boidAcceleration;
    m_ship->setPosition(m_ship->getPosition() + m_boidVelocity);
    m_boidAcceleration *= 0.f;
}

void Boid::seek(sf::Vector2f target)
{
    sf::Vector2f desired = target - m_ship->getPosition();
    desired = thor::unitVector(desired);
    desired = desired * m_maxSpeed;

    sf::Vector2f steer = desired - m_boidVelocity;
    applyForce(steer);
}

void Boid::applyForce(sf::Vector2f force)
{
    m_boidAcceleration = force;
}
