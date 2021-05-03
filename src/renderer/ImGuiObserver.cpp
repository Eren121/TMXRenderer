#include "renderer/ImGuiObserver.hpp"
#include <imgui-SFML.h>
#include <imgui.h>

namespace renderer
{
    ImGuiObserver::ImGuiObserver(SceneManager &parent)
    {
        // Attach events

        parent.attachObserver<OnInputEvent>(*this);
        parent.attachObserver<OnUpdate>(*this);
        parent.attachObserver<OnRender>(*this);
        parent.attachObserver<OnGameOpen>(*this);
        parent.attachObserver<OnGameClose>(*this);
    }

    void ImGuiObserver::receiveEvent(const OnInputEvent &eventData)
    {
        ImGui::SFML::ProcessEvent(eventData.e);
    }

    void ImGuiObserver::receiveEvent(const OnUpdate &event)
    {
        ImGui::SFML::Update(event.source.window(), event.delta);
    }

    void ImGuiObserver::receiveEvent(const OnRender &event)
    {
        const auto &config = event.source.config();

        // Render Imgui window only if in debug mode
        if (config.isDebugMode())
        {
            if(ImGui::Begin("Debug Window"))
            {
                // Global config
                event.source.config().showImguiDebugWindow();

                // Render all scene debug information
                for (auto &scene : event.source.scenes())
                {
                    scene->showImguiDebugWindow();
                }
            }
            ImGui::End();
        }

        // Imgui notification for rendering
        ImGui::SFML::Render(event.source.window());
    }

    void ImGuiObserver::receiveEvent(const OnGameOpen &event)
    {
        ImGui::SFML::Init(event.source.window());

        if (event.source.config().noImguiIni())
        {
            // Set to nullptr to not use imgui.ini
            ImGui::GetIO().IniFilename = nullptr;
        }
    }

    void ImGuiObserver::receiveEvent(const OnGameClose &eventData)
    {
        ImGui::SFML::Shutdown();
    }
}