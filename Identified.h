#ifndef IDENTIFIED_H
#define IDENTIFIED_H

#include "IIdentifiable.h"

template <typename T>
class Identified : public IIdentifiable, public T
{
public:
    void setId(const uint16_t& theId)
    {
        this->theId = theId;
    }

    const uint16_t& getId() const
    {
        return theId;
    }

private:
    uint16_t theId;
};

#endif // IDENTIFIED_H
