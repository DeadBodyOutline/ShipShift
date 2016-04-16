#ifndef __WAVECONTROLLER_H__
#define __WAVECONTROLLER_H__

#include <vector>
#include <SFML/Graphics.hpp>

#include "cluster.h"

class WaveController
{
public:
    WaveController(sf::RenderWindow &renderWindow);
    void update(float dt);
    void draw();
    void spawnCluster();
    void spawnMediumEnemyCluster();
    unsigned int currentWave() const { return m_currentWave; }

private:
    sf::RenderWindow &m_renderWindow;
    std::vector<Cluster *> m_clusters;
    unsigned int m_currentWave;
    float m_timeToNewWave;
};

#endif // __WAVECONTROLLER_H__
