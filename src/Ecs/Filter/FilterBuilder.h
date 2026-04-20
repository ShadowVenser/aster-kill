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
    FilterBuilder& With()
    {
        int storageId = _world.GetRawStorage<T>()->Id();
        _filterMask |= 1 << storageId;
        return *this; 
    }

    template<typename T>
    FilterBuilder& OptimisedBy()
    {
        #ifdef DEBUG
            if (_optimiser) 
                throw std::runtime_error("Filter already optimised!");
        #endif
        if (!_optimiser)
            _optimiser = _world.GetRawStorage<T>();
        return *this; 
    }

    std::shared_ptr<Filter> Build() const;
};

#endif //FILTERBUILDER_H
