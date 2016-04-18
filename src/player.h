#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SFML/System.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include <memory>
#include <map>

#include "ship.h"
#include "triangleship.h"
#include "rectangleship.h"
#include "circleship.h"
#include "projectile.h"

class Player : public sf::Drawable
{
public:
    enum ShipType {
        Triangle,
        Rectangle,
        Circle
    };

    Player(int width = 50, int height = 50);
    ~Player();

    void attack();
    void altAttack(sf::Vector2i target = sf::Vector2i());

    void accelerate();
    void deacelerate();
    void rotate(int x, int y);

    void changeShipType(ShipType type);
    ShipType shipType();

    void receiveDamage(float damage);
    void setHealth(float health);
    float health() const;
    float totalHealth() const;

    void setPosition(int x, int y);
    void setPosition(sf::Vector2f point);
    sf::Vector2f position() const;

    void update(float delta);
    void update(sf::Time delta = sf::Time::Zero);

    bool collideWith(Ship *ship = nullptr);
    bool collideWith(Projectile *projectile = nullptr);

    void revaluateVelocity();

    void setCanSwitchShip(bool canSwitch);

    Ship *currentShip() { return m_currentShip; }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    Ship *m_currentShip;
    std::map<ShipType, Ship *> m_ships;

    ShipType m_shipType;

    float m_velocity;
    float m_step;
    sf::Vector2f m_targetPos;

    float m_hull;
    float m_totalHull;

    bool m_canSwitchShip;
};

#endif // __PLAYER_H__
