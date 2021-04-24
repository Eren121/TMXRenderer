#pragma once

#include <tuple>

namespace obs
{
    /// Callback for Events
    template<typename... EventType>
    struct Observer : Observer<EventType>...
    {
    };

    template<typename EventType>
    struct Observer<EventType>
    {
    public:
        virtual void receiveEvent(const EventType & eventData) = 0;
    };
}