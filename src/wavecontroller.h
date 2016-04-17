#ifndef __WAVECONTROLLER_H__
#define __WAVECONTROLLER_H__

#include <vector>
#include <SFML/Graphics.hpp>

class WaveController
{
public:
    WaveController();
    void update(float dt);
    void spawnCluster();
    void spawnMediumEnemyCluster();
    void spawnSmallEnemyCluster();
    void spawnLargeEnemyCluster();
    unsigned int currentWave() const { return m_currentWave; }

private:
        unsigned int m_currentWave;
    float m_timeToNewWave;
};

#endif // __WAVECONTROLLER_H__
