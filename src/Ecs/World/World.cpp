#include "World.h"
#include <bit>
#include <cstdint>
#include <memory>
#include "../Filter/Filter.h"

void World::EntityComponentsChanged(const int e, const int storageId, const bool added)
{
    auto& entity = _entities[e];
    if (added)
    {
        _entities[e].AddComponent(storageId);
        if (_listeners.find(storageId) != _listeners.end())
        {
            for (auto listener: _listeners[storageId])
                if (auto mask = listener->GetMask(); (mask & _entities[e].Components()) == mask)
                    listener->Add(e);
        }
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
        if (!newCCount && !entity.onDelete)
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
    entity.onDelete = true;
    if (entity.IsRemoved())
        return;

    int id{0};
    uint64_t components = entity.Components();
    while (components)
    {
        id = std::countr_zero(components);
        _componentStorages[id]->Remove(e);
        components &= components - 1;
    }
    entity.Remove();
    entity.onDelete = false;
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
    return !entity.IsRemoved() && entity.Id >= 0 && (size_t)entity.Id < _entities.size() && e == entity.Id;
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

void World::AddListener(uint64_t filterMask, std::shared_ptr<Filter> filter)
{
    auto mask = filterMask;
    int id = 0;
    while (mask) 
    {
        id = std::countr_zero(mask);
        _listeners[id].push_back(filter);
        mask &= mask - 1;
    }
}

uint64_t World::GetEntityComponents(int e) 
{
    return _entities[e].Components();
}

std::shared_ptr<BaseComponentStorage> World::GetStorageById(int storageId)
{
    return _componentStorages[storageId];
}

int World::GetStoragesCount() const
{
    return _storagesCount;
}
