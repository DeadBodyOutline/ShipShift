#include "mediumcluster.h"

MediumCluster::MediumCluster(sf::RenderWindow &renderWindow)
    : Cluster(renderWindow)
{
}

void MediumCluster::update(float dt)
{
    // TODO: loop and update enemies
}


void MediumCluster::spawn()
{
    sf::Vector2u size = m_renderWindow.getSize();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> wDis(0, size.x);
    std::uniform_int_distribution<> hDis(0, size.y);

    for (int i = 0; i < 10; ++i) {
        MediumEnemy *enemy = new MediumEnemy(20, 20);
        enemy->setPosition(wDis(gen), hDis(gen));
        m_ships.push_back(static_cast<Ship *>(enemy));
    }
}
