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
}

void Scene::addShip(Ship *ship)
{
    m_ships.push_back(ship);
}

void Scene::addProjectile(Projectile *projectile)
{
    m_projectiles.push_back(projectile);
}
