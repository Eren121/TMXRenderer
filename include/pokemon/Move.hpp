#pragma once

#include "common.hpp"

namespace Pkm
{
    /**
     * @brief An attack.
     *
     * A pokemon has multiple moves, and a move has:
     * - a name
     * - damage count: power
     * - a precision: accuracy
     * - a max use count (pp= power points): maxPP
     *
     * @remarks The same move is shared between all pokemons.
     * @remarks The current pp is stored in the Pokemon component, not here.
     * @remarks This class is not a component because the database of moves is loaded once and read-only.
     */
    class Move
    {
    public:
        const string &name() const { return m_name; }

        int maxPP() const { return m_maxPP; }

        int power() const { return m_power; }

        int accuracy() const { return m_accuracy; }

        void setName(const string &name) { m_name = name; }

        void setMaxPP(int maxPP) { m_maxPP = max(0, maxPP); }

        void setPower(int power) { m_power = max(0, power); }

        void setAccuracy(int accuracy) { m_accuracy = max(0, accuracy); }

    private:
        string m_name;
        int m_maxPP;
        int m_power;
        int m_accuracy;
    };
}