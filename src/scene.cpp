#include "scene.h"
#include "boid.h"

#include <Thor/Vectors/VectorAlgebra2D.hpp>

Scene::Scene()
    : m_score(0)
{
    m_player = new Player(20, 20);
    m_player->setPosition(800 / 2, 600 / 2);
}

Scene *Scene::instance()
{
    static Scene *instance = new Scene;
    return instance;
}

void Scene::update(float dt)
{
    for (auto i = m_events.begin(); i != m_events.end(); ) {
        (*i)->update(dt);

        if ((*i)->finished())
            i = m_events.erase(i);
        else
            ++i;
    }

    checkCollisions();

    sf::Time delta = sf::seconds(dt);

    m_waveController.update(dt);
    m_player->update(delta);

    for (auto i = m_ships.begin(); i != m_ships.end(); ) {
        (*i)->update(delta);

        Boid *boid = dynamic_cast<Boid *>(*i);
        if (!boid)
            continue;

        if (boid->markedForDeletion())
            i = m_ships.erase(i);
        else
            ++i;
    }

    for (auto i = m_projectiles.begin(); i != m_projectiles.end(); ) {
        (*i)->update(delta);

        if ((*i)->markedForDeletion())
            i = m_projectiles.erase(i);
        else
            ++i;
    }

    if (!m_ships.size())
        m_waveController.nextWave();
}

void Scene::draw()
{
    for (Projectile *projectile : m_projectiles)
        m_game->draw(*projectile);

    for (Ship *ship : m_ships)
        m_game->draw(*ship);

    m_game->draw(*m_player);

    for (TimedEvent *event : m_events)
        m_game->draw(*event);
}

void Scene::addShip(Ship *ship)
{
    m_ships.push_back(ship);
}

void Scene::addProjectile(Projectile *projectile)
{
    m_projectiles.push_back(projectile);
}

void Scene::addTimedEvent(TimedEvent *event)
{
    m_events.push_back(event);
}

// someday, implement a quadtree (aabb) to achieve this ;)
void Scene::checkCollisions()
{
    bool collide = false;
    for (auto ship: m_ships) {
        collide = m_player->collideWith(ship, true);

        if (collide) {
            Boid *boid = dynamic_cast<Boid *>(ship);
            if (!boid)
                continue;

            boid->markForDeletion();
            m_player->receiveDamage(boid->damage(), true);
            addScore(boid->damage());
        }
    }

    for (auto projectile: m_projectiles) {
        if (projectile->playerProjectile()) {
            // NOOOOOOOOOOOOoo--
            // ¯\_(ツ)_/¯
            for (auto ship: m_ships) {
                collide = ship->collideWith(projectile->shape());
                if (collide) {
                    projectile->markForDeletion();

                    Boid *boid = dynamic_cast<Boid *>(ship);
                    if (boid) {
                        boid->receiveDamage(projectile->damage());
                        if (boid->markedForDeletion())
                            addScore(boid->damage());
                    }

                    break;
                }
            }
        } else {
            collide = m_player->collideWith(projectile);
            if (collide) {
                projectile->markForDeletion();
                m_player->receiveDamage(projectile->damage());
            }
        }
    }
}

void Scene::reset()
{
    m_score = 0;
    for (auto i = m_ships.begin(); i != m_ships.end();)
        i = m_ships.erase(i);
    for (auto i = m_projectiles.begin(); i != m_projectiles.end();)
        i = m_projectiles.erase(i);
    for (auto i = m_events.begin(); i != m_events.end();)
        i = m_events.erase(i);
    delete m_player;
    m_player = new Player(20, 20);
    m_player->setPosition(800 / 2, 600 / 2);
    m_waveController.reset();
}

Ship *Scene::nearestEnemy()
{
    Ship *nearest = nullptr;
    float minDist = 99999999999.f;
    for (Ship *ship : m_ships) {
        float dist = thor::length(m_player->position() - ship->position());
        if (dist < minDist) {
            minDist = dist;
            nearest = ship;
        }
    }

        return nearest;
}
