#pragma once

#include "Observer.hpp"

namespace obs
{
    /**
     * Subject::attachObserver() is overloaded with this class to allow using lambda as event handlers.
     * @tparam Lambda Deduced Parameter of the constructor.
     */
    template<typename EventClass, typename Lambda>
    class LambdaObserver final : public Observer<EventClass>
    {
    public:
        LambdaObserver(Lambda&& lambda)
            : m_lambda(std::forward<Lambda>(lambda))
        {
        }

    protected:
        void onDetach(const Subject <EventClass> &source) override
        {
            // Since the lambda depends only from the Subject, it should deallocate itself
            delete this;
        }

        /// Care because the lambda will receive all events until the subject is destroyed
        void receiveEvent(const EventClass &eventData) override
        {
            m_lambda(eventData);
        }

    private:
        Lambda m_lambda;
    };
}