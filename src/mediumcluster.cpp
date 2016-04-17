#include "mediumcluster.h"

#include <Thor/Vectors/VectorAlgebra2D.hpp>
#include <random>

MediumCluster::MediumCluster(sf::RenderWindow &renderWindow, Player &player)
    : Cluster(renderWindow, player)
{
}

void MediumCluster::update(float dt)
{
    int i = 0;
    for (Boid *boid : m_boids) {
        boid->seek(m_player.position());
        boid->wander(dt, sf::Vector2f(0.f, 0.f), (sf::Vector2f)m_renderWindow.getSize(), 0.6);
        boid->update(sf::seconds(dt));
    }
}

void MediumCluster::spawn()
{
    sf::Vector2u size = m_renderWindow.getSize();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> wDis(0, size.x);
    std::uniform_int_distribution<> hDis(0, size.y);
    std::uniform_real_distribution<> wanderDis(2.f, 5.f);
    std::uniform_real_distribution<> spawnDis(20.f, 300.f);

    for (int i = 0; i < 10; ++i) {
        MediumEnemy *enemy = new MediumEnemy(20, 20);
        enemy->setPosition(wDis(gen), hDis(gen));
        // don't spawn enemies too close to the player
        float spawnDistance = 200.f + spawnDis(gen);
        sf::Vector2f desired = m_player.position() - enemy->position();
        float toDist = thor::length(desired);
        if (std::fabs(toDist) < spawnDistance)
            desired = enemy->position() + sf::Vector2f(-desired.y, desired.x) - m_player.position();
        desired = thor::unitVector(desired);
        desired = desired * spawnDistance;
        enemy->setPosition(m_player.position() + desired);
        enemy->setMaxSpeed(0.5f);
        enemy->setMaxAcceleration(0.01f);
        enemy->setWanderTime(wanderDis(gen));
        m_boids.push_back(static_cast<Boid *>(enemy));
    }
}
