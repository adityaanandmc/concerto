#ifndef INODE_H
#define INODE_H

#include "NodeType.h"

struct INode
{
    virtual ~INode() {}

    virtual bool canBeSentinel() const = 0;

    virtual const std::string getName() const = 0;

    virtual void setName(const std::string& theName) = 0;

    virtual const NodeType& getType() const = 0;

    virtual void setType(const NodeType theType) = 0;
};

#endif // INODE_H
