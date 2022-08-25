#include "decrypt_dialog.h"
#include "ui_decrypt_dialog.h"

#include "crypt_system.h"
#include "msg_box_handler.h"
#include "file_helper.h"
#include "main_dialog.h"

/* forms */
#include "open_file_dialog.h"

DecryptDialog::DecryptDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DecryptDialog) {
    ui->setupUi(this);

    CryptSystem::decryptStatus = false;
}

DecryptDialog::~DecryptDialog() {
    delete ui;
}

void DecryptDialog::on_decKeyBox_textChanged(const QString &arg1) {
    bool ok;
    arg1.toInt(&ok, 10);

    if(!ok) { ui->decKeyBox->backspace(); }
    if(arg1.length() > 4) { ui->decKeyBox->backspace(); }
}

/* browse button clicked */
void DecryptDialog::on_browseBtn_clicked() {
    OpenFileDialog openFileDialog;
    openFileDialog.setModal(true);
    openFileDialog.show();
    openFileDialog.exec();

    if(OpenFileDialog::fileOpened) {
        ui->filePathBox->setText(OpenFileDialog::filePath);
    }
}

/* decrypt button clicked */
void DecryptDialog::on_decryptBtn_clicked() {
    if(!ui->filePathBox->text().length() || !ui->decKeyBox->text().length()) {
        MsgBoxHandler::warningMessage("Warning", "You have to fill all the boxes to decrypt the file");
        return;
    }

    FILE* f = fopen(OpenFileDialog::filePath.toStdString().c_str(), "r");
    if(!f) {
        MsgBoxHandler::errorMessage("Error", "The application has failed to load the crypted file");
        return;
    }
    MainDialog::messageBuffer = CryptSystem::decrypt(ui->decKeyBox->text().toInt(), f);
    CryptSystem::decryptStatus = true;
    fclose(f);

    qDebug() << QString::fromStdString(MainDialog::messageBuffer);

    MsgBoxHandler::infoMessage("Success", "The application has successfully decripted the file");
    return;
}
