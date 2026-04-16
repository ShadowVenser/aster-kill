#include "EntityId.h"
#include <bit>
#include <string>

void EntityId::AddComponent(const int component)
{
    _components |= 1 << component;
}

int EntityId::RemoveComponent(const int component)
{
    if (uint64_t mask = 1 << component; (_components && mask) == mask)
        _components ^= mask;
    return std::popcount(_components);
}

bool EntityId::IsRemoved() const
{
    return _gen < 0;
}

uint64_t EntityId::Components() const
{
    return _components;
}

int EntityId::Gen() const
{
    return _gen;
}

void EntityId::Remove()
{
    _gen = -(_gen + 1);
}

void EntityId::Recycle()
{
    _gen *= -1;
}

bool EntityId::Equals(const EntityId &other) const
{
    return Id == other.Id && _gen == other._gen;
}

bool EntityId::operator==(const EntityId &other) const
{
    return this->Equals(other);
}

bool EntityId::operator!=(const EntityId &other) const
{
    return !this->Equals(other);
}

std::ostream& operator<<(std::ostream &os, const EntityId &eId)
{
    os << "Entity: " << eId.Id << "; Gen: " << eId._gen << '\n';
    os << "Components: [";
    int id = 0;
    auto comps = eId._components;
    while (comps)
    {
        int isComponent = comps & 1;
        comps >>= 1;
        os << isComponent ? (std::to_string(id) + (comps ? ", " : "]\n")) : "";
        ++id;
    }
    return os;
}
