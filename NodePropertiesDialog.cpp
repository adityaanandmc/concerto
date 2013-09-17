#include "NodePropertiesDialog.h"
#include "ui_nodepropertiesdialog.h"

NodePropertiesDialog::NodePropertiesDialog(const IAttributable *theAttributes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NodePropertiesDialog)
{
    ui->setupUi(this);

    if (theAttributes) {
        std::string value = theAttributes->getAttribute("Design Scope");

        if (std::string("Organization (black-box)") == value) {
            ui->designScopeComboBox->setCurrentIndex(0);
        } else if (std::string("Organization (white-box)") == value) {
            ui->designScopeComboBox->setCurrentIndex(1);
        } else if (std::string("System (black-box)") == value) {
            ui->designScopeComboBox->setCurrentIndex(2);
        } else if (std::string("System (white-box)") == value) {
            ui->designScopeComboBox->setCurrentIndex(3);
        } else if (std::string("Component") == value) {
            ui->designScopeComboBox->setCurrentIndex(4);
        }

        value = theAttributes->getAttribute("Goal Level");

        if (std::string("Very High Summary") == value) {
            ui->goalLevelComboBox->setCurrentIndex(0);
        } else if (std::string("High Summary") == value) {
            ui->goalLevelComboBox->setCurrentIndex(1);
        } else if (std::string("User Goal") == value) {
            ui->goalLevelComboBox->setCurrentIndex(2);
        } else if (std::string("Subfunction") == value) {
            ui->goalLevelComboBox->setCurrentIndex(3);
        } else if (std::string("Too Low") == value) {
            ui->goalLevelComboBox->setCurrentIndex(4);
        }

        ui->mainSuccessScenarioTextBox->setHtml(tr(theAttributes->getAttribute("Main Success Scenario").c_str()));
        ui->minimalGuaranteesTextBox->setHtml(tr(theAttributes->getAttribute("Minimal Guarantees").c_str()));
        ui->successGuaranteesTextBox->setHtml(tr(theAttributes->getAttribute("Success Guarantees").c_str()));
        ui->notesTextBox->setHtml(tr(theAttributes->getAttribute("Notes").c_str()));
        ui->triggerTextBox->setHtml(tr(theAttributes->getAttribute("Trigger").c_str()));
        ui->preConditionsTextBox->setHtml(tr(theAttributes->getAttribute("Pre Conditions").c_str()));
    }
}

NodePropertiesDialog::~NodePropertiesDialog()
{
    delete ui;
}

const std::map<std::string, std::string> NodePropertiesDialog::getSavedAttributes() const
{
    std::map<std::string, std::string> attributes;

    attributes.insert(std::make_pair<std::string, std::string>("Design Scope", ui->designScopeComboBox->currentText().toStdString().c_str()));
    attributes.insert(std::make_pair<std::string, std::string>("Goal Level", ui->goalLevelComboBox->currentText().toStdString().c_str()));
    attributes.insert(std::make_pair<std::string, std::string>("Main Success Scenario", ui->mainSuccessScenarioTextBox->toHtml().toHtmlEscaped().toStdString().c_str()));
    attributes.insert(std::make_pair<std::string, std::string>("Success Guarantees", ui->successGuaranteesTextBox->toHtml().toHtmlEscaped().toStdString().c_str()));
    attributes.insert(std::make_pair<std::string, std::string>("Minimal Guarantees", ui->minimalGuaranteesTextBox->toHtml().toHtmlEscaped().toStdString().c_str()));
    attributes.insert(std::make_pair<std::string, std::string>("Notes", ui->notesTextBox->toHtml().toHtmlEscaped().toStdString().c_str()));
    attributes.insert(std::make_pair<std::string, std::string>("Trigger", ui->triggerTextBox->toHtml().toHtmlEscaped().toStdString().c_str()));
    attributes.insert(std::make_pair<std::string, std::string>("Pre Conditions", ui->preConditionsTextBox->toHtml().toHtmlEscaped().toStdString().c_str()));

    return attributes;
}
