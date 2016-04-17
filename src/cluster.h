#ifndef __CLUSTER_H__
#define __CLUSTER_H__

#include <SFML/Graphics.hpp>

#include "boid.h"
#include "player.h"

class Cluster
{
public:
    Cluster(sf::RenderWindow &renderWindow, Player &player);

    enum ClusterType {
        SmallEnemies,
        MediumEnemies,
        LargeEnemies
    };

    virtual void update(float dt) = 0;
    virtual void draw();
    virtual void spawn() = 0;

protected:
    sf::RenderWindow &m_renderWindow;
    Player &m_player;
    std::vector<Boid *> m_boids;
};

#endif // __CLUSTER_H__
