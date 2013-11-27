#ifndef INODE_H
#define INODE_H

#include "NodeType.h"

struct INode
{
    virtual ~INode() {}

    virtual bool canBeSentinel() const = 0;

    virtual bool validatable() const = 0;

    virtual const NodeType& getType() const = 0;

    virtual void setType(const NodeType theType) = 0;
};

#endif // INODE_H
