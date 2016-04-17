#include "wavecontroller.h"

#include <Thor/Vectors/VectorAlgebra2D.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "scene.h"
#include "mediumenemy.h"
#include "smallenemy.h"

WaveController::WaveController()
    : m_currentWave(0)
{
}

void WaveController::update(float dt)
{
    m_timeToNewWave -= dt;

    if (m_timeToNewWave <= 0.f) {
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
        spawnMediumEnemyCluster();
    } else if (m_currentWave == 2) {
        spawnSmallEnemyCluster();
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

void WaveController::spawnMediumEnemyCluster()
{
    Scene *scene = Scene::instance();
    sf::RenderWindow *game = scene->game();
    Player *player = scene->player();

    sf::Vector2u size = game->getSize();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> wDis(0, size.x);
    std::uniform_int_distribution<> hDis(0, size.y);
    std::uniform_real_distribution<> wanderDis(2.f, 5.f);
    std::uniform_real_distribution<> spawnDis(20.f, 300.f);

    for (int i = 0; i < 10; ++i) {
        MediumEnemy *enemy = new MediumEnemy(20, 20);
        enemy->setPosition(wDis(gen), hDis(gen));
        // don't spawn enemies too close to the player
        float spawnDistance = 200.f + spawnDis(gen);
        sf::Vector2f desired = player->position() - enemy->position();
        float toDist = thor::length(desired);
        if (std::fabs(toDist) < spawnDistance)
            desired = enemy->position() + sf::Vector2f(-desired.y, desired.x) - player->position();
        desired = thor::unitVector(desired);
        desired = desired * spawnDistance;
        enemy->setPosition(player->position() + desired);
        enemy->setMaxSpeed(0.5f);
        enemy->setMaxAcceleration(0.01f);
        enemy->setWanderTime(wanderDis(gen));
        scene->addShip(static_cast<Ship *>(enemy));
    }
}

void WaveController::spawnSmallEnemyCluster()
{
    Scene *scene = Scene::instance();
    sf::RenderWindow *game = scene->game();
    Player *player = scene->player();

    sf::Vector2u size = game->getSize();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> wDis(0, size.x);
    std::uniform_int_distribution<> hDis(0, size.y);
    std::uniform_real_distribution<> wanderDis(2.f, 5.f);
    // every enemy will spawn offscreen
    float spawnDistance = std::max<float>(size.x, size.y) + 10.f;

    for (int i = 0; i < 50; ++i) {
        SmallEnemy *enemy = new SmallEnemy(7, 7);
        enemy->setPosition(wDis(gen), hDis(gen));
        sf::Vector2f desired = player->position() - enemy->position();
        float toDist = thor::length(desired);
        if (std::fabs(toDist) < spawnDistance)
            desired = enemy->position() + sf::Vector2f(-desired.y, desired.x) - player->position();
        desired = thor::unitVector(desired);
        desired = desired * spawnDistance;
        enemy->setPosition(player->position() + desired);
        enemy->setMaxSpeed(0.8f);
        enemy->setMaxAcceleration(0.03);
        enemy->setWanderTime(wanderDis(gen));
        scene->addShip(static_cast<Ship *>(enemy));
    }
}
