#include "tilemap/Components.hpp"
#include "tilemap/LayerOfObjects.hpp"
#include "tilemap/Engine.hpp"

using namespace sf;

namespace Tm
{
    LayerOfObjects::LayerOfObjects(Region &region)
        : Layer(region.size()),
          m_registry(region.registry())
    {
        m_type = tmx::Layer::Type::Object;
    }

    bool Tm::LayerOfObjects::canMoveTo(const vec2i &pos) const
    {
        return isTileEmpty(pos);
    }

    void LayerOfObjects::render(RenderTarget &target, TileRenderer &renderer, const IntRect &bounds,
                                const Transform &parentTransform) const
    {
        auto &registry = m_registry;

        for (auto entity : m_entities)
        {
            const auto &sprite_comp = registry.try_get<Tm::Sprite>(entity);

            // Check the entity has a sprite component
            // That is it is renderable
            if (sprite_comp)
            {
                const auto &pos = m_engine->movementSystem().getInterpolatedPosition(entity);
                const auto &character = registry.try_get<Tm::Character>(entity);
                const auto &moving = registry.try_get<Tm::IsMoving>(entity);

                // Default direction when the entity is non-orientable
                Direction direction = Direction::DOWN;

                // The entity is a character
                // It also has a facing direction and can be rendered accordingly
                if (character)
                {
                    direction = character->facingDirection;
                }

                // Get the GID of the sprite when it's moving or not and relative to it's direction
                Tm::GID gid = sprite_comp->gid(direction, moving != nullptr);
                const auto &type = renderer.updateAnimation(gid, m_registry, entity);

                // If the tile type is valid
                if (type)
                {
                    // No rotation, the tileset should contain each tile in each direction if needed
                    Transform model;

                    // Move into the tile coordinates
                    model = Transform().translate(pos) * model;

                    Transform combinedTransform = parentTransform * model;
                    renderer.drawTile(target, *type, combinedTransform);
                }
            }
        }
    }

    void LayerOfObjects::addEntity(entt::entity entity)
    {
        m_entities.push_back(entity);
    }

    bool LayerOfObjects::isTileEmpty(const Vector2i &pos) const
    {
        // Can move only if no other entity is at the same position
        // <=> all entities are on a different position
        return std::all_of(
            m_entities.begin(), m_entities.end(),
            [&](auto e) {
                const Position *entityPos = m_registry.try_get<Position>(e);
                return !entityPos || *entityPos != pos;
            }
        );
    }
}