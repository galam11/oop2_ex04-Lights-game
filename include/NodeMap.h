#pragma once
#include <unordered_map>
#include <functional> 
#include "LightNode.h"

struct VectorHash {
    template <typename T>
    std::size_t operator()(const sf::Vector2<T>& v) const
    {
        std::size_t h1 = std::hash<T>{}(v.x);
        std::size_t h2 = std::hash<T>{}(v.y);
        return h1 ^ (h2 << 1);
    }
};

using NodeMap = std::unordered_map<sf::Vector2i, LightNode, VectorHash>;