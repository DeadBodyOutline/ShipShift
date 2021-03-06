#include "timedevent.h"

TimedEvent::TimedEvent(float triggerTime, float duration)
    : m_triggerTime(triggerTime)
    , m_duration(duration)
    , m_triggered(false)
    , m_running(false)
    , m_finished(false)
    , m_onTriggered([](){})
    , m_onRun([](float){})
    , m_onWait([](float){})
    , m_onFinished([](){})
    , m_onDraw([](sf::RenderTarget&, sf::RenderStates){})
{
}

void TimedEvent::update(float dt)
{
    if (!m_triggered) {
        m_triggerTime -= dt;
        if (m_triggerTime <= 0.f) {
            m_triggered = true;
            m_running = true;
            m_onTriggered();
        } else
            m_onWait(dt);
    } else if (m_running) {
        m_duration -= dt;
        if (m_duration <= 0.f) {
            m_running = false;
            m_finished = true;
            m_onFinished();
        } else
            m_onRun(dt);
    }
}

void TimedEvent::onTrigger(std::function<void()> handler)
{
    m_onTriggered = handler;
}

void TimedEvent::run(std::function<void(float)> handler)
{
    m_onRun = handler;
}

void TimedEvent::wait(std::function<void(float)> handler)
{
    m_onWait = handler;
}

void TimedEvent::onFinish(std::function<void()> handler)
{
    m_onFinished = handler;
}

void TimedEvent::onDraw(std::function<void(sf::RenderTarget&, sf::RenderStates)> handler)
{
    m_onDraw = handler;
}

void TimedEvent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    m_onDraw(target, states);
}
