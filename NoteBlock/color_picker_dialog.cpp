#include "color_picker_dialog.h"
#include "ui_color_picker_dialog.h"

#include "utilities.h"
#include "options_dialog.h"
#include "options.h"
#include "msg_box_handler.h"

#include <QMessageBox>

QString getRGB(int r, int g, int b) {
    QString color = "rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ")";

    return color;
}

ColorPickerDialog::ColorPickerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorPickerDialog) {
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    /* align the items */
    ui->resultLabel->setAlignment(Qt::AlignCenter);
    ui->redSpinBox->setAlignment(Qt::AlignCenter);
    ui->greenSpinBox->setAlignment(Qt::AlignCenter);
    ui->blueSpinBox->setAlignment(Qt::AlignCenter);

    if(OptionsDialog::changeTextColor) {
        ui->redSpinBox->setValue(Options::defTextColorG);
        ui->reedSlider->setValue(Options::defTextColorR);

        ui->greenSpinBox->setValue(Options::defTextColorG);
        ui->greenSlider->setValue(Options::defTextColorG);

        ui->blueSpinBox->setValue(Options::defTextColorB);
        ui->blueSlider->setValue(Options::defTextColorB);
    }
    else {
        ui->redSpinBox->setValue(Options::defBackColorR);
        ui->reedSlider->setValue(Options::defBackColorR);

        ui->greenSpinBox->setValue(Options::defBackColorG);
        ui->greenSlider->setValue(Options::defBackColorG);

        ui->blueSpinBox->setValue(Options::defBackColorB);
        ui->blueSlider->setValue(Options::defBackColorB);
    }
}

ColorPickerDialog::~ColorPickerDialog() {
    delete ui;
}

/* Edit Sliders */
void ColorPickerDialog::on_reedSlider_valueChanged(int value) {
    ui->redSpinBox->setValue(value);

    if(OptionsDialog::changeTextColor) {
        ui->resultLabel->setStyleSheet("color: " + getRGB(value, ui->greenSpinBox->value(), ui->blueSpinBox->value()) + + ";" + "background-color: " + Options::defaultBackColor + ";font: 600 16pt Segoe UI Semibold");
    }
    else {
        ui->resultLabel->setStyleSheet("background-color: " + getRGB(value, ui->greenSpinBox->value(), ui->blueSpinBox->value()) + ";" + "color: " + Options::defaultTextColor + ";font: 600 16pt Segoe UI Semibold");
    }
}

void ColorPickerDialog::on_greenSlider_valueChanged(int value) {
    ui->greenSpinBox->setValue(value);

    if(OptionsDialog::changeTextColor) {
        ui->resultLabel->setStyleSheet("color: " + getRGB(ui->redSpinBox->value(), value, ui->blueSpinBox->value()) + ";" + "background-color: " + Options::defaultBackColor + ";font: 600 16pt Segoe UI Semibold");
    }
    else {
        ui->resultLabel->setStyleSheet("background-color: " + getRGB(ui->redSpinBox->value(), value, ui->blueSpinBox->value()) + ";" + "color: " + Options::defaultTextColor + ";font: 600 16pt Segoe UI Semibold");
    }
}

void ColorPickerDialog::on_blueSlider_valueChanged(int value) {
    ui->blueSpinBox->setValue(value);

    if(OptionsDialog::changeTextColor) {
        ui->resultLabel->setStyleSheet("color: " + getRGB(ui->redSpinBox->value(), ui->greenSpinBox->value(), value) + ";" + "background-color: " + Options::defaultBackColor + ";font: 600 16pt Segoe UI Semibold");
    }
    else {
        ui->resultLabel->setStyleSheet("background-color: " + getRGB(ui->redSpinBox->value(), ui->greenSpinBox->value(), value) + ";" + "color: " + Options::defaultTextColor + ";font: 600 16pt Segoe UI Semibold");
    }
}


/* Edit SpinBoxes */
void ColorPickerDialog::on_redSpinBox_valueChanged(int arg1) {
    ui->reedSlider->setValue(arg1);

    if(OptionsDialog::changeTextColor) {
        ui->resultLabel->setStyleSheet("color: " + getRGB(arg1, ui->greenSpinBox->value(), ui->blueSpinBox->value()) + ";" + "background-color: " + Options::defaultBackColor + ";font: 600 16pt Segoe UI Semibold");
    }
    else {
        ui->resultLabel->setStyleSheet("background-color: " + getRGB(arg1, ui->greenSpinBox->value(), ui->blueSpinBox->value()) + ";" + "color: " + Options::defaultTextColor + ";font: 600 16pt Segoe UI Semibold");
    }
}

void ColorPickerDialog::on_greenSpinBox_valueChanged(int arg1) {
    ui->greenSlider->setValue(arg1);

    if(OptionsDialog::changeTextColor) {
        ui->resultLabel->setStyleSheet("color: " + getRGB(ui->redSpinBox->value(), arg1, ui->blueSpinBox->value()) + ";" + "background-color: " + Options::defaultBackColor + ";font: 600 16pt Segoe UI Semibold");
    }
    else {
        ui->resultLabel->setStyleSheet("background-color: " + getRGB(ui->redSpinBox->value(), arg1, ui->blueSpinBox->value()) + ";" + "color: " + Options::defaultTextColor + ";font: 600 16pt Segoe UI Semibold");
    }
}

void ColorPickerDialog::on_blueSpinBox_valueChanged(int arg1) {
    ui->blueSlider->setValue(arg1);

    if(OptionsDialog::changeTextColor) {
        ui->resultLabel->setStyleSheet("color: " + getRGB(ui->redSpinBox->value(), ui->greenSpinBox->value(), arg1) + ";" + "background-color: " + Options::defaultBackColor + ";font: 600 16pt Segoe UI Semibold");
    }
    else {
        ui->resultLabel->setStyleSheet("background-color: " + getRGB(ui->redSpinBox->value(), ui->greenSpinBox->value(), arg1) + ";" + "color: " + Options::defaultTextColor + ";font: 600 16pt Segoe UI Semibold");
    }
}

/* reset button */
void ColorPickerDialog::on_resetBtn_clicked() {
    QMessageBox confirmBox;

    confirmBox.setText(tr("The application will proceed with resetting the colors, are u sure that you want to continue?"));
    confirmBox.addButton(tr("Yes"), QMessageBox::YesRole);

    QAbstractButton* noBtn = confirmBox.addButton(tr("No"), QMessageBox::YesRole);
    confirmBox.exec();

    if(confirmBox.clickedButton() == noBtn) { return; }

    FILE* f = fopen(Options::sysDefaultOptionsPath, "r");
    if(!f) {
        MsgBoxHandler::errorMessage("Error", "Fatal Error");
        return;
    }

    /* re-read the options, store the default options in the class Options */
    Options::readOptions(f);
    fclose(f);

    f = fopen(Options::sysCurrentOptionsPath, "w");
    if(!f) {
        MsgBoxHandler::errorMessage("Error", "Fatal Error");
        return;
    }

    /* write in the current settings file the options */
    Options::storeOptions(f);
    fclose(f);

    ui->resultLabel->setStyleSheet("color: " + Options::defaultTextColor + ";" + "background-color: " + Options::defaultBackColor + ";font: 600 16pt Segoe UI Semibold");
    this->close(); return;
}

/* Done button */
void ColorPickerDialog::on_doneBn_clicked() {
    /* store the informations in the file */
    FILE* f = fopen(Options::sysCurrentOptionsPath, "w");
    if(!f) {
        MsgBoxHandler::errorMessage("Error", "The application has failed to load the system files");
        return;
    }

    if(OptionsDialog::changeTextColor) {
        Options::defaultTextColor = "rgb(" + QString::number(ui->redSpinBox->value()) + ",";
        Options::defaultTextColor.append(QString::number(ui->greenSpinBox->value()) + ",");
        Options::defaultTextColor.append(QString::number(ui->blueSpinBox->value()) + ")");

        Options::defTextColorR = ui->redSpinBox->value();
        Options::defTextColorG = ui->greenSpinBox->value();
        Options::defTextColorB = ui->blueSpinBox->value();
    }
    else {
        Options::defaultBackColor = "rgb(" + QString::number(ui->redSpinBox->value()) + ",";
        Options::defaultBackColor.append(QString::number(ui->greenSpinBox->value()) + ",");
        Options::defaultBackColor.append(QString::number(ui->blueSpinBox->value()) + ")");

        Options::defBackColorR = ui->redSpinBox->value();
        Options::defBackColorG = ui->greenSpinBox->value();
        Options::defBackColorB = ui->blueSpinBox->value();
    }

    Options::storeOptions(f);
    fclose(f);

    this->close();
    return;
}
