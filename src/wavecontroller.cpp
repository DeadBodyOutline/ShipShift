#include "wavecontroller.h"

#include <iostream>

WaveController::WaveController()
    : m_currentWave(0)
{
}

void WaveController::update(float dt)
{
    for (auto cluster : m_clusters)
        cluster->update(dt);

    m_timeToNewWave -= dt;

    // TODO activate the size rule when we have some enemy ships :)
    if (/*!m_clusters.size() || */m_timeToNewWave <= 0.f) {
        ++m_currentWave;
        spawnCluster();
    }
}

void WaveController::spawnCluster()
{
    m_timeToNewWave = 30.f; // 30 seconds for each wave. This value can be changed below in the spawn rules

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
        m_timeToNewWave = 40;
    }
    // ...
    else if (m_currentWave == 4) {
        // TODO: maybe from wave 6 to 10, spawn mixed waves, changing enemy attributes to
        // increase difficulty
    } else {
        m_timeToNewWave = 45;
       // TODO: after this point, spawn random mixed waves, increasing difficulty
    }

    std::cout << "Spawnning new wave! Wave number " << m_currentWave << ". Time to new wave: " << m_timeToNewWave << " seconds." << std::endl;
}
