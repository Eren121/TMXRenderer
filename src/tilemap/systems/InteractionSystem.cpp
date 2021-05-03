#include "tilemap/systems/InteractionSystem.hpp"
#include "tilemap/Engine.hpp"
#include "ui/DialogScene.hpp"
#include "pokemon/Trainer.hpp"
#include "battle/BattleScene.hpp"

namespace Tm
{
    void InteractionSystem::update()
    {
        if (!hasFocus() || !m_sceneManager.controller().isJustPressed(Command::A))
        {
            return;
        }

        auto &region = m_engine.region();
        auto &registry = region.registry();
        auto entity = region.player();
        const auto &playerPos = registry.get<Position>(entity);
        auto &character = registry.get<Character>(entity);

        const auto targetPos = playerPos + facingVector(character.facingDirection);

        auto view = registry.view<Position, Dialog>();
        for (auto[entity, pos, dialog] : view.each())
        {
            // For capture (cannot capture from structured binding; it does introduce a name but not a variable)
            const auto e = entity;

            if (pos == targetPos)
            {
                std::string text;

                if (auto chr = registry.try_get<Character>(entity); chr)
                {
                    text += chr->name;
                    text += ": ";
                }

                text += dialog.text;

                const auto dialogMenu = new ui::DialogScene(m_sceneManager, text);
                m_sceneManager.pushScene(dialogMenu);

                // Start battle at the end of the dialog if it's a trainer
                if (registry.try_get<Pkm::Trainer>(entity))
                {
                    dialogMenu->attachObserver([&, e](const renderer::OnSceneClose &) {

                        if (registry.try_get<Pkm::Trainer>(e))
                        {
                            m_sceneManager.pushScene(new Btl::BattleScene(m_sceneManager, registry, e));
                        }
                    });
                }

                // The interacted component was found, stop here
                // If there are multiple entities, they are at the same location that's unlikely
                break;
            }
        }
    }
}
