#include "renderer/ImGuiObserver.hpp"
#include "imgui-SFML.h"

namespace renderer
{
    ImGuiObserver::ImGuiObserver(SceneManager &parent)
    {
        parent.attachObserver<OnInputEvent>(*this);
        parent.attachObserver<OnUpdate>(*this);
        parent.attachObserver<OnRender>(*this);
    }

    void ImGuiObserver::receiveEvent(const OnInputEvent &eventData)
    {
        ImGui::SFML::ProcessEvent(eventData.e);
    }

    void ImGuiObserver::receiveEvent(const OnUpdate &eventData)
    {
        ImGui::SFML::Update(eventData.source.window(), eventData.delta);
    }

    void ImGuiObserver::receiveEvent(const OnRender &eventData)
    {
        ImGui::SFML::Render(eventData.source.window());
    }

    void ImGuiObserver::receiveEvent(const OnGameOpen &eventData)
    {
        ImGui::SFML::Init(eventData.source.window());
    }

    void ImGuiObserver::receiveEvent(const OnGameClose &eventData)
    {
        ImGui::SFML::Shutdown();
    }
}