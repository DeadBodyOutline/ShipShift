#ifndef __CIRCLEPROJECTILE_H__
#define __CIRCLEPROJECTILE_H__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>

#include "projectile.h"

class CircleProjectile : public Projectile
{
public:
    CircleProjectile(int width = 2, int height = 20);
    virtual ~CircleProjectile();

    void update(sf::Time delta = sf::Time::Zero);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // __CIRCLEPROJECTILE_H__
