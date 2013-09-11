#ifndef ICOLOURABLE_H
#define ICOLOURABLE_H

#include <stdint.h>

typedef struct __Colour {
    uint8_t r,
            g,
            b,
            a;
} Colour;

class QColor;

struct IColourable
{
    virtual ~IColourable() {}

    virtual void SetFill(const QColor& theColour) = 0;

    virtual void SetFill(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) = 0;

    virtual void SetBorderFill(const QColor& theColour) = 0;

    virtual void SetBorderFill(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) = 0;

    virtual const Colour& GetFill() const = 0;

    virtual const Colour& GetBorderFill() const = 0;
};

#endif // ICOLOURABLE_H
