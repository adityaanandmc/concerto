#ifndef RELATIONTYPE_H
#define RELATIONTYPE_H

typedef enum __RelationType
{
    UndefinedRelationType = 0x01,

    UnidirectionalAssociationType = 0x76,
    BidirectionalAssociationType,
    ExtensionPointType,
    UsesType
} RelationType;

#endif // RELATIONTYPE_H
