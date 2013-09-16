#ifndef COLOURED_H
#define COLOURED_H

#include "IStylable.h"

#include <QColor>

template <typename T>
class Styled : public IStylable, public T
{
public:

    void SetFill(const QColor& theColour)
    {
        theColour.getRgb(&theFill.r, &theFill.g, &theFill.b);
    }

    void SetFill(const int r, const int g, const int b, const int a)
    {
        theFill.r = r;
        theFill.g = g;
        theFill.b = b;
        theFill.a = a;
    }

    void SetBorderFill(const QColor& theColour)
    {
        theColour.getRgb(&theBorderFill.r, &theBorderFill.g, &theBorderFill.b);
    }

    void SetBorderFill(const int r, const int g, const int b, const int a)
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
