#include <vector>
#include "Filter.h"

class SparseFilter: public Filter {
public:
    SparseFilter(World& world, uint64_t filterMask);
    
    std::span<const int> GetView() const override;
    uint64_t GetMask() const;

    void Add(const int e);
    void Remove(const int e);

    private:
    uint64_t _filterMask;

    int _count;
    std::vector<int> _sparse;
    std::vector<int> _dense;

    void _Resize(const int sparseSize, const int dataSize);
};
