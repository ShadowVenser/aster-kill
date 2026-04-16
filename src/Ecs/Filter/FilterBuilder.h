#ifndef FILTERBUILDER_H
#define FILTERBUILDER_H

#include <memory>
#include "Filter.h"
#include "../World/World.h"

class FilterBuilder
{
    World& _world;
    uint64_t _filterMask = 0l;
    std::shared_ptr<BaseComponentStorage> _optimiser = nullptr;

public:
    FilterBuilder(World& world);

    template <typename T>
    FilterBuilder& With();

    template<typename T>
    FilterBuilder& Without();

    template<typename T>
    FilterBuilder& OptimisedBy();

    std::shared_ptr<Filter> Build() const;
};

#endif //FILTERBUILDER_H
