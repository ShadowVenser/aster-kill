#include "ComponentStorage.hpp"

template <typename T>
ComponentStorage<T>::ComponentStorage(internal::IWorldInternal& w, const int id): 
    _world(w), _id(id)
{ }

template <typename T>
void ComponentStorage<T>::_Resize(const int sparseSize, const int dataSize)
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

template <typename T>
T& ComponentStorage<T>::Add(const int e, const T& value) 
{
    #if DEBUG
        if (!_world.IsEntityAlive(e))
            throw std::runtime_error("Try to add to dead entity!");
    #endif

    _Resize((e / 64 + 1) * 64, _data.size() == _count + 1 ? _data.size() + 64 : _data.size());
    
    if (_isBinded && (_world.GetEntityComponents(e) & _filterMask) == _filterMask) {
        _data[_count] = _data[_matchedCount];
        _dense[_count] = _dense[_matchedCount];
        _sparse[_dense[_matchedCount]] = _count;

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

template <typename T>
void ComponentStorage<T>::Remove(const int e) 
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

        --_count;
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

template <typename T>
bool ComponentStorage<T>::Has(const int e) const
{
    return _sparse[e] != -1;
}

template <typename T>
T& ComponentStorage<T>::Get(const int e)
{
    return _data[_sparse[e]];
}

template <typename T>
T& ComponentStorage<T>::operator[](const int e)
{
    return _data[_sparse[e]];
}

template <typename T>
std::span<const T> ComponentStorage<T>::All() const
{
    std::span<const T> view = _data;
    return view.first(_count);
}

template <typename T>
std::span<const int> ComponentStorage<T>::Entities() const
{
    std::span<const int> view = _dense;
    return view.first(_count);
}

template <typename T>
int ComponentStorage<T>::Count() const
{
    return _count;
}


template <typename T>
int ComponentStorage<T>::Id() const
{
    return _id;
}

template <typename T>
bool ComponentStorage<T>::_BindFilter(uint64_t mask)
{
    if (_isBinded) return false;

    _isBinded = true;
    _filterMask = mask;
    
    std::vector<T> tmpData(_count);  
    std::vector<int> tmpDense(_count);   

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
    for (int i = 0; i < tmpData.size(); ++i) 
    {
        _data[_matchedCount + i] = tmpData[i];
        _dense[_matchedCount + i] = tmpDense[i];
        _sparse[tmpDense[i]] = _matchedCount + i;
    }
}

template <typename T>
std::span<const int> ComponentStorage<T>::_Filtered() 
{
    std::span<int> view = _dense;
    return view.first(_matchedCount);
}
