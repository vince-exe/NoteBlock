#include "options_dialog.h"
#include "ui_options_dialog.h"

#include <iostream>

#include "options_dialog_utilities.h"

/* forms */
#include "color_picker_dialog.h"

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
    /* set the font style box */
    ui->fontStyleBox->setCurrentFont(QFont(defaultFontStyle));
}

OptionsDialog::~OptionsDialog() {
    delete ui;
}

/* reset button */
void OptionsDialog::on_resetBtn_clicked() {

}

/* done button */
void OptionsDialog::on_doneBtn_clicked() {

}

/* when the users wants to change the text color */
void OptionsDialog::on_currentTextColorLabel_clicked() {
    changeTextColor = true;

    ColorPickerDialog colorPickerDialog;
    colorPickerDialog.setModal(true);
    colorPickerDialog.show();
    colorPickerDialog.exec();

    /* reset the text color label */
    ui->currentTextColorLabel->setStyleSheet("background-color: " + defaultTextColor);
}

/* when the user wants to change the background color */
void OptionsDialog::on_currentBackColorLabel_clicked() {
    changeTextColor = false;

    ColorPickerDialog colorPickerDialog;
    colorPickerDialog.setModal(true);
    colorPickerDialog.show();
    colorPickerDialog.exec();

    /* reset the background color label */
    ui->currentBackColorLabel->setStyleSheet("background-color: " + defaultBackColor);
}

