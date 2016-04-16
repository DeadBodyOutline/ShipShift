#include "cluster.h"

Cluster::Cluster(sf::RenderWindow &renderWindow)
    : m_renderWindow(renderWindow)
{
}

void Cluster::draw()
{
    for (Boid *boid : m_boids)
        m_renderWindow.draw(*boid);
}
