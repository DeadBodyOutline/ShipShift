#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

#include <string>

#include <Thor/Animations.hpp>

#include "sprite.h"
#include "animation.h"

class AnimatedSprite : public Sprite
{
public:
    AnimatedSprite(const std::string &fileName, int width = 0, int height = 0);
    virtual ~AnimatedSprite();

    virtual void addAnimation(const Animation &animation, sf::Time duration = sf::seconds(1.0f));

    virtual void play(const std::string &animation);
    virtual void stop();

    void setPosition(int x, int y);
    void setPosition(sf::Vector2f point);
    sf::Vector2f position() const;

    virtual void update(sf::Time delta = sf::Time::Zero);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    thor::Animator<sf::Sprite, std::string> m_animator;
    thor::AnimationMap<sf::Sprite, std::string> m_animationMap;
};

#endif // __ANIMATEDSPRITE_H__
