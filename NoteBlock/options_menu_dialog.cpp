#include "options_menu_dialog.h"
#include "ui_options_menu_dialog.h"

/* forms */
#include "save_as_dialog.h"
#include "options_dialog.h"

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

}

/* Open button */
void OptionsMenuDialog::on_openBtn_clicked() {

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

