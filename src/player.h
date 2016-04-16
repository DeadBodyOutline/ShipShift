#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SFML/System.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include <memory>

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

    void changeShipType(ShipType type);
    ShipType shipType();

    void setPosition(int x, int y);
    void setPosition(sf::Vector2f point);
    sf::Vector2f position() const;

    void update(sf::Time delta = sf::Time::Zero);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    //void *m_currentShip;
    std::shared_ptr<Ship> m_currentShip;
    std::shared_ptr<TriangleShip> m_triangleShip;
    std::shared_ptr<RectangleShip> m_rectangleShip;
    std::shared_ptr<CircleShip> m_circleShip;

    ShipType m_shipType;

};

#endif // __PLAYER_H__
