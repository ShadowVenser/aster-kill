#ifndef WORLD_H
#define WORLD_H

#include <cstdint>
#include <unordered_map>
#include <vector>
#include <memory>

#include "IWorldInternal.h"
#include "../Entity/EntityId.h"
#include "../Components/ComponentStorage.hpp"

class Filter;
class SparseFilter;

class World final : public internal::IWorldInternal {
    
    const int DefaultEntitiesCapacity = 64;

    std::vector<EntityId> _entities;
    std::vector<int> _freeEntities;

    std::unordered_map<uint64_t, std::shared_ptr<Filter>> _worldFilters;
    std::unordered_map<int, std::vector<std::shared_ptr<SparseFilter>>> _listeners;

    std::unordered_map<size_t, std::shared_ptr<BaseComponentStorage>> _componentStoragesHash;
    std::vector<std::shared_ptr<BaseComponentStorage>> _componentStorages;

    int _storagesCount = 0;

public:
    World();

    int CreateEntity();
    void RemoveEntity(int e);

    EntityId GetPackedEntity(int e) const;
    bool UnpackEntity(const EntityId& eId, int& e) const;

    uint64_t GetEntityComponents(int e) override;
    bool IsEntityAlive(int e) const override;
    void EntityComponentsChanged(int e, int storageId, bool added) override;

    std::shared_ptr<Filter> GetFilter(uint64_t filterMask);
    void AddFilter(uint64_t filterMask, std::shared_ptr<Filter> filter);
    void AddListener(uint64_t filterMask, std::shared_ptr<SparseFilter> filter);

    template <typename T>
    std::shared_ptr<ComponentStorage<T>> GetRawStorage();

    template <typename T>
    ComponentStorage<T>& GetStorage();

    std::shared_ptr<BaseComponentStorage> GetStorageById(int storageId);

};

#endif //WORLD_H
