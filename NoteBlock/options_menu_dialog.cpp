#include "options_menu_dialog.h"
#include "ui_options_menu_dialog.h"

#include <QMessageBox>

#include "main_dialog.h"
#include "options.h"
#include "crypt_system.h"
#include "file_helper.h"
#include "msg_box_handler.h"

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
            MsgBoxHandler::errorMessage("Error", "The application has failed to save the file");
            return;
        }

        /* store the informations in the opened file */
        FileHelper::storeInformations(f, MainDialog::messageBuffer);
        fclose(f);

        MsgBoxHandler::infoMessage("Success", "Successfully saved the file");
        return;
    }
    else {
        MsgBoxHandler::warningMessage("Warning", "This is a new file, so you have to select the 'save as' option to save it");
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
    OpenFileDialog::fileOpened = false;

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
        MsgBoxHandler::warningMessage("Warning", "You have to open a file to crypt it");
        return;
    }

    QMessageBox confirmBox;

    confirmBox.setText(tr("This option has been build for fun by the developer of the application, it doesn't guarantee a secure criptation of the file, dont' use it to crypt sensible informations"));
    confirmBox.addButton(tr("Ok"), QMessageBox::YesRole);

    QAbstractButton* noBtn = confirmBox.addButton(tr("No"), QMessageBox::YesRole);
    confirmBox.exec();

    if(confirmBox.clickedButton() == noBtn) { return; }

    /* generate the key and crypt the message */
    CryptSystem::generateKey();
    MainDialog::messageBuffer = CryptSystem::crypt(MainDialog::messageBuffer, CryptSystem::getKey());
    MainDialog::messageBuffer.append("\n");

    FILE* f = fopen(OpenFileDialog::filePath.toStdString().c_str(), "w");
    if(!f) {
        MsgBoxHandler::errorMessage("Error", "The application has failed to crypt the file");
        return;
    }

    FileHelper::storeInformations(f, MainDialog::messageBuffer);
    fclose(f);

    /* get the name of the cripted file without .txt */
    std::string criptedFileName = FileHelper::getFileName(OpenFileDialog::filePath.toStdString());
    criptedFileName = criptedFileName.erase(criptedFileName.find('.'), criptedFileName.length());

    /* get the name of the directory without the file name */
    std::string dirPath = FileHelper::getDirName(OpenFileDialog::filePath.toStdString());

    /* construct the path of the decryption key */
    std::string decKeyPath = dirPath + "/" + "pri_key_for_" + criptedFileName + ".txt";

    /* store the key in the same path of the cripted file */
    f = fopen(decKeyPath.c_str(), "w");
    if(!f) {
        MsgBoxHandler::errorMessage("Error", "The application has failed to crypt the file");
        return;
    }
    fprintf(f, "%d\n", CryptSystem::getKey());
    fclose(f);

    MsgBoxHandler::infoMessage("Success", "The application has successfully cripted the file, it has been generated a file that contain the key to decrypt the file in the same directory, keep it private");
    CryptSystem::criptedStatus = true;

    return;
}

/* decrypt a file */
void OptionsMenuDialog::on_decryptBtn_clicked() {

}
