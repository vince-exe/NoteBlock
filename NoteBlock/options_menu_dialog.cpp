#include "options_menu_dialog.h"
#include "ui_options_menu_dialog.h"

#include "utilities.h"
#include "main_dialog.h"
#include "options.h"

/* forms */
#include "save_as_dialog.h"
#include "options_dialog.h"
#include "open_file_dialog.h"
#include "open_file_dialog.h"

OptionsMenuDialog::OptionsMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsMenuDialog) {

    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    ui->titleLabel->setAlignment(Qt::AlignCenter);
}

OptionsMenuDialog::~OptionsMenuDialog() {
    delete ui;
}

/* Save as */
void OptionsMenuDialog::on_saveAsBtn_clicked() {
    SaveAsDialog saveAsDialog;
    saveAsDialog.setModal(true);
    saveAsDialog.show();
    saveAsDialog.exec();
}

/* Save */
void OptionsMenuDialog::on_saveBtn_clicked() {
    if(OpenFileDialog::fileOpened) {
        FILE* f = fopen(OpenFileDialog::filePath.toStdString().c_str(), "w");
        if(!f) {
            errorBox("Error", "The application has failed to save the file");
            return;
        }

        /* store the informations in the opened file */
        storeInformations(f, MainDialog::messageBuffer);
        fclose(f);

        infoMessage("Success", "Successfully saved the file");
        return;
    }
    else {
        warningMessage("Warning", "This is a new file, so you have to select the 'save as' option to save it");
        return;
    }
}

/* Open button */
void OptionsMenuDialog::on_openBtn_clicked() {
    OpenFileDialog openFileDialog;
    openFileDialog.setModal(true);
    openFileDialog.show();
    openFileDialog.exec();

    /* if the application has successfully opened the file */
    if(OpenFileDialog::fileOpened) {
        this->close(); return;
    }
}

/* New button */
void OptionsMenuDialog::on_newBtn_clicked() {
    QMessageBox confirmBox;

    confirmBox.setText(tr("If you have applied new changes, the application will ignore them and create a new file, are you sure?"));
    confirmBox.addButton(tr("Yes"), QMessageBox::YesRole);

    QAbstractButton* noBtn = confirmBox.addButton(tr("No"), QMessageBox::YesRole);
    confirmBox.exec();

    if(confirmBox.clickedButton() == noBtn) { return; }

    /* reset all the informations */
    MainDialog::messageBuffer = "";
    Options::wantsNewFile = true;

    this->close(); return;
}

/* options button */
void OptionsMenuDialog::on_optionsBtn_clicked() {
    OptionsDialog optionsDialog;
    optionsDialog.setModal(true);
    optionsDialog.show();
    optionsDialog.exec();
}

/* crypt a file */
void OptionsMenuDialog::on_cryptBtn_clicked() {
    if(!OpenFileDialog::fileOpened) {
        warningMessage("Warning", "You have to open a file to crypt it");
        return;
    }
}

/* decrypt a file */
void OptionsMenuDialog::on_decryptBtn_clicked() {

}
