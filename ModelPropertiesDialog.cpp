#include "ModelPropertiesDialog.h"
#include "ui_modelpropertiesdialog.h"
#include <QFileInfo>

ModelPropertiesDialog::ModelPropertiesDialog(const QString filePath, const QString modelName, const QString author, const QString description, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModelPropertiesDialog)
{
    ui->setupUi(this);

    ui->authorLineEdit->setText(author);
    ui->descriptionTextEdit->appendPlainText(description);
    ui->modelLineEdit->setText(modelName);

    QFileInfo finfo(filePath);
    ui->lastModifiedDateTimeEdit->setDateTime(finfo.lastModified());
}

ModelPropertiesDialog::~ModelPropertiesDialog()
{
    delete ui;
}

QString ModelPropertiesDialog::getModelName() const
{
    return ui->modelLineEdit->text();
}

QString ModelPropertiesDialog::getAuthor() const
{
    return ui->authorLineEdit->text();
}

QString ModelPropertiesDialog::getDescription() const
{
    return ui->descriptionTextEdit->toPlainText();
}
