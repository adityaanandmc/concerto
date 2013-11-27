#-------------------------------------------------
#
# Project created by QtCreator 2013-09-06T21:29:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = mozart
TEMPLATE = app


SOURCES += main.cpp\
        concerto.cpp \
    diagramwindow.cpp \
    DocumentModel.cpp \
    Diagram/DiagramItem.cpp \
    Diagram/DiagramTextItem.cpp \
    Diagram/Arrow.cpp \
    Diagram/DiagramScene.cpp \
    TinyXML/tinyxml2.cpp \
    ModelMapper.cpp \
    NodePropertiesDialog.cpp \
    ModelPropertiesDialog.cpp

HEADERS  += concerto.h \
    diagramwindow.h \
    IPositionable.h \
    Positioned.h \
    IAttributable.h \
    Attributed.h \
    IIdentifiable.h \
    Identified.h \
    NodeType.h \
    INode.h \
    Node.h \
    NodeDefs.h \
    Relation.h \
    RelationType.h \
    IRelation.h \
    RelationDefs.h \
    IAuthor.h \
    Author.h \
    IDiagram.h \
    Diagram.h \
    DocumentModel.h \
    IDocumentModel.h \
    GraphDefs.h \
    Nodes/UsecaseGraphNode.h \
    Nodes/ActorGraphNode.h \
    Nodes/SubFlowGraphNode.h \
    Nodes/SecFlowGraphNode.h \
    Nodes/SquareGraphNode.h \
    Nodes/AltFlowGraphNode.h \
    Nodes/RectangleGraphNode.h \
    Nodes/CircleGraphNode.h \
    Nodes/TriangleGraphNode.h \
    Relations/UnidirectionalAssociationRelation.h \
    Relations/BidirectionalAssociationRelation.h \
    Relations/ExtensionPointRelation.h \
    Relations/UsesRelation.h \
    Graph/Vertex.h \
    Graph/Edge.h \
    Graph/DiagramInfo.h \
    Diagram/DiagramItem.h \
    Diagram/DiagramTextItem.h \
    Diagram/Arrow.h \
    Diagram/DiagramScene.h \
    NodeFactory.h \
    RelationFactory.h \
    ILabelizable.h \
    Labelled.h \
    IStylable.h \
    Styled.h \
    TinyXML/tinyxml2.h \
    IModelMapper.h \
    ModelMapper.h \
    StdStringUtil.h \
    NodePropertiesDialog.h \
    Undoable/InsertNode.h \
    NodeUtil.h \
    RelationUtil.h \
    Undoable/InsertRelation.h \
    Undoable/RemoveNode.h \
    Undoable/RemoveRelation.h \
    Undoable/MoveNode.h \
    ModelPropertiesDialog.h

FORMS    += concerto.ui \
    nodepropertiesdialog.ui \
    modelpropertiesdialog.ui

RESOURCES += \
    Image-Resources.qrc
