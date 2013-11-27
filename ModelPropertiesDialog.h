#ifndef MODELPROPERTIESDIALOG_H
#define MODELPROPERTIESDIALOG_H

#include <QDialog>

namespace Ui {
class ModelPropertiesDialog;
}

class ModelPropertiesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ModelPropertiesDialog(const QString filePath, const QString modelName, const QString author, const QString description, QWidget *parent = 0);
    ~ModelPropertiesDialog();

    QString getModelName() const;

    QString getAuthor() const;

    QString getDescription() const;
    
private:
    Ui::ModelPropertiesDialog *ui;
};

#endif // MODELPROPERTIESDIALOG_H
