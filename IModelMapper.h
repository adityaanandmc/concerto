#ifndef IMODELMAPPER_H
#define IMODELMAPPER_H

#include "IDocumentModel.h"

struct IModelMapper
{
    virtual ~IModelMapper() {}

    virtual void load(const std::string& theFile, IDocumentModel *theModel, bool& theStatus) = 0;

    virtual void save(const std::string& theFile, const IDocumentModel *theModel, bool& theStatus) = 0;
};

#endif // IMODELMAPPER_H
