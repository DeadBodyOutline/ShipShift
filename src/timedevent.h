#ifndef __TIMEDEVENT_H__
#define __TIMEDEVENT_H__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>
#include <functional>

class TimedEvent : public sf::Drawable
{
public:
    TimedEvent(float triggerTime, float duration = 0.f);
    void update(float dt);
    void onTrigger(std::function<void()> handler);
    void onFinish(std::function<void()> handler);
    void onDraw(std::function<void(sf::RenderTarget&, sf::RenderStates)> handler);
    bool triggered() const { return m_triggered; }
    bool running() const { return m_running; }
    bool finished() const { return m_finished; }
    void run(std::function<void(float)> handler);
    void wait(std::function<void(float)> handler);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
    float m_triggerTime;
    float m_duration;
    bool m_triggered;
    bool m_running;
    bool m_finished;
    std::function<void()> m_onTriggered;
    std::function<void(float)> m_onRun;
    std::function<void(float)> m_onWait;
    std::function<void()> m_onFinished;
    std::function<void(sf::RenderTarget&, sf::RenderStates)> m_onDraw;
};

#endif // __TIMEDEVENT_H__
