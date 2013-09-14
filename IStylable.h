#ifndef ISTYLABLE_H
#define ISTYLABLE_H

#include <stdint.h>
#include <string>

typedef struct __Colour {
    uint8_t r,
            g,
            b,
            a;
} Colour;

typedef struct __Font {
    std::string theFamily;
    uint8_t theSize;
    std::string theWeight;
    bool isUnderlined;
    bool isItalic;
} Font;

class QColor;

struct IStylable
{
    virtual ~IStylable() {}

    virtual void SetFill(const QColor& theColour) = 0;

    virtual void SetFill(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) = 0;

    virtual void SetBorderFill(const QColor& theColour) = 0;

    virtual void SetBorderFill(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) = 0;

    virtual const Colour& GetFill() const = 0;

    virtual const Colour& GetBorderFill() const = 0;

    virtual const Font& GetFont() const = 0;

    virtual void SetFont(const Font& theFont) = 0;
};

#endif // ISTYLABLE_H
