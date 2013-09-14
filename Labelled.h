#ifndef LABELLED_H
#define LABELLED_H

#include "ILabelizable.h"

template <typename T>
class Labelled : public ILabelizable, public T
{
public:
    const std::string getName() const
    {
        return theName;
    }

    void setName(const std::string& theName)
    {
        this->theName = theName;
    }

    void setLabelPosition(const double x, const double y)
    {
        theX = x;
        theY = y;
    }

    const double& getLabelX() const
    {
        return theX;
    }

    const double& getLabelY() const
    {
        return theY;
    }

private:
    std::string theName;

    double theX,
           theY;
};

#endif // LABELLED_H
