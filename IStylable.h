#ifndef ISTYLABLE_H
#define ISTYLABLE_H

#include <string>

typedef struct __Colour {
    int r,
        g,
        b,
        a;

    __Colour()
    {
        r = g = b = 0;
        a = 255;
    }
} Colour;

class QColor;

struct IStylable
{
    virtual ~IStylable() {}

    virtual void SetFill(const QColor& theColour) = 0;

    virtual void SetFill(const int r, const int g, const int b, const int a) = 0;

    virtual void SetBorderFill(const QColor& theColour) = 0;

    virtual void SetBorderFill(const int r, const int g, const int b, const int a) = 0;

    virtual const Colour& GetFill() const = 0;

    virtual const Colour& GetBorderFill() const = 0;
};

#endif // ISTYLABLE_H
