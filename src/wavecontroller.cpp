#include "wavecontroller.h"

#include <Thor/Vectors/VectorAlgebra2D.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "scene.h"
#include "mediumenemy.h"
#include "smallenemy.h"
#include "largeenemy.h"

#include <iostream>

WaveController::WaveController()
    : m_currentWave(0)
    , m_timeToNewWave(20)
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
        spawnMediumEnemyCluster();
    } else if (m_currentWave == 2) {
        spawnSmallEnemyCluster();
    } else if (m_currentWave == 3) {
        spawnLargeEnemyCluster();
    } else if (m_currentWave == 4) {
        m_timeToNewWave = 30;
        spawnMediumEnemyCluster();
        spawnLargeEnemyCluster();
    } else if (m_currentWave == 5) {
        spawnSmallEnemyCluster();
        spawnLargeEnemyCluster();
    } else if (m_currentWave == 6) {
        spawnSmallEnemyCluster();
        spawnMediumEnemyCluster();
    } else {
        // TODO: the game is supposed to be infinite,
        // but we couldn't get it done in time for ludumdare
        // so, game over :/
        Scene::instance()->player()->setHealth(0.f);
    }

    m_timeToNewWaveAcc = m_timeToNewWave;
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
    std::uniform_real_distribution<> fireDis(2.f, 5.f);

    for (int i = 0; i < 5; ++i) {
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
    std::uniform_real_distribution<> wanderDis(4.f, 6.f);
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
        enemy->setFireTime(8.f);
        scene->addShip(static_cast<Ship *>(enemy));
    }
}

void WaveController::spawnLargeEnemyCluster()
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
    std::uniform_real_distribution<> spawnDis(20.f, 50.f);
    std::uniform_real_distribution<> fireDis(8.f, 10.f);

    for (int i = 0; i < 4; ++i) {
        LargeEnemy *enemy = new LargeEnemy(40, 50);
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
        scene->addShip(static_cast<Ship *>(enemy));
    }
}

void WaveController::reset()
{
    m_currentWave = 0;
    m_timeToNewWave = 20;
    m_timeToNewWaveAcc = 0.f;
}
