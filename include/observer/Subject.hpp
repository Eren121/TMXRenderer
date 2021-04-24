#pragma once

#include "Observer.hpp"
#include "LambdaObserver.hpp"
#include <set>

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
    struct Subject : public Subject<EventType> ...
    {
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
    struct Subject<EventType>
    {
    public:
        using Obs = Observer<EventType>;

        Subject() = default;
        virtual ~Subject() = default;

        void attachObserver(Obs &observer)
        {
            m_observers.insert(&observer);
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
            m_observers.insert(observer);
        }

        void detachObserver(Obs &observer)
        {
            m_observers.erase(&observer);
        }

        void notify(const EventType &eventData = {}) const
        {
            for (auto observer : m_observers)
            {
                observer->receiveEvent(eventData);
            }
        }

    private:
        std::set<Obs *> m_observers;
    };
}