#ifndef POSITIONED_H
#define POSITIONED_H

#include "IPositionable.h"

template <typename T>
class Positioned : public IPositionable, public T
{
public:

    void setPosition(double x, double y, double z = 0)
    {
        mX = x;
        mY = y;
        mZ = z;
    }

    void setZIndex(double z)
    {
        mZ = z;
    }

    std::pair<double, double> getPosition() const
    {
        return std::pair<double, double>(mX, mY);
    }

    const double& getX() const
    {
        return mX;
    }

    const double& getY() const
    {
        return mY;
    }

    const double& getZ() const
    {
        return mZ;
    }

private:
    double mX;
    double mY;
    double mZ;
};

#endif // POSITIONED_H
