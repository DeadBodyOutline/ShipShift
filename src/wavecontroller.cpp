#include "wavecontroller.h"

WaveController::WaveController()
    : m_currentWave(0)
{
}

void WaveController::update(float dt)
{
    for (auto cluster : m_clusters)
        cluster->update(dt);

    if (!m_clusters.size()) {
        ++m_currentWave;
        spawnCluster();
    }
}

void WaveController::spawnCluster()
{
    // The first waves shouls teach the player how to
    // play the game.
    // After the learning curve, the game clusters in waves will be
    // randomized, with increased difficulty

    if (m_currentWave == 1) {
        // TODO: spawn first wave, quick enemies to fight with the triangle ship
    } else if (m_currentWave == 2) {
        // TODO: spawn second wave, small enemies that shot bullets from all directions
        // to fight with the circle ship
    } else if (m_currentWave == 3) {
        // TODO: spawn third wave, large enemies that shot big lasers
        // to fight with the square ship
    } else if (m_currentWave == 4) {
        // TODO: maybe from wave 4 to 6, spawn some mixed waves
    }
    // ...
    else if (m_currentWave == 4) {
        // TODO: maybe from wave 6 to 10, spawn mixed waves, changing enemy attributes to
        // increase difficulty
    } else {
       // TODO: after this point, spawn random mixed waves, increasing difficulty
    }
}
