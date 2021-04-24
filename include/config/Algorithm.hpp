#pragma once

#include <algorithm>
#include <vector>

template<typename T, typename Predicate>
std::vector<T> filter(const std::vector<T> &source, Predicate predicate)
{
    using std::begin;
    using std::end;

    std::vector<T> filtered;

    copy_if(
        begin(source), end(source),
        back_inserter(filtered),
        predicate
    );

    return filtered;
}

template<typename Container>
decltype(auto) randomElement(const Container &container)
{
    return container[rand() % container.size()];
}