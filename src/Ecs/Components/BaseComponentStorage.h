#ifndef BASECOMPONENTSTORAGE_H
#define BASECOMPONENTSTORAGE_H

#include <span>
#include <cstdint>

class FilterBuilder;

class BaseComponentStorage {
private:
    friend class FilterBuilder;
    virtual std::span<const int> _Filtered() = 0;
    virtual bool _BindFilter(uint64_t mask) = 0;
public:
    virtual ~BaseComponentStorage() = default;

    virtual bool Has(int entityIid) const = 0;
    virtual int Count() const = 0;
    virtual std::span<const int> Entities() const = 0;
    virtual void Remove(int e) = 0;
    virtual int Id() const = 0;
};

#endif //BASECOMPONENTSTORAGE_H
