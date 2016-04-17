#include "cluster.h"

Cluster::Cluster(sf::RenderWindow &renderWindow, Player &player)
    : m_renderWindow(renderWindow)
    , m_player(player)
{
}

void Cluster::draw()
{
    for (Boid *boid : m_boids)
        m_renderWindow.draw(*boid);
}
