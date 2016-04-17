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
    void altAttack();

    void accelerate();
    void deacelerate();

    void rotate(int x, int y);

    void changeShipType(ShipType type);
    ShipType shipType();

    void setPosition(int x, int y);
    void setPosition(sf::Vector2f point);
    sf::Vector2f position() const;

    void update(float delta);
    void update(sf::Time delta = sf::Time::Zero);

private:
    void revaluateVelocity();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    Ship *m_currentShip;
    std::map<ShipType, Ship *> m_ships;

    ShipType m_shipType;

    float m_velocity;
    float m_step;

    float m_angle;
};

#endif // __PLAYER_H__
