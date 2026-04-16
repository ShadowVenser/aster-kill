#ifndef FILTER_H
#define FILTER_H

#include <memory>
#include <ranges>
#include <utility>
#include <vector>

#include "../Components/BaseComponentStorage.h"
#include "../World/World.h"

class Filter {
    World& _world;

public:
    Filter(World& world);

    virtual std::span<const int> GetView() const = 0;

    virtual ~Filter() = default;
};

#endif //FILTER_H
