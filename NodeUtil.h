#ifndef NODEUTIL_H
#define NODEUTIL_H

namespace Util {
    namespace Node {
    #include <string>
    #include "NodeType.h"

    const std::string toString(const NodeType theType)
    {
        switch (theType) {
        case ActorType:
            return "Actor";

        case UsecaseType:
            return "Usecase";

        case SubFlowType:
            return "Sub Flow";

        case AltFlowType:
            return "Alt Flow";

        case SecFlowType:
            return "Security Flow";

        case GeomCircleType:
            return "Circle";

        case GeomRectangleType:
            return "Rectangle";

        case GeomSquareType:
            return "Square";

        case GeomTriangleType:
            return "Triangle";
        }

        return "";
    }

    }
}

#endif // NODEUTIL_H
