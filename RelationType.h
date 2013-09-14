#ifndef RELATIONTYPE_H
#define RELATIONTYPE_H

typedef enum __RelationType
{
    UnidirectionalAssociationType = 0x76,
    BidirectionalAssociationType,
    ExtensionPointType,
    UsesType
} RelationType;

#endif // RELATIONTYPE_H
