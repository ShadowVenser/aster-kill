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

    bool _BindFilter(uint64_t mask) override;
    std::span<const int> _Filtered() override;

    std::vector<T> _data;      
    std::vector<int> _sparse;  
    std::vector<int> _dense;   
    
    int _count = 0;            

    int _id;

    void _Resize(const int sparseSize, const int dataSize);

public:
    ComponentStorage(internal::IWorldInternal& w, const int id);

    bool Has(const int e) const override;

    T& Get(const int e);
    T& operator[](const int e);

    T& Add(const int e, const T& value);

    void Remove(const int e) override;

    std::span<const T> All() const;
    std::span<const int> Entities() const override;

    int Count() const override;
    int Id() const override;

};

#endif //COMPONENTSTORAGE_H
