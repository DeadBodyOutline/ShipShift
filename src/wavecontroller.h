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
    float waveTime() const { return m_timeToNewWave; }
    float waveTimeAcc() const { return m_timeToNewWaveAcc; }

private:
    unsigned int m_currentWave;
    float m_timeToNewWave;
    float m_timeToNewWaveAcc;
};

#endif // __WAVECONTROLLER_H__
