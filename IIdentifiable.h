#ifndef IIDENTIFIABLE_H
#define IIDENTIFIABLE_H

#include <stdint.h>

struct IIdentifiable
{
    virtual ~IIdentifiable() {}

    virtual void setId(const uint16_t& theId) = 0;

    virtual const uint16_t& getId() const = 0;
};

#endif // IIDENTIFIABLE_H
