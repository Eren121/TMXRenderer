#include "ui/MenuWidget.hpp"
#include "renderer/ImGui.hpp"
#include <SFML/Math.hpp>

using namespace sf;
using namespace std;

namespace ui
{
    MenuWidget::MenuWidget(renderer::SceneManager &parent, const vec2i &optionsCount)
        : m_parent(parent),
          m_optionsCount(optionsCount),
          m_hoveredOption(0, 0)
    {
        assert(m_optionsCount.x >= 1 && m_optionsCount.y >= 1); // Check there is atleast one option
    }

    vec2f getMatrixScale(const sf::Transform &t)
    {
        auto m = t.getMatrix();
        auto a = m[0], e = m[1], i = m[2];
        auto b = m[4], f = m[5], j = m[6];
        auto c = m[8], g = m[9], k = m[10]; // Z unused

        auto x = sqrt(a * a + e * e + i * i);
        auto y = sqrt(b * b + f * f + j * j);
        return {x, y};
    }

    void MenuWidget::draw(RenderTarget &target, RenderStates parent) const
    {
        // Divide the space in equals size
        // And render the centered label
        // Add a distinction if the label is hovered

        const auto transform = parent.transform * getTransform();
        RectangleShape background({1.0f, 1.0f});
        background.setFillColor(Color::Yellow);
        target.draw(background, transform);

        for (int x = 0; x < m_optionsCount.x; ++x)
        {
            for (int y = 0; y < m_optionsCount.y; ++y)
            {
                const Option id(x, y);
                auto label = this->label(id);

                if (id == m_hoveredOption)
                {
                    label = "> " + label;
                }

                Text text(label, m_parent.font(), m_parent.charSize());
                //text.setPosition(vec2f(id) / vec2f(m_optionsCount));
                text.setFillColor(Color::Red);

                // Make that the text always has the font size in pixel
                // Independantly from every transformation
                sf::Transform adjust;
                adjust.scale(1.0f / getMatrixScale(transform));

                // Move the text inside each option
                // the translation is relative to the background, so 0.5f = 50%
                sf::Transform pos;
                pos.translate(vec2f(id) / vec2f(m_optionsCount));

                target.draw(text, transform * pos * adjust);
            }
        }
    }

    void MenuWidget::setLabel(Option id, const string &label)
    {
        assert(isInsideRect(m_optionsCount, id));
        m_labels[id] = label;
    }

    const string &MenuWidget::label(Option id) const
    {
        assert(isInsideRect(m_optionsCount, id));

        auto it = m_labels.find(id);
        if (it == m_labels.end())
        {
            return DEF_LABEL;
        }
        else
        {
            return it->second;
        }
    }

    void MenuWidget::setHovered(Option id)
    {
        assert(isInsideRect(m_optionsCount, id));
        m_hoveredOption = id;
    }

    void MenuWidget::handleCommand(Command command)
    {
        vec2i direction;
        if (getInputDirection(command, direction))
        {
            // Move option
            m_hoveredOption += direction;

            // Don't go outside bounds
            m_hoveredOption = clamp(m_hoveredOption, {0, 0}, m_optionsCount - 1);
        }
        else if(command == Command::A)
        {
            notify(OnOptionAccept{
                .source = *this,
                .choice = m_hoveredOption
            });
        }
    }
}