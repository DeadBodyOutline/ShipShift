#include "ship.h"

Ship::Ship(int width, int height)
    : sf::Drawable()
    , m_ship(nullptr)
    , m_width(width)
    , m_height(height)
    , m_hull(100.f)
    , m_velocity(1.f)
{
}

Ship::~Ship()
{
}

void Ship::setPosition(int x, int y)
{
    sf::Vector2f v(x, y);
    this->setPosition(v);
}

void Ship::setPosition(sf::Vector2f point)
{
    if (!m_ship || point == m_ship->getPosition())
        return;

    m_ship->setPosition(point.x, point.y);
}

sf::Vector2f Ship::position() const
{
    if (!m_ship)
        return sf::Vector2f();

    return m_ship->getPosition();
}

void Ship::setScale(float scaleX, float scaleY)
{
    if (!m_ship)
        return;

    // XXX should width() and height() return its values multiplied by scale?
    m_ship->setScale(scaleX, scaleY);
}

int Ship::width() const
{
    return m_width;
}

int Ship::height() const
{
    return m_height;
}

void Ship::setRotation(float angle)
{
    if (!m_ship)
        return;

    m_ship->setRotation(angle);
}

float Ship::rotation() const
{
    if (!m_ship)
        return -1.f;

    return m_ship->getRotation();
}

void Ship::setColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
    if (!m_ship)
        return;

    setColor(sf::Color(r, g, b, 255));
}

void Ship::setColor(sf::Color color)
{
    if (!m_ship)
        return;

    m_ship->setFillColor(color);
}

sf::Color Ship::color() const
{
    if (!m_ship)
        return sf::Color();

    return m_ship->getFillColor();
}

void Ship::setOutlineColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
    if (!m_ship)
        return;

    setOutlineColor(sf::Color(r, g, b, 255));
}

void Ship::setOutlineColor(sf::Color color)
{
    if (!m_ship)
        return;

    m_ship->setOutlineColor(color);
}

sf::Color Ship::outlineColor() const
{
    if (!m_ship)
        return sf::Color();

    return m_ship->getOutlineColor();
}

void Ship::setOutlineThickness(float thickness)
{
    if (!m_ship)
        return;

    m_ship->setOutlineThickness(thickness);
}

float Ship::outlineThickness() const
{
    if (!m_ship)
        return -1;

    return m_ship->getOutlineThickness();
}

void Ship::setTransparency(float value)
{
    if (!m_ship)
        return;

    int transparency = std::max(0.0, std::min(std::ceil(value * 255.0), 255.0));

    // TODO setFillColor and setOutlineColor transparency
}

void Ship::update(sf::Time delta)
{
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!m_ship)
        return;

    target.draw(*m_ship);
}
