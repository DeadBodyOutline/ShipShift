#include "boid.h"

#include <Thor/Vectors/VectorAlgebra2D.hpp>
#include <cmath>
#include "stuffmath.h"

Boid::Boid(int width, int height)
    : Ship(width, height)
    , m_maxSpeed(0.f)
    , m_maxAcceleration(0.f)
    , m_wanderTime(0.f)
    , m_wanderTimeAcc(0.f)
{
}

void Boid::update(sf::Time delta)
{
    m_boidVelocity += m_boidAcceleration;
    m_ship->setPosition(m_ship->getPosition() + m_boidVelocity);
    m_boidAcceleration *= 0.f;
}

void Boid::seek(sf::Vector2f target, float weight)
{
    sf::Vector2f desired = target - m_ship->getPosition();
    desired = thor::unitVector(desired);
    desired = desired * m_maxSpeed;
    desired = truncate(desired, m_maxSpeed);

    sf::Vector2f steer = desired - m_boidVelocity;
    applyForce(steer, weight);
}

void Boid::wander(float dt, sf::Vector2f wanderTopLeft, sf::Vector2f wanderBottomRight, float weight)
{
    if (m_wanderTime <= 0)
        return;

    m_wanderTimeAcc -= dt;
    if (m_wanderTimeAcc <= 0.f) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> wDis(wanderTopLeft.x, wanderBottomRight.x);
        std::uniform_real_distribution<> hDis(wanderTopLeft.y, wanderBottomRight.y);
        m_wanderTarget = sf::Vector2f(wDis(gen), hDis(gen));
        m_wanderTimeAcc = m_wanderTime;
    }

    seek(m_wanderTarget, weight);
}

void Boid::applyForce(sf::Vector2f force, float weight)
{
    m_boidAcceleration += truncate(force * weight, m_maxAcceleration);
}
