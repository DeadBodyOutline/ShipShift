#ifndef __WAVECONTROLLER_H__
#define __WAVECONTROLLER_H__

#include <vector>

#include "cluster.h"

class WaveController
{
public:
    WaveController();
    void update(float dt);
    void spawnCluster();
    unsigned int currentWave() const { return m_currentWave; }

private:
    std::vector<Cluster *> m_clusters;
    unsigned int m_currentWave;
};

#endif // __WAVECONTROLLER_H__
