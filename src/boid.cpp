#include <Thor/Vectors/VectorAlgebra2D.hpp>
#include <cmath>
#include <random>

#include "boid.h"
#include "stuffmath.h"
#include "scene.h"

Boid::Boid(int width, int height)
    : Ship(width, height)
    , m_maxSpeed(0.f)
    , m_maxAcceleration(0.f)
    , m_wanderTime(0.f)
    , m_wanderTimeAcc(0.f)
    , m_fireTime(0.f)
    , m_fireTimeAcc(0.f)
    , m_damage(5.f)
    , m_markedForDeletion(false)
    , m_hull(10.f)
{
    m_player = Scene::instance()->player();
    m_game = Scene::instance()->game();
}

void Boid::update(sf::Time delta)
{
    m_boidVelocity += m_boidAcceleration;
    m_ship->setPosition(m_ship->getPosition() + m_boidVelocity);
    m_boidAcceleration *= 0.f;

    rotate(m_player->position());

    if (m_fireTime <= 0.f)
        return;
    m_fireTimeAcc -= delta.asSeconds();
    if (m_fireTimeAcc <= 0.f) {
        attack();
        m_fireTimeAcc = m_fireTime;
    }
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

void Boid::keepDistance(sf::Vector2f target, float distance, float weight)
{
    sf::Vector2f desired = target - m_ship->getPosition();
    float toDist = thor::length(desired);
    if (std::fabs(toDist) < distance)
        desired = m_ship->getPosition() + sf::Vector2f(-desired.y, desired.x) - target;

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

void Boid::markForDeletion()
{
    m_markedForDeletion = true;
}

bool Boid::markedForDeletion() const
{
    return m_markedForDeletion;
}

void Boid::setDamage(float damage)
{
    m_damage = damage;
}

float Boid::damage() const
{
    return m_damage;
}

void Boid::receiveDamage(float damage)
{
    m_hull = std::max(0.f, m_hull - damage);

    if (m_hull == 0)
        m_markedForDeletion = true;
}

void Boid::setHealth(float health)
{
    m_hull = health;
}

float Boid::health() const
{
    return m_hull;
}
