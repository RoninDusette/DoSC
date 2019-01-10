#include "resettabletimer.h"

#define DEFAULT_TIMEOUT_MS 500

void ResettableTimer::RunTimer()
{
    tMutexLock lock(m_resetMutex);

    while (m_running == true)
    {
        if (m_resetCondition.wait_for(lock, m_timeout) ==
            std::cv_status::timeout)
        {
            break;
        }
    }
}

void ResettableTimer::Start()
{
    if (m_running == true || m_thread.joinable())
    {
        m_running = false;
        Stop();
    }

    m_running = true;
    m_thread = std::thread(&ResettableTimer::RunTimer, this);
}

void ResettableTimer::Stop()
{
    if (m_thread.joinable() == true)
    {
        m_running = false;
        Reset();
        m_thread.join();
    }
}

void ResettableTimer::Reset()
{
    m_resetCondition.notify_all();
}

void ResettableTimer::SetTimeout(std::chrono::milliseconds timeout)
{
    m_timeout = timeout;
}

void ResettableTimer::SetCallback(tTimerCb callback)
{
    m_timerCallback = callback;
}

ResettableTimer::ResettableTimer()
{
    m_timeout = std::chrono::milliseconds(DEFAULT_TIMEOUT_MS);
    m_timerCallback = nullptr;
}

ResettableTimer::~ResettableTimer()
{
    Stop();
}
