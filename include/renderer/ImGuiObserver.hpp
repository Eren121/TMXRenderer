#pragma once

#include "SceneManager.hpp"

namespace renderer
{
    /// Observer of SceneManager that integrate ImGui.
    class ImGuiObserver
        : public obs::Observer<OnInputEvent, OnUpdate, OnRender, OnGameOpen, OnGameClose>
    {
    public:
        ImGuiObserver(SceneManager &parent);

    private:
        void receiveEvent(const OnInputEvent &eventData) override;
        void receiveEvent(const OnUpdate &event) override;
        void receiveEvent(const OnRender &event) override;
        void receiveEvent(const OnGameOpen &event) override;
        void receiveEvent(const OnGameClose &eventData) override;
    };
}