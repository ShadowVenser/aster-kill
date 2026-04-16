#include "OptimisedFilter.h"
#include "Filter.h"

OptimisedFilter::OptimisedFilter(
    World& world,
    std::function<std::span<const int>()> getter
):
    Filter(world),
    _GetFiltered(getter)
{}

std::span<const int> OptimisedFilter::GetView() const {
    return _GetFiltered();
}
