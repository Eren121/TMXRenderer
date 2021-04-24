#pragma once

#include "Observer.hpp"

namespace obs
{
    /**
     * Subject::attachObserver() is overloaded with this class to allow using lambda as event handlers.
     * @tparam Lambda Deduced Parameter of the constructor.
     */
    template<typename EventClass, typename Lambda>
    struct LambdaObserver : Observer<EventClass>
    {
    public:
        LambdaObserver(Lambda&& lambda)
            : m_lambda(std::forward<Lambda>(lambda))
        {
        }

        void receiveEvent(const EventClass &eventData) override
        {
            m_lambda(eventData);

            // !!
            // The subject store a list of pointer to observers
            // And don't delete it when callback is called, so delete it.
            delete this;
        }

    private:
        Lambda m_lambda;
    };
}