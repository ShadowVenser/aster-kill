#ifndef COMPONENTSTORAGE_H
#define COMPONENTSTORAGE_H

#include <algorithm>
#include <memory>
#include <vector>
#include <stdexcept>
#include <cstdint>

#include "BaseComponentStorage.h"
#include "../World/IWorldInternal.h"

template <typename T>
class ComponentStorage final : public BaseComponentStorage {
    internal::IWorldInternal& _world;

    bool _isBinded {false};
    uint64_t _filterMask {0};
    int _matchedCount {0};

    bool _BindFilter(uint64_t mask) override
    {
        if (_isBinded) return false;

        _isBinded = true;
        _filterMask = mask;
        
        std::vector<T> tmpData;  
        std::vector<int> tmpDense;
        
        tmpData.reserve(_count);
        tmpDense.reserve(_count);

        for (int i = 0; i < _count; ++i) {
            if ((_world.GetEntityComponents(_dense[i]) & mask) == mask)
            {
                if (_matchedCount != i) 
                {
                    _data[_matchedCount] = _data[i];
                    _dense[_matchedCount] = _dense[i];
                    _sparse[_dense[i]] = _matchedCount;
                }
                ++_matchedCount;
            }
            else 
            {
                tmpData.push_back(_data[i]);
                tmpDense.push_back(_dense[i]);
            }
        }
        for (size_t i = 0; i < tmpData.size(); ++i) 
        {
            _data[_matchedCount + i] = tmpData[i];
            _dense[_matchedCount + i] = tmpDense[i];
            _sparse[tmpDense[i]] = _matchedCount + i;
        }
        return true;
    }

    std::span<const int> _Filtered() override
    {
        std::span<int> view = _dense;
        return view.first(_matchedCount);
    }

    void _AddToFilter(int e) override
    {
        int pos = _sparse[e];
        T tmp = _data[pos];

        _data[pos] = _data[_matchedCount];
        _dense[pos] = _dense[_matchedCount];
        _sparse[_dense[_matchedCount]] = pos;

        _data[_matchedCount] = tmp;
        _dense[_matchedCount] = e;
        _sparse[e] = _matchedCount;

        ++_matchedCount;
    }

    void _RemoveFromFilter(int e) override
    {
        int pos = _sparse[e];
        T tmp = _data[pos];

        --_matchedCount;

        _data[pos] = _data[_matchedCount];
        _dense[pos] = _dense[_matchedCount];
        _sparse[_dense[_matchedCount]] = pos;

        _data[_matchedCount] = tmp;
        _dense[_matchedCount] = e;
        _sparse[e] = _matchedCount;
    }

    std::vector<T> _data;      
    std::vector<int> _sparse;  
    std::vector<int> _dense;   
    
    int _count = 0;            

    int _id;

    void _Resize(const int sparseSize, const int dataSize)
    {
        int oldSparseSize = _sparse.size();
        if (oldSparseSize < sparseSize) 
        {
            _sparse.resize(sparseSize);
            std::fill_n(_sparse.data() + oldSparseSize, sparseSize - oldSparseSize, -1);
        }
        int oldDataSize = _dense.size();
        if (oldDataSize < dataSize) 
        {
            _dense.resize(dataSize);
            _data.resize(dataSize);
            std::fill_n(_dense.data() + oldDataSize, dataSize - oldDataSize, -1);
        }
    }

public:
    ComponentStorage(internal::IWorldInternal& w, const int id): 
        _world(w), _id(id)
    { }

    bool Has(const int e) const override
    {
        return _sparse[e] != -1;
    }

    T& Get(const int e)
    {
        return _data[_sparse[e]];
    }

    T& operator[](const int e)
    {
        return _data[_sparse[e]];
    }

    T& Add(const int e, const T& value)
    {
        #if DEBUG
            if (!_world.IsEntityAlive(e))
                throw std::runtime_error("Try to add to dead entity!");
        #endif

        _Resize((e / 64 + 1) * 64, _data.size() <= (size_t)(_count + 1) ? _data.size() + 64 : _data.size());
        
        if (_isBinded && ((_world.GetEntityComponents(e) | 1 << _id)& _filterMask) == _filterMask) {
            if (_matchedCount < _count) 
            {
                _data[_count] = _data[_matchedCount];
                _dense[_count] = _dense[_matchedCount];
                _sparse[_dense[_matchedCount]] = _count;
            }

            _data[_matchedCount] = value;
            _dense[_matchedCount] = e;
            _sparse[e] = _matchedCount;

            ++_matchedCount; ++_count;

            _world.EntityComponentsChanged(e, _id, true);
            return _data[_matchedCount - 1];
        }

        _data[_count] = value;
        _dense[_count] = e;
        _sparse[e] = _count;
        _count++;
        
        _world.EntityComponentsChanged(e, _id, true);
        return _data[_count - 1];
    }

    void Remove(const int e) override
    {
        #if DEBUG
            if (!_world.IsEntityAlive(e))
                throw std::runtime_error("Try to remove from dead entity!");
        #endif

        int pos = _sparse[e];

        if (pos < _matchedCount) {
            _data[pos] = _data[--_matchedCount];
            _dense[pos] = _dense[_matchedCount];
            _sparse[_dense[pos]] = pos;

            _data[_matchedCount] = _data[--_count];
            _dense[_matchedCount] = _dense[_count];
            _sparse[_dense[_matchedCount]] = _matchedCount;

            _sparse[e] = -1;
        } 
        else 
        {
            _data[pos] = _data[--_count];
            _dense[pos] = _dense[_count];
            _sparse[_dense[pos]] = pos;

            _sparse[e] = -1;    
        }

        _world.EntityComponentsChanged(e, _id, false);
    }

    std::span<const T> All() const
    {
        std::span<const T> view = _data;
        return view.first(_count);
    }

    std::span<const int> Entities() const override
    {
        std::span<const int> view = _dense;
        return view.first(_count);
    }

    int Count() const override
    {
        return _count;
    }


    int Id() const override
    {
        return _id;
    }

};

#endif //COMPONENTSTORAGE_H
