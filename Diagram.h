#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "IDiagram.h"

class Diagram : public IDiagram
{
public:
    const std::string& getTitle() const
    {
        return theTitle;
    }

    void setTitle(const std::string& theTitle)
    {
        this->theTitle = theTitle;
    }

    const std::string& getDescription() const
    {
        return theDescription;
    }

    void setDescription(const std::string& theDescription)
    {
        this->theDescription = theDescription;
    }

    const IAuthor *getAuthor() const
    {
        return theAuthor;
    }

    void setAuthor(const IAuthor *theAuthor)
    {
        this->theAuthor = const_cast<IAuthor *>(theAuthor); // quirk; must for const-correctness
    }

protected:
    std::string theTitle;
    std::string theDescription;
    IAuthor *theAuthor;
};

#endif // DIAGRAM_H
