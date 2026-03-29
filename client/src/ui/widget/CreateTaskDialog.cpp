#include "ui/widget/CreateTaskDialog.h"
#include "LanguageManager.h"

CreateTaskDialog::CreateTaskDialog(QWidget* parent)
    : QDialog(parent) {

    setWindowTitle(LanguageManager::tr("task.create"));
    resize(300, 250);

    QFormLayout* layout = new QFormLayout(this);

    titleInput = new QLineEdit(this);
    tagInput = new QLineEdit(this);
    assignedToInput = new QLineEdit(this);
    groupIdInput = new QLineEdit(this);
    completedCheck = new QCheckBox(LanguageManager::tr("task.completed"), this);

    btnCreate = new QPushButton(LanguageManager::tr("action.create"), this);
    btnCancel = new QPushButton(LanguageManager::tr("action.cancel"), this);

    layout->addRow(LanguageManager::tr("task.form.title"), titleInput);
    layout->addRow(LanguageManager::tr("task.form.tag"), tagInput);
    layout->addRow(LanguageManager::tr("task.form.assigned_to_id"), assignedToInput);
    layout->addRow(LanguageManager::tr("task.form.group_id"), groupIdInput);
    layout->addRow(completedCheck);
    layout->addRow(btnCreate, btnCancel);

    connect(btnCreate, &QPushButton::clicked, this, &CreateTaskDialog::handleCreate);
    connect(btnCancel, &QPushButton::clicked, this, &CreateTaskDialog::reject);
}

void CreateTaskDialog::handleCreate() {
    int id = rand();

    Task task(
        id,
        titleInput->text().toStdString(),
        tagInput->text().toStdString(),
        completedCheck->isChecked(),
        1,
        assignedToInput->text().toInt(),
        groupIdInput->text().toInt()
    );

    emit taskCreated(task);
    accept(); 
}