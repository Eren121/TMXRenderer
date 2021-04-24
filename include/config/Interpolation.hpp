#pragma once

namespace interpolation
{
    /// Between 0.0 and 1.0
    using Percent = float;

    constexpr Percent percentMax(1.0f);

    template<typename T, typename TConvertible>
    T linear(const TConvertible& empty, const TConvertible& full, Percent percent)
    {
        return T(empty) * (percentMax - percent) + T(full) * percent;
    }
}