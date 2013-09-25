#include "ModelMapper.h"
#include "Author.h"
#include "NodeFactory.h"
#include "RelationFactory.h"
#include "TinyXML/tinyxml2.h"
#include "StdStringUtil.h"

using namespace tinyxml2;

ModelMapper::ModelMapper()
{

}

void ModelMapper::load(const std::string &theFile, IDocumentModel *theModel, bool &theStatus)
{
    if (!theModel) {
        theStatus = false;
        return;
    }

    XMLDocument doc;

    if (XML_SUCCESS != doc.LoadFile(theFile.c_str())) {
        theStatus = false;
        return;
    }

    XMLElement *root = doc.FirstChildElement("Document");

    if (!root) {
        theStatus = false;
        return;
    }

    // Meta Block
    {
        XMLElement *meta = root->FirstChildElement("meta");

        if (meta) {
            if (XMLElement *element = meta->FirstChildElement("model")) {
                theModel->setTitle(element->GetText());
            }

            if (XMLElement *element = meta->FirstChildElement("description")) {
                theModel->setDescription(element->GetText());
            }

            if (XMLElement *element = meta->FirstChildElement("author")) {
                Author *author = new Author;
                if (NULL != element->GetText()) {
                    author->setName(element->GetText());
                }

                theModel->setAuthor(author);
            }
        }
    }

    // Objects Block
    {
        XMLElement *objects = root->FirstChildElement("objects");

        if (!objects) {
            theStatus = false;
            return;
        }

        XMLElement *node = objects->FirstChildElement("node");

        int _temp;

        while (node) {
            INode *theNode = NULL;

            if (XML_SUCCESS == node->QueryIntAttribute("type", &_temp)) {
                NodeType theType = static_cast<NodeType>(_temp);

                theNode = NodeFactory::makeNode(theType);

                if (NULL == theNode) {
                    theStatus = false;
                    return;
                }
            } else {
                // FATAL. Nodes *need* to be of a type!
                theStatus = false;
                return;
            }

            // Implements IIdentifiable
            if (XML_SUCCESS == node->QueryIntAttribute("id", &_temp)) {
                if (IIdentifiable *thing = dynamic_cast<IIdentifiable *>(theNode)) {
                    thing->setId(static_cast<uint16_t>(_temp));
                }
            }

            // Implements ILabelizable
            if (XMLElement *label = node->FirstChildElement("label")) {
                if (ILabelizable *thing = dynamic_cast<ILabelizable *>(theNode)) {
                    if (XMLElement *name = label->FirstChildElement("name")) {
                        thing->setName(name->GetText());
                    }

                    if (XMLElement *position = label->FirstChildElement("position")) {
                        double xPos = 0, yPos = 0;

                        if (XMLElement *x = position->FirstChildElement("x")) {
                            xPos = Util::StdString::fromString<double>(x->GetText());
                        }

                        if (XMLElement *y = position->FirstChildElement("y")) {
                            yPos = Util::StdString::fromString<double>(y->GetText());
                        }

                        thing->setLabelPosition(xPos, yPos);
                    }
                } else {
                    theStatus = false;
                    return;
                }
            }

            // Implements IPositionable
            if (XMLElement *position = node->FirstChildElement("position")) {
                if (IPositionable *thing = dynamic_cast<IPositionable *>(theNode)) {
                    double xPos, yPos, zVal;
                    xPos = yPos = zVal = 0;

                    if (XMLElement *x = position->FirstChildElement("x")) {
                        xPos = Util::StdString::fromString<double>(x->GetText());
                    }

                    if (XMLElement *y = position->FirstChildElement("y")) {
                        yPos = Util::StdString::fromString<double>(y->GetText());
                    }

                    if (XMLElement *z = position->FirstChildElement("z")) {
                        zVal = Util::StdString::fromString<double>(z->GetText());
                    }

                    thing->setPosition(xPos, yPos, zVal);
                } else {
                    theStatus = false;
                    return;
                }
            }

            // Implements IStylable
            if (XMLElement *style = node->FirstChildElement("style")) {
                if (IStylable *thing = dynamic_cast<IStylable *>(theNode)) {
                    if (XMLElement *fill = style->FirstChildElement("fill")) {
                        if (XMLElement *colour = fill->FirstChildElement("colour")) {
                            Colour col;

                            if (XMLElement *r = colour->FirstChildElement("r")) {
                                col.r = Util::StdString::fromString<int>(r->GetText());
                            }

                            if (XMLElement *g = colour->FirstChildElement("g")) {
                                col.g = Util::StdString::fromString<int>(g->GetText());
                            }

                            if (XMLElement *b = colour->FirstChildElement("b")) {
                                col.b = Util::StdString::fromString<int>(b->GetText());
                            }

                            if (XMLElement *a = colour->FirstChildElement("a")) {
                                col.a = Util::StdString::fromString<int>(a->GetText());
                            }

                            thing->SetFill(col.r, col.g, col.b, col.a);
                        }
                    }

                    if (XMLElement *line = style->FirstChildElement("line")) {
                        if (XMLElement *colour = line->FirstChildElement("colour")) {
                            Colour col;

                            if (XMLElement *r = colour->FirstChildElement("r")) {
                                col.r = Util::StdString::fromString<int>(r->GetText());
                            }

                            if (XMLElement *g = colour->FirstChildElement("g")) {
                                col.g = Util::StdString::fromString<int>(g->GetText());
                            }

                            if (XMLElement *b = colour->FirstChildElement("b")) {
                                col.b = Util::StdString::fromString<int>(b->GetText());
                            }

                            if (XMLElement *a = colour->FirstChildElement("a")) {
                                col.a = Util::StdString::fromString<int>(a->GetText());
                            }

                            thing->SetBorderFill(col.r, col.g, col.b, col.a);
                        }
                    }
                } else {
                    theStatus = false;
                    return;
                }
            }

            // Implements IAttributable
            if (XMLElement *properties = node->FirstChildElement("properties")) {
                if (IAttributable *thing = dynamic_cast<IAttributable *>(theNode)) {
                    XMLElement *property = properties->FirstChildElement("property");
                    std::string key, value;

                    while (property) {
                        key = property->Attribute("name");
                        value = (property->GetText()) ? property->GetText() : "";

                        thing->setAttribute(key, value);

                        property = property->NextSiblingElement();
                    }
                } else {
                    theStatus = false;
                    return;
                }
            }

            theModel->addNode(theNode);

            node = node->NextSiblingElement();
        }
    }

    // Relations Block
    {
        XMLElement *relations = root->FirstChildElement("relations");

        if (!relations) {
            theStatus = true; // It's okay if nothing is connected (yet)
            return;
        }

        XMLElement *relation = relations->FirstChildElement("relation");

        int _tmp;

        while (relation) {
            IRelation *theRelation = NULL;
            const INode *thisNode = NULL, *thatNode = NULL;

            if (XML_SUCCESS == relation->QueryIntAttribute("type", &_tmp)) {
                theRelation = RelationFactory::makeRelation(static_cast<RelationType>(_tmp));

                if (NULL == theRelation) {
                    theStatus = false;
                    return;
                }
            } else {
                theStatus = false;
                return;
            }

            if (XML_SUCCESS == relation->QueryIntAttribute("source", &_tmp)) {
                thisNode = theModel->getNode(static_cast<uint16_t>(_tmp));

                if (!thisNode) {
                    theStatus = false;
                    return;
                }
            } else {
                theStatus = false;
                return;
            }

            if (XML_SUCCESS == relation->QueryIntAttribute("target", &_tmp)) {
                thatNode = theModel->getNode(static_cast<uint16_t>(_tmp));

                if (!thisNode) {
                    theStatus = false;
                    return;
                }
            } else {
                theStatus = false;
                return;
            }

            if (XMLElement *style = relation->FirstChildElement("style")) {
                if (IStylable *thing = dynamic_cast<IStylable *>(theRelation)) {
                    if (XMLElement *fill = style->FirstChildElement("fill")) {
                        if (XMLElement *colour = fill->FirstChildElement("colour")) {
                            Colour col;

                            if (XMLElement *r = colour->FirstChildElement("r")) {
                                col.r = Util::StdString::fromString<int>(r->GetText());
                            }

                            if (XMLElement *g = colour->FirstChildElement("g")) {
                                col.g = Util::StdString::fromString<int>(g->GetText());
                            }

                            if (XMLElement *b = colour->FirstChildElement("b")) {
                                col.b = Util::StdString::fromString<int>(b->GetText());
                            }

                            if (XMLElement *a = colour->FirstChildElement("a")) {
                                col.a = Util::StdString::fromString<int>(a->GetText());
                            }

                            thing->SetFill(col.r, col.g, col.b, col.a);
                        }
                    }

                    if (XMLElement *line = style->FirstChildElement("line")) {
                        if (XMLElement *colour = line->FirstChildElement("colour")) {
                            Colour col;

                            if (XMLElement *r = colour->FirstChildElement("r")) {
                                col.r = Util::StdString::fromString<int>(r->GetText());
                            }

                            if (XMLElement *g = colour->FirstChildElement("g")) {
                                col.g = Util::StdString::fromString<int>(g->GetText());
                            }

                            if (XMLElement *b = colour->FirstChildElement("b")) {
                                col.b = Util::StdString::fromString<int>(b->GetText());
                            }

                            if (XMLElement *a = colour->FirstChildElement("a")) {
                                col.a = Util::StdString::fromString<int>(a->GetText());
                            }

                            thing->SetBorderFill(col.r, col.g, col.b, col.a);
                        }
                    }
                } else {
                    theStatus = false;
                    return;
                }
            }

            theModel->relate(theRelation, thisNode, thatNode);

            relation = relation->NextSiblingElement();
        }
    }

    theStatus = true;
}

void ModelMapper::save(const std::string &theFile, const IDocumentModel *theModel, bool &theStatus)
{
    if (!theModel) {
        theStatus = false;
        return;
    }

    XMLDocument doc;
    doc.LinkEndChild(doc.NewDeclaration());

    XMLElement *root = doc.NewElement("Document");
    doc.LinkEndChild(root);

    // Meta Block
    {
        XMLElement *meta = doc.NewElement("meta");
        root->LinkEndChild(meta);

        XMLElement *model = doc.NewElement("model");
        model->InsertEndChild(doc.NewText(theModel->getTitle().c_str()));
        meta->InsertEndChild(model);

        XMLElement *description = doc.NewElement("description");
        description->InsertEndChild(doc.NewText(theModel->getDescription().c_str()));
        meta->InsertEndChild(description);

        XMLElement *author = doc.NewElement("author");
        if (theModel->getAuthor()) {
            author->InsertEndChild(doc.NewText(theModel->getAuthor()->getName().c_str()));
        }
        meta->InsertEndChild(author);
    }

    GraphType theGraph = theModel->getGraph();

    // Objects Block
    {
        XMLElement *objects = doc.NewElement("objects");
        root->LinkEndChild(objects);

        vertex_iterator_t vi, vi_end, next;

        boost::tie(vi, vi_end) = boost::vertices(theGraph);

        for (next = vi; vi != vi_end; vi = next) {
            ++next;
            INode *aNode = theGraph[*vi].theNode;

            XMLElement *node = doc.NewElement("node");

            node->SetAttribute("type", static_cast<int>(aNode->getType()));

            if (IIdentifiable *thing = dynamic_cast<IIdentifiable *>(aNode)) {
                node->SetAttribute("id", static_cast<int>(thing->getId()));
            }

            if (IPositionable *thing = dynamic_cast<IPositionable *>(aNode)) {
                XMLElement *position = doc.NewElement("position");
                XMLElement *x = doc.NewElement("x");
                x->InsertEndChild(doc.NewText(Util::StdString::toString<double>(thing->getX()).c_str()));
                XMLElement *y = doc.NewElement("y");
                y->InsertEndChild(doc.NewText(Util::StdString::toString<double>(thing->getY()).c_str()));
                XMLElement *z = doc.NewElement("z");
                z->InsertEndChild(doc.NewText(Util::StdString::toString<double>(thing->getZ()).c_str()));

                position->InsertEndChild(x);
                position->InsertEndChild(y);
                position->InsertEndChild(z);

                node->LinkEndChild(position);
            }

            if (IStylable *thing = dynamic_cast<IStylable *>(aNode)) {
                XMLElement *style = doc.NewElement("style");
                XMLElement *fill = doc.NewElement("fill");
                XMLElement *line = doc.NewElement("line");

                {
                    Colour fillColour = thing->GetFill();

                    XMLElement *colour = doc.NewElement("colour");
                    XMLElement *r = doc.NewElement("r");
                    r->InsertEndChild(doc.NewText(Util::StdString::toString<int>(fillColour.r).c_str()));

                    XMLElement *g = doc.NewElement("g");
                    g->InsertEndChild(doc.NewText(Util::StdString::toString<int>(fillColour.g).c_str()));

                    XMLElement *b = doc.NewElement("b");
                    b->InsertEndChild(doc.NewText(Util::StdString::toString<int>(fillColour.b).c_str()));

                    XMLElement *a = doc.NewElement("a");
                    a->InsertEndChild(doc.NewText(Util::StdString::toString<int>(fillColour.a).c_str()));

                    colour->InsertEndChild(r);
                    colour->InsertEndChild(g);
                    colour->InsertEndChild(b);
                    colour->InsertEndChild(a);

                    fill->InsertEndChild(colour);
                    style->InsertEndChild(fill);
                }

                {
                    Colour lineColour = thing->GetBorderFill();

                    XMLElement *colour = doc.NewElement("colour");
                    XMLElement *r = doc.NewElement("r");
                    r->InsertEndChild(doc.NewText(Util::StdString::toString<int>(lineColour.r).c_str()));

                    XMLElement *g = doc.NewElement("g");
                    g->InsertEndChild(doc.NewText(Util::StdString::toString<int>(lineColour.g).c_str()));

                    XMLElement *b = doc.NewElement("b");
                    b->InsertEndChild(doc.NewText(Util::StdString::toString<int>(lineColour.b).c_str()));

                    XMLElement *a = doc.NewElement("a");
                    a->InsertEndChild(doc.NewText(Util::StdString::toString<int>(lineColour.a).c_str()));

                    colour->InsertEndChild(r);
                    colour->InsertEndChild(g);
                    colour->InsertEndChild(b);
                    colour->InsertEndChild(a);

                    line->InsertEndChild(colour);
                    style->InsertEndChild(line);
                }

                node->InsertEndChild(style);
            }

            if (ILabelizable *thing = dynamic_cast<ILabelizable *>(aNode)) {
                XMLElement *label = doc.NewElement("label");
                XMLElement *name = doc.NewElement("name");
                name->InsertEndChild(doc.NewText(thing->getName().c_str()));

                XMLElement *position = doc.NewElement("position");
                XMLElement *x = doc.NewElement("x");
                XMLElement *y = doc.NewElement("y");

                x->InsertEndChild(doc.NewText(Util::StdString::toString<double>(thing->getLabelX()).c_str()));
                y->InsertEndChild(doc.NewText(Util::StdString::toString<double>(thing->getLabelY()).c_str()));

                position->InsertEndChild(x);
                position->InsertEndChild(y);

                label->InsertEndChild(name);
                label->InsertEndChild(position);

                node->InsertEndChild(label);
            }

            if (IAttributable *thing = dynamic_cast<IAttributable *>(aNode)) {
                XMLElement *properties = doc.NewElement("properties");

                std::map<std::string, std::string> propertyList = thing->getPropertyList();
                std::map<std::string, std::string>::const_iterator it, end = propertyList.end();

                for (it = propertyList.begin(); it != end; ++it) {
                    XMLElement *property = doc.NewElement("property");
                    property->SetAttribute("name", it->first.c_str());
                    property->InsertEndChild(doc.NewText(it->second.c_str()));

                    properties->InsertEndChild(property);
                }

                node->InsertEndChild(properties);
            }

            objects->LinkEndChild(node);
        }
    }

    // Relations Block
    {
        XMLElement *relations = doc.NewElement("relations");
        root->LinkEndChild(relations);

        edge_iterator_t ei, ei_end, next;
        vertex_t u, v;

        boost::tie(ei, ei_end) = boost::edges(theGraph);
        for (next = ei; ei != ei_end; ei = next) {
            ++next;
            u = boost::source(*ei, theGraph);
            v = boost::target(*ei, theGraph);

            IRelation *theRelation = theGraph[*ei].theRelation;
            IIdentifiable *sourceNode = dynamic_cast<IIdentifiable *>(theGraph[u].theNode),
                          *targetNode = dynamic_cast<IIdentifiable *>(theGraph[v].theNode);

            XMLElement *relation = doc.NewElement("relation");
            relation->SetAttribute("type", static_cast<int>(theRelation->getType()));
            relation->SetAttribute("title", theRelation->getTitle().c_str());
            relation->SetAttribute("source", static_cast<int>(sourceNode->getId()));
            relation->SetAttribute("target", static_cast<int>(targetNode->getId()));

            if (IStylable *thing = dynamic_cast<IStylable *>(theRelation)) {
                XMLElement *style = doc.NewElement("style");
                XMLElement *fill = doc.NewElement("fill");
                XMLElement *line = doc.NewElement("line");

                {
                    Colour fillColour = thing->GetFill();

                    XMLElement *colour = doc.NewElement("colour");
                    XMLElement *r = doc.NewElement("r");
                    r->InsertEndChild(doc.NewText(Util::StdString::toString<int>(fillColour.r).c_str()));

                    XMLElement *g = doc.NewElement("g");
                    g->InsertEndChild(doc.NewText(Util::StdString::toString<int>(fillColour.g).c_str()));

                    XMLElement *b = doc.NewElement("b");
                    b->InsertEndChild(doc.NewText(Util::StdString::toString<int>(fillColour.b).c_str()));

                    XMLElement *a = doc.NewElement("a");
                    a->InsertEndChild(doc.NewText(Util::StdString::toString<int>(fillColour.a).c_str()));

                    colour->InsertEndChild(r);
                    colour->InsertEndChild(g);
                    colour->InsertEndChild(b);
                    colour->InsertEndChild(a);

                    fill->InsertEndChild(colour);
                    style->InsertEndChild(fill);
                }

                {
                    Colour lineColour = thing->GetBorderFill();

                    XMLElement *colour = doc.NewElement("colour");
                    XMLElement *r = doc.NewElement("r");
                    r->InsertEndChild(doc.NewText(Util::StdString::toString<int>(lineColour.r).c_str()));

                    XMLElement *g = doc.NewElement("g");
                    g->InsertEndChild(doc.NewText(Util::StdString::toString<int>(lineColour.g).c_str()));

                    XMLElement *b = doc.NewElement("b");
                    b->InsertEndChild(doc.NewText(Util::StdString::toString<int>(lineColour.b).c_str()));

                    XMLElement *a = doc.NewElement("a");
                    a->InsertEndChild(doc.NewText(Util::StdString::toString<int>(lineColour.a).c_str()));

                    colour->InsertEndChild(r);
                    colour->InsertEndChild(g);
                    colour->InsertEndChild(b);
                    colour->InsertEndChild(a);

                    line->InsertEndChild(colour);
                    style->InsertEndChild(line);
                }

                relation->InsertEndChild(style);
            }

            relations->LinkEndChild(relation);
        }
    }

    if (XML_SUCCESS == doc.SaveFile(theFile.c_str())) {
        theStatus = true;
    } else {
        theStatus = false;
    }
}
