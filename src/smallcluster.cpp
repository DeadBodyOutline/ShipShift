#include "smallcluster.h"

#include <Thor/Vectors/VectorAlgebra2D.hpp>
#include "smallenemy.h"

SmallCluster::SmallCluster(sf::RenderWindow &renderWindow, Player &player)
    : Cluster(renderWindow, player)
{
}

void SmallCluster::update(float dt)
{
    int i = 0;
    for (Boid *boid : m_boids) {
        boid->keepDistance(m_player.position(), 250.f);
        boid->wander(dt, sf::Vector2f(0.f, 0.f), (sf::Vector2f)m_renderWindow.getSize(), 0.01);
        boid->update(sf::seconds(dt));
    }
}

void SmallCluster::spawn()
{
    sf::Vector2u size = m_renderWindow.getSize();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> wDis(0, size.x);
    std::uniform_int_distribution<> hDis(0, size.y);
    std::uniform_real_distribution<> wanderDis(2.f, 5.f);
    // every enemy will spawn offscreen
    float spawnDistance = std::max<float>(size.x, size.y) + 10.f;

    for (int i = 0; i < 50; ++i) {
        SmallEnemy *enemy = new SmallEnemy(7, 7);
        enemy->setPosition(wDis(gen), hDis(gen));
        sf::Vector2f desired = m_player.position() - enemy->position();
        float toDist = thor::length(desired);
        if (std::fabs(toDist) < spawnDistance)
            desired = enemy->position() + sf::Vector2f(-desired.y, desired.x) - m_player.position();
        desired = thor::unitVector(desired);
        desired = desired * spawnDistance;
        enemy->setPosition(m_player.position() + desired);
        enemy->setMaxSpeed(0.8f);
        enemy->setMaxAcceleration(0.03);
        enemy->setWanderTime(wanderDis(gen));
        m_boids.push_back(static_cast<Boid *>(enemy));
    }
}
