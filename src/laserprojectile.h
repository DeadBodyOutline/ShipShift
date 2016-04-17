#ifndef __LASERPROJECTILE_H__
#define __LASERPROJECTILE_H__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>

#include "projectile.h"

class LaserProjectile : public Projectile
{
public:
    LaserProjectile(int width = 2, int height = 20);
    virtual ~LaserProjectile();

    void update(sf::Time delta = sf::Time::Zero);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // __LASERPROJECTILE_H__
