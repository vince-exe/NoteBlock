#include "save_as_utilities.h"
#include "ui_save_as_utilities.h"

#include "save_as_dialog.h"

#include <QKeyEvent>

SaveAsUtilities::SaveAsUtilities(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveAsUtilities) {
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    if(SaveAsDialog::selOption == "Add") {
        this->setWindowTitle("Add Folder");
    }

    SaveAsDialog::cancelBtnPressed = true;
}

SaveAsUtilities::~SaveAsUtilities() {
    delete ui;
}

/* check that the user doesn't pass the limit od characters for the folder name */
void SaveAsUtilities::on_folderNameBox_textChanged(const QString &arg1) {
    if(arg1.length() > SaveAsDialog::maxDirName) { ui->folderNameBox->backspace(); }
}

void SaveAsUtilities::on_cancelBtn_clicked() {
    SaveAsDialog::cancelBtnPressed = true;
    this->close(); return;
}

void SaveAsUtilities::on_doneBtn_clicked() {
    SaveAsDialog::dirName = ui->folderNameBox->text();
    SaveAsDialog::cancelBtnPressed = false;

    this->close(); return;
}

void SaveAsUtilities::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Return) {
        this->on_doneBtn_clicked(); return;
    }
}
