#include "OptimisedFilter.h"
#include <cstdint>
#include "Filter.h"

OptimisedFilter::OptimisedFilter(
    World& world,
    uint64_t mask,
    std::function<std::span<const int>()> getter,
    std::function<void(int)> add,
    std::function<void(int)> remove
):
    Filter(world, mask),
    _GetFiltered(getter),
    _AddToFilter(add),
    _RemoveFromFilter(remove)
{}

OptimisedFilter::OptimisedFilter(
    World& world,
    uint64_t mask,
    std::function<std::span<const int>()> getter
):
    Filter(world, mask),
    _GetFiltered(getter),
    _AddToFilter([](int){}),
    _RemoveFromFilter([](int){})
{}

std::span<const int> OptimisedFilter::GetView() const 
{
    return _GetFiltered();
}

void OptimisedFilter::Add(const int e)
{
    _AddToFilter(e);
}

void OptimisedFilter::Remove(const int e)
{
    _RemoveFromFilter(e);
}
