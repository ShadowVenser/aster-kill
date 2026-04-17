#include "SparseFilter.h"
#include "Filter.h"

SparseFilter::SparseFilter(World& world, uint64_t filterMask):
    Filter(world, filterMask) 
{}

std::span<const int> SparseFilter::GetView() const 
{
    std::span<const int> view = _dense;
    return view.first(_count);
}

void SparseFilter::_Resize(const int sparseSize, const int denseSize)
{
    int oldSparseSize = _sparse.size();
    if (oldSparseSize < sparseSize) 
    {
        _sparse.resize(sparseSize);
        std::fill_n(_sparse.data() + oldSparseSize, sparseSize - oldSparseSize, -1);
    }
    int oldDenseSize = _dense.size();
    if (oldDenseSize < denseSize) 
    {
        _dense.resize(denseSize);
        std::fill_n(_dense.data() + oldDenseSize, denseSize - oldDenseSize, -1);
    }
}

void SparseFilter::Add(const int e) 
{
    _Resize((e / 64 + 1) * 64, _dense.size() <= static_cast<size_t>(_count + 1) ? _dense.size() + 64 : _dense.size());

    _dense[_count] = e;
    _sparse[e] = _count;
    _count++;
    
}

void SparseFilter::Remove(const int e) 
{
    int pos = _sparse[e];

    _dense[pos] = _dense[--_count];
    _sparse[_dense[pos]] = pos;
    _sparse[e] = -1;    
    
}