#include "options_dialog.h"
#include "ui_options_dialog.h"

#include <iostream>

#include "options_dialog_utilities.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog) {
    ui->setupUi(this);

    /* set the default path */
    ui->defaultPath->setText(defaultPathOption);
    /* set the default font */
    ui->fontBox->setValue(defaultFontSize);
    /* set the default text color */
    ui->currentTextColorLabel->setStyleSheet("background-color: " + defaultTextColor);
    /* set the default background color */
    ui->currentBackColorLabel->setStyleSheet("background-color: " + defaultBackColor);
}

OptionsDialog::~OptionsDialog() {
    delete ui;
}
