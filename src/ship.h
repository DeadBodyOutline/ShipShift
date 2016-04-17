#ifndef __SHIP_H__
#define __SHIP_H__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>

class Ship : public sf::Drawable
{
public:
    Ship(int width, int height);
    virtual ~Ship();

    virtual void attack() = 0;
    virtual void altAttack() = 0;

    virtual void setPosition(int x, int y);
    void setPosition(sf::Vector2f point);
    virtual sf::Vector2f position() const;

    virtual void setScale(float scaleX, float scaleY);
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

    // 0.0-1.0
    virtual void setTransparency(float value);

    virtual void move(const float x, const float y);
    void rotate(int x, int y);
    void rotate(sf::Vector2f target);

    virtual void setMaxVelocity(float maxVelocity);
    virtual float maxVelocity() const;
    virtual void setVelModifier(float velModifier);
    virtual float velModifier() const;

    virtual void setVisible(bool visible);
    virtual bool visible() const;

    virtual void update(sf::Time delta = sf::Time::Zero);

    float angle() const { return m_angle; }

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Shape *m_ship;

    int m_width;
    int m_height;

    float m_hull;

    float m_maxVelocity;
    float m_velModifier;

    bool m_visible;
    float m_angle;
};

#endif // __SHIP_H__
