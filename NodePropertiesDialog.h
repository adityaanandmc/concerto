#ifndef NODEPROPERTIESDIALOG_H
#define NODEPROPERTIESDIALOG_H

#include <QDialog>
#include "IAttributable.h"

namespace Ui {
class NodePropertiesDialog;
}

class NodePropertiesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NodePropertiesDialog(const IAttributable *theAttributes, QWidget *parent = 0);
    ~NodePropertiesDialog();

    const std::map<std::string, std::string> getSavedAttributes() const;
    
private:
    Ui::NodePropertiesDialog *ui;
};

#endif // NODEPROPERTIESDIALOG_H
