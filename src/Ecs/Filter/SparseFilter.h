#pragma once

#include <vector>
#include "Filter.h"

class SparseFilter: public Filter {
public:
    SparseFilter(World& world, uint64_t filterMask);
    
    std::span<const int> GetView() const override;

    void Add(const int e) override;
    void Remove(const int e) override;

private:

    int _count;
    std::vector<int> _sparse;
    std::vector<int> _dense;

    void _Resize(const int sparseSize, const int dataSize);
};
