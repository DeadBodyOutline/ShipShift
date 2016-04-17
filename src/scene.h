#ifndef __SCENE_H__
#define __SCENE_H__

#include <SFML/Graphics.hpp>
#include <vector>

#include "player.h"
#include "ship.h"
#include "projectile.h"
#include "wavecontroller.h"

class Scene
{
public:
    static Scene *instance();
    void setPlayer(Player *player) { m_player = player; }
    void setGame(sf::RenderWindow *game) { m_game = game; }
    Player *player() { return m_player; }
    sf::RenderWindow *game() { return m_game; }
    void update(float dt);
    void draw();
    void addShip(Ship *ship);
    void addProjectile(Projectile *projectile);

protected:
    Scene();

protected:
    static Scene *m_instance;
    Player *m_player;
    sf::RenderWindow *m_game;
    WaveController m_waveController;
    std::vector<Ship *> m_ships;
    std::vector<Projectile *> m_projectiles;
};

#endif // __SCENE_H__
