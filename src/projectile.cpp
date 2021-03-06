#include "projectile.h"

Projectile::Projectile(int width, int height)
    : sf::Drawable()
    , m_projectile(nullptr)
    , m_width(width)
    , m_height(height)
    , m_velocity(10.f)
    , m_damage(10.f)
    , m_liveness(5.f)
    , m_livenessCounter(0.f)
    , m_markedForDeletion(false)
    , m_playerProjectile(false)
{
}

Projectile::~Projectile()
{
}

void Projectile::setPosition(int x, int y)
{
    sf::Vector2f v(x, y);
    this->setPosition(v);
}

void Projectile::setPosition(sf::Vector2f point)
{
    if (!m_projectile || point == m_projectile->getPosition())
        return;

    m_projectile->setPosition(point.x, point.y);
}

sf::Vector2f Projectile::position() const
{
    if (!m_projectile)
        return sf::Vector2f();

    return m_projectile->getPosition();
}

int Projectile::width() const
{
    return m_width;
}

int Projectile::height() const
{
    return m_height;
}

void Projectile::setRotation(float angle)
{
    if (!m_projectile)
        return;

    m_projectile->setRotation(angle);
}

float Projectile::rotation() const
{
    if (!m_projectile)
        return -1.f;

    return m_projectile->getRotation();
}

void Projectile::setColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
    if (!m_projectile)
        return;

    setColor(sf::Color(r, g, b, 255));
}

void Projectile::setColor(sf::Color color)
{
    if (!m_projectile)
        return;

    m_projectile->setFillColor(color);
}

sf::Color Projectile::color() const
{
    if (!m_projectile)
        return sf::Color();

    return m_projectile->getFillColor();
}

void Projectile::setOutlineColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
    if (!m_projectile)
        return;

    setOutlineColor(sf::Color(r, g, b, 255));
}

void Projectile::setOutlineColor(sf::Color color)
{
    if (!m_projectile)
        return;

    m_projectile->setOutlineColor(color);
}

sf::Color Projectile::outlineColor() const
{
    if (!m_projectile)
        return sf::Color();

    return m_projectile->getOutlineColor();
}

void Projectile::setOutlineThickness(float thickness)
{
    if (!m_projectile)
        return;

    m_projectile->setOutlineThickness(thickness);
}

float Projectile::outlineThickness() const
{
    if (!m_projectile)
        return -1;

    return m_projectile->getOutlineThickness();
}

void Projectile::move(const float x, const float y)
{
    if (!m_projectile)
        return;

    m_projectile->move(x, y);
}


void Projectile::markForDeletion()
{
    m_markedForDeletion = true;
}

bool Projectile::markedForDeletion() const
{
    return m_markedForDeletion;
}

void Projectile::setPlayerProjectile(bool playerProjectile)
{
    m_playerProjectile = playerProjectile;
}

bool Projectile::playerProjectile()
{
    return m_playerProjectile;
}

float Projectile::damage() const
{
    return m_damage;
}

void Projectile::update(sf::Time delta)
{
    if (m_markedForDeletion)
        return;

    m_livenessCounter += delta.asSeconds();

    if (m_livenessCounter >= m_liveness) {
        m_markedForDeletion = true;
        m_livenessCounter = 0.f;
    }
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!m_projectile && m_markedForDeletion)
        return;

    target.draw(*m_projectile);
}

sf::Shape *Projectile::shape()
{
    return m_projectile;
}
