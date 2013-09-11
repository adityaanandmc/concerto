#ifndef EXTENSIONPOINTRELATION_H
#define EXTENSIONPOINTRELATION_H

#include "../Relation.h"

class ExtensionPointRelation : public Relation
{
public:
    ExtensionPointRelation()
    {
        theType = ExtensionPointType;
    }
};

#endif // EXTENSIONPOINTRELATION_H
