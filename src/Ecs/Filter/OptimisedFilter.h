#include <functional>
#include <span>
#include "Filter.h"

class OptimisedFilter final: public Filter 
{
    public:
        OptimisedFilter(
            World& world,
            std::function<std::span<const int>()> getter
        );

        std::span<const int> GetView() const override;

    private:
        std::function<std::span<const int>()> _GetFiltered;
};