#pragma once

#include "Connection.hpp"
#include "Observer.hpp"
#include "LambdaObserver.hpp"
#include <map>
#include <memory>

namespace obs
{
    /// Subject that emit events.
    /// Variadic template is only to avoid repeating parent class.
    /// Permit also the "using" clause to allow to disambiguiate call transparently.
    /// Usage example:
    /// @code
    /// struct A : obs::Subject<I, J> {};
    /// // Same as
    /// struct A : obs::Subject<I>, obs::Subject<J> {};
    /// @endcode
    template<typename... EventType>
    class Subject : public Subject<EventType> ...
    {
    public:
        using Subject<EventType>::notify...;
        using Subject<EventType>::attachObserver...;
        using Subject<EventType>::detachObserver...;

        /// Use it to subscribe when there is an ambiguity
        /// When the observer inherit from multiple observers
        /// That the subject emits
        template<typename E>
        void attachObserver(Observer<E> &t)
        {
            attachObserver(t);
        }
    };

    template<typename EventType>
    class Subject<EventType>
    {
    public:
        using Obs = Observer<EventType>;

        Subject() = default;
        Subject(const Subject&) = delete;
        Subject(Subject&&) = delete;
        Subject& operator=(Subject&&) = delete;
        Subject& operator=(const Subject&) = delete;

        /// All remaining observers will have onDetach() called
        virtual ~Subject()
        {
            removeExpired();

            // Notify the remaining observers that the subject is getting destroyed,
            // so the observers will be indirectly detached (no further observation will be possible)
            // Event if detachObserver() is not called explicitly
            // Can't call detachObserver() because it would erase while iterating the map
            // Thanks to that autoregistrated lambdas can delete itselves
            for (auto &[obs, conn] : m_connections)
            {
                obs->onDetach(*this);
            }
        }

        void attachObserver(Obs &observer)
        {
            auto connection = std::make_shared<Connection>();

            m_connections[&observer] = connection;
            observer.m_connection = connection;
        }

        /// This function suits better than Obs even if the class is inheriting from Obs
        /// see https://stackoverflow.com/questions/67221799/wrong-function-resolution-in-template-when-using-inheritance
        /// That's why the SFINAE
        template<
            typename Lambda,
            typename SFINAE = std::enable_if_t<!std::is_base_of_v<Obs, std::decay_t<Lambda>>>>
        void attachObserver(Lambda &&lambda)
        {
            const auto observer = new LambdaObserver<EventType, Lambda>(std::forward<Lambda>(lambda));
            this->attachObserver(*observer);
        }

        void detachObserver(Obs &observer)
        {
            if(m_connections.contains(&observer))
            {
                m_connections.at(&observer).onDetach(*this);
            }

            m_connections.erase(&observer);
        }

    protected:
        /// Removed all observers that do not exists any more
        void removeExpired()
        {
            auto it = m_connections.begin();
            auto end = m_connections.end();
            while (it != end)
            {
                const auto &connection = it->second;
                if (connection.expired())
                {
                    it = m_connections.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        void notify(const EventType &eventData = {})
        {
            this->removeExpired();

            for (auto &[obs, conn] : m_connections)
            {
                obs->receiveEvent(eventData);
            }
        }

    private:
        std::map<Obs *, std::weak_ptr<Connection>> m_connections;
    };
}