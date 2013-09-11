#ifndef IPOSITIONABLE_H
#define IPOSITIONABLE_H

#include <utility>

struct IPositionable
{
    virtual ~IPositionable() {}

    virtual void setPosition(double x, double y, double z = 0) = 0;

    virtual void setZIndex(double z) = 0;

    virtual std::pair<double, double> getPosition() const = 0;

    virtual const double& getX() const = 0;

    virtual const double& getY() const = 0;

    virtual const double& getZ() const = 0;
};

#endif // IPOSITIONABLE_H
