#ifndef __RECTANGLESHIP_H__
#define __RECTANGLESHIP_H__

#include <SFML/System.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "ship.h"

class RectangleShip : public Ship
{
public:
    RectangleShip(int width = 50, int height = 50);
    ~RectangleShip();

    void attack();
    void altAttack();

    void update(sf::Time delta = sf::Time::Zero);

    float chargeTime() const { return m_chargeTime; }
    float chargeTimeAcc() const { return m_chargeTimeAcc; }
    float chargeCooldown() const { return m_chargeCooldown; }
    float chargeCooldownAcc() const { return m_chargeCooldownAcc; }
    bool charge() const { return m_charge; }

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
    bool m_charge;
    bool m_chargeEnabled;
    float m_chargeTime;
    float m_chargeTimeAcc;
    float m_chargeCooldown;
    float m_chargeCooldownAcc;
};

#endif // __RECTANGLESHIP_H__
