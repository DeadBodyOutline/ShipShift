#include "cluster.h"

Cluster::Cluster(sf::RenderWindow &renderWindow)
    : m_renderWindow(renderWindow)
{
}

void Cluster::draw()
{
    for (Ship *ship : m_ships)
        m_renderWindow.draw(*ship);
}
