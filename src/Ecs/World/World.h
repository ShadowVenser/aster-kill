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

class World final : public internal::IWorldInternal {
    
    const int DefaultEntitiesCapacity = 64;

    std::vector<EntityId> _entities;
    std::vector<int> _freeEntities;

    std::unordered_map<uint64_t, std::shared_ptr<Filter>> _worldFilters;
    std::unordered_map<int, std::vector<std::shared_ptr<Filter>>> _listeners;

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
    void AddListener(uint64_t filterMask, std::shared_ptr<Filter> filter);

    template <typename T>
    std::shared_ptr<ComponentStorage<T>> GetRawStorage()
    {
        const auto typeHash = typeid(T).hash_code();
        const auto foundStorageIt = _componentStoragesHash.find(typeHash);

        if (foundStorageIt != _componentStoragesHash.end()) {
            return std::static_pointer_cast<ComponentStorage<T>>(foundStorageIt->second);
        }

        auto storage = std::make_shared<ComponentStorage<T>>(*this, _storagesCount);
        
        if ((size_t)_storagesCount == _componentStorages.capacity())
            _componentStorages.reserve(_storagesCount << 1);
        _componentStorages.push_back(storage);
        _componentStoragesHash.insert({typeHash, storage});

        ++_storagesCount;

        return storage;
    }

    template <typename T>
    ComponentStorage<T>& GetStorage()
    {
        return *GetRawStorage<T>();
    }

    std::shared_ptr<BaseComponentStorage> GetStorageById(int storageId);
    int GetStoragesCount() const;

};

#endif //WORLD_H
