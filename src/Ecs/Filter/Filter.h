#ifndef FILTER_H
#define FILTER_H

#include <cstdint>
#include <memory>
#include <ranges>
#include <utility>
#include <vector>

#include "../Components/BaseComponentStorage.h"
#include "../World/World.h"

class Filter {
    World& _world;
    uint64_t _mask;

public:
    Filter(World& world, uint64_t mask): _world(world), _mask(mask) {}

    virtual std::span<const int> GetView() const = 0;

    virtual void Add(const int e) = 0;
    virtual void Remove(const int e) = 0;

    uint64_t GetMask() const { return _mask; }

    virtual ~Filter() = default;
};

#endif //FILTER_H
