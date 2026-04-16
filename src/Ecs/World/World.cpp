#include "World.h"
#include <bit>
#include <cstdint>
#include <memory>
#include "../Filter/SparseFilter.h"

void World::EntityComponentsChanged(const int e, const int storageId, const bool added)
{
    auto& entity = _entities[e];
    if (added)
    {
        if (_listeners.find(storageId) != _listeners.end())
        {
            for (auto listener: _listeners[storageId])
            listener->Add(e);
        }
        entity.AddComponent(storageId);
    }
    else
    {
        if (_listeners.find(storageId) != _listeners.end())
        {
            for (auto listener: _listeners[storageId])
                if (auto mask = listener->GetMask(); (mask & _entities[e].Components()) == mask)
                    listener->Remove(e);
        }
        const int newCCount = entity.RemoveComponent(storageId);
        if (!newCCount)
            RemoveEntity(e);
    }
}

World::World()
{
    _entities.reserve(DefaultEntitiesCapacity);
    _freeEntities.reserve(DefaultEntitiesCapacity);
}

int World::CreateEntity()
{
    int eId;
    
    if (!_freeEntities.empty()) 
    {
        eId = _freeEntities.back();
        _freeEntities.pop_back();
        _entities[eId].Recycle();
    }
    else
    {
        eId = _entities.size();
        _entities.emplace_back(eId, 1);
    }
    return eId;
}

void World::RemoveEntity(int e)
{
    auto& entity = _entities[e];
    if (entity.IsRemoved())
        return;

    int id{0};
    uint64_t components = entity.Components();
    while (components)
    {
        id += std::countr_zero(components);
        _componentStorages[id]->Remove(e);
        components &= components - 1;
        id++;
    }
    entity.Remove();
    _freeEntities.push_back(e);
}

EntityId World::GetPackedEntity(const int e) const
{
    return _entities[e];
}

bool World::UnpackEntity(const EntityId &eId, int &e) const
{
    e = eId.Id;
    return IsEntityAlive(e) && eId.Gen() == _entities[e].Gen();
}

bool World::IsEntityAlive(const int e) const
{
    auto& entity = _entities[e];
    return !entity.IsRemoved() && entity.Id > 0 && (size_t)entity.Id < _entities.size() && e == entity.Id;
}

template <typename T>
std::shared_ptr<ComponentStorage<T>> World::GetRawStorage()
{
    const auto typeHash = typeid(T).hash_code();
    const auto foundStorageIt = _componentStoragesHash.find(typeHash);

    if (foundStorageIt != _componentStoragesHash.end()) {
        return std::static_pointer_cast<ComponentStorage<T>>(foundStorageIt);
    }

    int storageCount = _componentStorages.size();
    auto storage = std::make_shared<ComponentStorage<T>>(*this, storageCount);
    
    if ((size_t)storageCount == _componentStorages.capacity())
        _componentStorages.reserve(storageCount << 1);
    _componentStorages.push_back(storage);
    _componentStoragesHash.insert({typeHash, storage});

    return storage;
}

template <typename T>
ComponentStorage<T>& World::GetStorage()
{
    return *GetRawStorage<T>();
}

std::shared_ptr<Filter> World::GetFilter(uint64_t filterMask)
{
    if (_worldFilters.find(filterMask) != _worldFilters.end())
        return _worldFilters[filterMask];
    return nullptr;
}

void World::AddFilter(uint64_t filterMask, std::shared_ptr<Filter> filter)
{
    _worldFilters[filterMask] = filter;
}

void World::AddListener(uint64_t filterMask, std::shared_ptr<SparseFilter> filter)
{
    auto mask = filterMask;
    int id = 0;
    while (mask) 
    {
        id += std::countr_zero(mask);
        _listeners[id].push_back(filter);
        mask &= mask - 1;
        ++id;
    }
}
