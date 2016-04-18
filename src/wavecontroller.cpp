#include "wavecontroller.h"

#include <Thor/Vectors/VectorAlgebra2D.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cmath>

#include "scene.h"
#include "mediumenemy.h"
#include "smallenemy.h"
#include "largeenemy.h"

#include <iostream>

WaveController::WaveController()
    : m_currentWave(0)
    , m_timeToNewWave(30)
    , m_timeToNewWaveAcc(0.f)
{
}

void WaveController::update(float dt)
{
    m_timeToNewWaveAcc -= dt;

    if (m_timeToNewWaveAcc <= 0.f) {
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
        spawnMediumEnemyCluster(m_currentWave);
    } else if (m_currentWave == 2) {
        spawnSmallEnemyCluster(m_currentWave);
    } else if (m_currentWave == 3) {
        spawnLargeEnemyCluster(m_currentWave);
    } else if (m_currentWave == 4) {
        m_timeToNewWave = 30;
        spawnMediumEnemyCluster(m_currentWave);
        spawnLargeEnemyCluster(m_currentWave);
    } else if (m_currentWave == 5) {
        spawnSmallEnemyCluster(m_currentWave);
        spawnLargeEnemyCluster(m_currentWave);
    } else if (m_currentWave == 6) {
        spawnSmallEnemyCluster(m_currentWave);
        spawnMediumEnemyCluster(m_currentWave);
    } else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> firstDis(0, 3);
        std::uniform_int_distribution<> secDis(0, 1);

        int shipType = firstDis(gen);
        if (shipType == 0) {
            spawnMediumEnemyCluster(m_currentWave);
            shipType = secDis(gen);
            if (shipType == 0)
                spawnSmallEnemyCluster(m_currentWave);
            else
                spawnLargeEnemyCluster(m_currentWave);
        } else if (shipType == 1) {
            spawnSmallEnemyCluster(m_currentWave);
            shipType = secDis(gen);
            if (shipType == 0)
                spawnMediumEnemyCluster(m_currentWave);
            else
                spawnLargeEnemyCluster(m_currentWave);
        }
        else if (shipType == 2) {
            spawnLargeEnemyCluster(m_currentWave);
            shipType = secDis(gen);
            if (shipType == 0)
                spawnMediumEnemyCluster(m_currentWave);
            else
                spawnSmallEnemyCluster(m_currentWave);
        }
    }

    m_timeToNewWaveAcc = m_timeToNewWave;
}

void WaveController::spawnMediumEnemyCluster(float wave)
{
    int numEnemies = 1 + (int)(wave * std::log(wave));
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
    std::uniform_real_distribution<> fireDis(2.f, 5.f);

    for (int i = 0; i < numEnemies; ++i) {
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
        enemy->setFireTime(fireDis(gen));
        enemy->setDamage(30.f);
        enemy->setHealth(20);
        scene->addShip(static_cast<Ship *>(enemy));
    }
}

void WaveController::spawnSmallEnemyCluster(float wave)
{
    int numEnemies = (int)(wave * wave);
    Scene *scene = Scene::instance();
    sf::RenderWindow *game = scene->game();
    Player *player = scene->player();

    sf::Vector2u size = game->getSize();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> wDis(0, size.x);
    std::uniform_int_distribution<> hDis(0, size.y);
    std::uniform_real_distribution<> wanderDis(4.f, 6.f);
    // every enemy will spawn offscreen
    float spawnDistance = std::max<float>(size.x, size.y) + 10.f;

    for (int i = 0; i < numEnemies; ++i) {
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
        enemy->setDamage(20.f);
        enemy->setFireTime(8.f);
        scene->addShip(static_cast<Ship *>(enemy));
    }
}

void WaveController::spawnLargeEnemyCluster(float wave)
{
    int numEnemies = (int)std::log(wave);
    Scene *scene = Scene::instance();
    sf::RenderWindow *game = scene->game();
    Player *player = scene->player();

    sf::Vector2u size = game->getSize();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> wDis(0, size.x);
    std::uniform_int_distribution<> hDis(0, size.y);
    std::uniform_real_distribution<> wanderDis(2.f, 5.f);
    std::uniform_real_distribution<> spawnDis(20.f, 50.f);
    std::uniform_real_distribution<> fireDis(8.f, 10.f);

    for (int i = 0; i < numEnemies; ++i) {
        LargeEnemy *enemy = new LargeEnemy(50, 50);
        enemy->setPosition(wDis(gen), hDis(gen));
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
        enemy->setFireTime(fireDis(gen));
        enemy->setHealth(100);
        enemy->setDamage(90.f);
        scene->addShip(static_cast<Ship *>(enemy));
    }
}

void WaveController::reset()
{
    m_currentWave = 0;
    m_timeToNewWave = 20;
    m_timeToNewWaveAcc = 0.f;
}
