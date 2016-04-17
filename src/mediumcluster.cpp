#include "mediumcluster.h"

#include <random>

MediumCluster::MediumCluster(sf::RenderWindow &renderWindow)
    : Cluster(renderWindow)
{
}

void MediumCluster::update(float dt)
{
    // TODO: remove, test code
    int i = 0;
    for (Boid *boid : m_boids) {
        boid->seek(sf::Vector2f(400.f, 400.f), 0.3f);
        boid->wander(dt, sf::Vector2f(0.f, 0.f), (sf::Vector2f)m_renderWindow.getSize(), 0.5f);
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

    for (int i = 0; i < 10; ++i) {
        MediumEnemy *enemy = new MediumEnemy(20, 20);
        enemy->setPosition(wDis(gen), hDis(gen));
        enemy->setMaxSpeed(0.4f);
        enemy->setWanderTime(wanderDis(gen));
        m_boids.push_back(static_cast<Boid *>(enemy));
    }
}
