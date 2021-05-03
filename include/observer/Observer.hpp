#pragma once

#include "Connection.hpp"
#include <tuple>
#include <memory>

namespace obs
{
    template<typename... EventType>
    class Subject;

    /// Callback for Events
    template<typename... EventType>
    class Observer : public Observer<EventType> ...
    {
    };

    template<typename EventType>
    class Observer<EventType>
    {
    public:
        virtual ~Observer() = default;

    protected:
        virtual void receiveEvent(const EventType &) = 0;

        virtual void onDetach(const Subject<EventType> &) {}

    private:
        std::shared_ptr<Connection> m_connection;

        friend Subject<EventType>;
    };
}