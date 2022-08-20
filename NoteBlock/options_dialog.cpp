#include "options_dialog.h"
#include "ui_options_dialog.h"

#include <iostream>

#include "options_dialog_utilities.h"

#include "options.h"

/* forms */
#include "color_picker_dialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog) {
    ui->setupUi(this);

    /* set the default path */
    ui->defaultPath->setText(Options::defaultPathOption);
    /* set the default font */
    ui->fontBox->setValue(Options::defaultFontSize);
    /* set the default text color */

    ui->currentTextColorLabel->setStyleSheet("background-color: " + Options::defaultTextColor + ";" + "border: none");
    /* set the default background color */
    ui->currentBackColorLabel->setStyleSheet("background-color: " + Options::defaultBackColor + ";" + "border: none");

    /* check if the font style combo box, find the font */
    if(ui->fontStyleBox->findText(Options::defaultFontStyle) == -1) {
        ui->fontStyleBox->setEditText(Options::defaultFontStyle);
    }
    else {
        ui->fontStyleBox->setCurrentFont(QFont(Options::defaultFontStyle));
    }
}

OptionsDialog::~OptionsDialog() {
    delete ui;
}

/* reset button */
void OptionsDialog::on_resetBtn_clicked() {
    QMessageBox confirmBox;
    confirmBox.setText(tr("The application will proceed with resetting all the options to the default options, are you sure that you want to continue?"));
    confirmBox.addButton(tr("Yes"), QMessageBox::YesRole);
    QAbstractButton* noBtn = confirmBox.addButton(tr("No"), QMessageBox::YesRole);

    /* show the message box */
    confirmBox.exec();
    if(confirmBox.clickedButton() == noBtn) { return; }

    /* read from the default file system */
    FILE* f = fopen(Options::sysDefaultOptionsPath, "r");
    if(!f) {
        errorBox("Error", "The application has failed to load the system files");
        return;
    }
    Options::readOptions(f);
    fclose(f);

    /* store the default informations in the current options system file */
    f = fopen(Options::sysCurrentOptionsPath, "w");
    if(!f) {
        errorBox("Error", "The application has failed to load the system files");
        return;
    }

    Options::storeOptions(f);
    fclose(f);

    /* reset the widgets */
    ui->defaultPath->setText(Options::defaultPathOption);
    qDebug() << Options::defaultFontSize;
    ui->fontBox->setValue(Options::defaultFontSize);
    ui->fontStyleBox->setEditText(Options::defaultFontStyle);
    ui->currentTextColorLabel->setStyleSheet("background-color: " + Options::defaultTextColor);
    ui->currentBackColorLabel->setStyleSheet("background-color: " + Options::defaultBackColor);
}

/* done button */
void OptionsDialog::on_doneBtn_clicked() {
    if(!IsPathExist(ui->defaultPath->text().toStdString())) {
        warningMessage("Warning", "The entered path doesn't exist");
        ui->defaultPath->setText(Options::defaultPathOption);
        return;
    }

    /* update the options */
    Options::defaultPathOption = ui->defaultPath->text();
    Options::defaultFontSize = ui->fontBox->value();
    Options::defaultFontStyle = ui->fontStyleBox->currentText();

    FILE* f = fopen(Options::sysCurrentOptionsPath, "w");
    if(!f) {
        errorBox("Error", "The application has failed to load the system files");
        return;
    }

    Options::storeOptions(f);
    fclose(f);

    infoMessage("Success", "Successfully updated the options");
    this->close(); return;
}

/* when the users wants to change the text color */
void OptionsDialog::on_currentTextColorLabel_clicked() {
    changeTextColor = true;

    ColorPickerDialog colorPickerDialog;
    colorPickerDialog.setModal(true);
    colorPickerDialog.show();
    colorPickerDialog.exec();

    /* update the color labels */
    ui->currentTextColorLabel->setStyleSheet("background-color: " + Options::defaultTextColor);
    ui->currentBackColorLabel->setStyleSheet("background-color: " + Options::defaultBackColor);
}

/* when the user wants to change the background color */
void OptionsDialog::on_currentBackColorLabel_clicked() {
    changeTextColor = false;

    ColorPickerDialog colorPickerDialog;
    colorPickerDialog.setModal(true);
    colorPickerDialog.show();
    colorPickerDialog.exec();

    /* update the color labels */
    ui->currentTextColorLabel->setStyleSheet("background-color: " + Options::defaultTextColor);
    ui->currentBackColorLabel->setStyleSheet("background-color: " + Options::defaultBackColor);
}

