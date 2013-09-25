#ifndef RELATIONUTIL_H
#define RELATIONUTIL_H

namespace Util {
    namespace Relation {
    #include <string>
    #include "RelationType.h"

    const std::string toString(const RelationType theType)
    {
        switch (theType) {
        case UnidirectionalAssociationType:
            return "Unidirectional Association";

        case BidirectionalAssociationType:
            return "Bidirectional Association";

        case ExtensionPointType:
            return "Extension Point";

        case UsesType:
            return "Uses";
        }

        return "";
    }

    }
}

#endif // RELATIONUTIL_H
