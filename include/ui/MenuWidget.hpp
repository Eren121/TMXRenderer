#pragma once

#include "common.hpp"
#include "renderer/SceneManager.hpp"
#include <SFML/Graphics.hpp>

namespace ui
{
    class MenuWidget;

    /// Event called when the player click on an option on a MenuWidget
    struct OnOptionAccept
    {
        MenuWidget &source;
        vec2i choice;
    };

    /// Menu for when the player has to choose something
    /// Like move, ui, etc...
    /// All these ui share the same style
    class MenuWidget : public sf::Drawable,
                       public sf::Transformable,
                       public obs::Subject<OnOptionAccept>
    {
    public:
        /// To make declaration shortcut, and scalar-like.
        /// But an option is only a vec2i.
        using Option = vec2i;

        /// The first option (0, 0) is by default the option currently hovered.
        /// @param optionsCount The count of options in each dimension. Should be >= 1 in each dimension.
        /// @param pos The position of the widget.
        /// @param size The size of the widget.
        MenuWidget(renderer::SceneManager &parent, const vec2i &optionsCount);

        /// Set the text displayed for the option at the specified position
        /// @param pos should be >= 0 in each dimension.
        void setLabel(Option id, const string &label);
        const string& label(Option id) const;

        /// Change the currently hovered option
        void setHovered(Option id);

        /// @returns true If a button was clicked
        bool handleCommand(Command command);

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates parent) const override;

    private:
        renderer::SceneManager &m_parent;
        vec2i m_optionsCount;
        Option m_hoveredOption;
        std::map<Option, string, vec_comp> m_labels;

        inline static const string DEF_LABEL { "?" };
    };
}


