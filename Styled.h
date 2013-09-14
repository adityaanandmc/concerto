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

    const Font& GetFont() const
    {
        return theFont;
    }

    void SetFont(const Font& theFont)
    {
        this->theFont = theFont;
    }

private:
    Colour theFill;
    Colour theBorderFill;
    Font theFont;
};

#endif // COLOURED_H
