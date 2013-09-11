#ifndef COLOURED_H
#define COLOURED_H

#include "IColourable.h"

#include <QColor>

template <typename T>
class Coloured : public IColourable, public T
{
public:

    void SetFill(const QColor& theColour)
    {
        int r, g, b;

        theColour.getRgb(&r, &g, &b);

        theFill.r = r;
        theFill.g = g;
        theFill.b = b;
    }

    void SetFill(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
    {
        theFill.r = r;
        theFill.g = g;
        theFill.b = b;
        theFill.a = a;
    }

    void SetBorderFill(const QColor& theColour)
    {
        int r, g, b;

        theColour.getRgb(&r, &g, &b);

        theBorderFill.r = r;
        theBorderFill.g = g;
        theBorderFill.b = b;
    }

    void SetBorderFill(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
    {
        theBorderFill.r = r;
        theBorderFill.g = g;
        theBorderFill.b = b;
        theBorderFill.a = a;
    }

    const Colour& GetFill() const
    {
        return theFill;
    }

    const Colour& GetBorderFill() const
    {
        return theBorderFill;
    }

private:
    Colour theFill;
    Colour theBorderFill;
};

#endif // COLOURED_H
