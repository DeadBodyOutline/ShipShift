#include "scene.h"

Scene::Scene()
{
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
    for (Ship *ship : m_ships)
        ship->update(delta);

    for (auto i = m_projectiles.begin(); i != m_projectiles.end(); ) {
        (*i)->update(delta);

        if ((*i)->markedForDeletion())
            i = m_projectiles.erase(i);
        else
            ++i;
    }
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

#include <iostream>
void Scene::checkCollisions()
{
    // someday, implement a quadtree (aabb) to achieve this ;)

    for (auto ship: m_ships) {
        bool collide = m_player->collideWith(ship);
        if (collide)
            std::cout
                << "YO: "
                << collide
                << std::endl;
    }

}
