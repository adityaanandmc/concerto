#ifndef ILABELIZABLE_H
#define ILABELIZABLE_H

struct ILabelizable
{
    virtual ~ILabelizable() {}

    virtual const std::string getName() const = 0;

    virtual void setName(const std::string& theName) = 0;

    virtual void setLabelPosition(const double x, const double y) = 0;

    virtual const double& getLabelX() const = 0;

    virtual const double& getLabelY() const = 0;
};

#endif // ILABELIZABLE_H
