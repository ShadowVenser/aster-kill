#include <functional>
#include <span>
#include "Filter.h"

class OptimisedFilter final: public Filter 
{

public:
    OptimisedFilter(
        World& world,
        uint64_t mask,
        std::function<std::span<const int>()> getter,
        std::function<void(int)> add,
        std::function<void(int)> remove
    );

    std::span<const int> GetView() const override;
    void Add(const int e) override;
    void Remove(const int e) override;

private:
    std::function<std::span<const int>()> _GetFiltered;
    std::function<void(int)> _AddToFilter;
    std::function<void(int)> _RemoveFromFilter;

};