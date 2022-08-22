#include "options_menu_dialog.h"
#include "ui_options_menu_dialog.h"

#include "utilities.h"

#include "open_file_dialog.h"

/* forms */
#include "save_as_dialog.h"
#include "options_dialog.h"
#include "open_file_dialog.h"

#include "main_dialog.h"

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

}

/* options button */
void OptionsMenuDialog::on_optionsBtn_clicked() {
    OptionsDialog optionsDialog;
    optionsDialog.setModal(true);
    optionsDialog.show();
    optionsDialog.exec();
}

