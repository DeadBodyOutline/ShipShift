#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>

class Projectile : public sf::Drawable
{
public:
    Projectile(int width, int height);
    virtual ~Projectile();

    virtual void setPosition(int x, int y);
    void setPosition(sf::Vector2f point);
    virtual sf::Vector2f position() const;

    virtual int width() const;
    virtual int height() const;

    virtual void setRotation(float angle);
    virtual float rotation() const;

    virtual void setColor(sf::Uint8 r = 255, sf::Uint8 g = 255, sf::Uint8 b = 255);
    void setColor(sf::Color color);
    virtual sf::Color color() const;

    virtual void setOutlineColor(sf::Uint8 r = 255, sf::Uint8 g = 255, sf::Uint8 b = 255);
    void setOutlineColor(sf::Color color);
    virtual sf::Color outlineColor() const;

    virtual void setOutlineThickness(float thickness);
    virtual float outlineThickness() const;

    virtual void move(const float x, const float y);

    void markForDeletion();
    bool markedForDeletion() const;

    virtual void setPlayerProjectile(bool playerProjectile);
    virtual bool playerProjectile();

    virtual void setDamage(float damage) { m_damage = damage; }
    virtual float damage() const;

    void setVelocity(float velocity) { m_velocity = velocity; }

    virtual void update(sf::Time delta = sf::Time::Zero);

    virtual sf::Shape *shape();

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Shape *m_projectile;

    int m_width;
    int m_height;

    float m_velocity;
    float m_damage;

    float m_liveness;

private:
    float m_livenessCounter;
    bool m_markedForDeletion;

    bool m_playerProjectile;
};

#endif // __PROJECTILE_H__
