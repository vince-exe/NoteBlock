#include "decrypt_dialog.h"
#include "ui_decrypt_dialog.h"

DecryptDialog::DecryptDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DecryptDialog) {
    ui->setupUi(this);
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

/* decrypt button clicked */
void DecryptDialog::on_browseBtn_clicked() {

}

/* done button clicked */
void DecryptDialog::on_doneBtn_clicked() {

}

