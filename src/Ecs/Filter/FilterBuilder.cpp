#include "FilterBuilder.h"

#include <cstdint>
#include <functional>
#include <memory>
#include <stdexcept>
#include "Filter.h"

#include "../Components/BaseComponentStorage.h"
#include "OptimisedFilter.h"
#include "SparseFilter.h"

FilterBuilder::FilterBuilder(World& world):
    _world(world)
{}

template <typename T>
FilterBuilder& FilterBuilder::With()
{
    int storageId = _world.GetRawStorage<T>()->Id();
    _filterMask |= 1 << storageId;
    return *this; 
}

template <typename T>
FilterBuilder& FilterBuilder::Without()
{
    int storageId = _world.GetRawStorage<T>()->Id();
    _filterMask = _filterMask ? _filterMask : ~_filterMask;
    _filterMask ^= 1 << storageId;
    return *this; 
}

template <typename T>
FilterBuilder& FilterBuilder::OptimisedBy()
{
    #ifdef DEBUG
        if (_optimiser) 
            throw std::runtime_error("Filter already optimised!");
    #endif
    if (!_optimiser)
        _optimiser = _world.GetRawStorage<T>();
    return *this; 
}


std::shared_ptr<Filter> FilterBuilder::Build() const
{
    if (auto filter = _world.GetFilter(_filterMask); filter)
        return filter; 
    if (_optimiser) 
    {
        if (!_optimiser->_BindFilter(_filterMask))
        {
            #ifdef DEBUG
                throw std::runtime_error("Storage already used by another filter");
            #endif
        }
        else
        {
            std::function<std::span<const int>()> getter = [optimiser=_optimiser](){return optimiser->_Filtered();};
            std::shared_ptr<Filter> filter = std::make_shared<OptimisedFilter>(_world, getter);
            _world.AddFilter(_filterMask, filter);
            return filter;
        }
    }
    std::shared_ptr<SparseFilter> filter = std::make_shared<SparseFilter>(_world, _filterMask);
    
    uint64_t mask = _filterMask;
    int id = 0;
    size_t size = 0;
    std::shared_ptr<BaseComponentStorage> storage = nullptr;

    while (mask) 
    {
        id += std::countr_zero(mask);
        if (auto current = _world.GetStorageById(id); !storage || current->Entities().size() < size)
        {
            storage = current;
            size = current->Entities().size();
        }
        mask &= mask - 1;
        id++;
    }

    for (auto e: storage->Entities())
    {
        if ((_world.GetEntityComponents(e) & _filterMask) == _filterMask)
            filter->Add(e);
    }
    
    _world.AddFilter(_filterMask, filter);
    _world.AddListener(_filterMask, filter);
    return filter;
}