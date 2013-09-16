#ifndef MODELMAPPER_H
#define MODELMAPPER_H

#include "IModelMapper.h"

class ModelMapper : public IModelMapper
{
public:
    ModelMapper();

    void load(const std::string& theFile, IDocumentModel *theModel, bool& theStatus);

    void save(const std::string& theFile, const IDocumentModel *theModel, bool& theStatus);

private:
    IDocumentModel *theModel;
};

#endif // MODELMAPPER_H
