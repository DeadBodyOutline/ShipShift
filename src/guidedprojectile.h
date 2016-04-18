#ifndef __GUIDEDPROJECTILE_H__
#define __GUIDEDPROJECTILE_H__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>

#include "projectile.h"
#include "ship.h"

class GuidedProjectile : public Projectile
{
public:
    GuidedProjectile(int width = 8, int height = 40);
    virtual ~GuidedProjectile();

    void setTarget(Ship *target);

    void update(sf::Time delta = sf::Time::Zero);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    Ship *m_target;
};

#endif // __GUIDEDPROJECTILE_H__
