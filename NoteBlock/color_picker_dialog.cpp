#include "color_picker_dialog.h"
#include "ui_color_picker_dialog.h"

#include "options_dialog_utilities.h"

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

    if(changeTextColor) {
        ui->redSpinBox->setValue(defTextColorInteger.toInt());
        ui->reedSlider->setValue(defTextColorInteger.toInt());

        ui->greenSpinBox->setValue(defTextColorInteger.toInt());
        ui->greenSlider->setValue(defTextColorInteger.toInt());

        ui->blueSpinBox->setValue(defTextColorInteger.toInt());
        ui->blueSlider->setValue(defTextColorInteger.toInt());
    }
    else {
        ui->redSpinBox->setValue(defBackColorInteger.toInt());
        ui->reedSlider->setValue(defBackColorInteger.toInt());

        ui->greenSpinBox->setValue(defBackColorInteger.toInt());
        ui->greenSlider->setValue(defBackColorInteger.toInt());

        ui->blueSpinBox->setValue(defBackColorInteger.toInt());
        ui->blueSlider->setValue(defBackColorInteger.toInt());
    }
}

ColorPickerDialog::~ColorPickerDialog() {
    delete ui;
}

/* Edit Sliders */
void ColorPickerDialog::on_reedSlider_valueChanged(int value) {
    ui->redSpinBox->setValue(value);

    if(changeTextColor) {
        ui->resultLabel->setStyleSheet("color: " + getRGB(value, ui->greenSpinBox->value(), ui->blueSpinBox->value()) + + ";" + "background-color: " + defaultBackColor + ";font: 600 16pt Segoe UI Semibold");
    }
    else {
        ui->resultLabel->setStyleSheet("background-color: " + getRGB(value, ui->greenSpinBox->value(), ui->blueSpinBox->value()) + ";" + "color: " + defaultTextColor + ";font: 600 16pt Segoe UI Semibold");
    }
}

void ColorPickerDialog::on_greenSlider_valueChanged(int value) {
    ui->greenSpinBox->setValue(value);

    if(changeTextColor) {
        ui->resultLabel->setStyleSheet("color: " + getRGB(ui->redSpinBox->value(), value, ui->blueSpinBox->value()) + ";" + "background-color: " + defaultBackColor + ";font: 600 16pt Segoe UI Semibold");
    }
    else {
        ui->resultLabel->setStyleSheet("background-color: " + getRGB(ui->redSpinBox->value(), value, ui->blueSpinBox->value()) + ";" + "color: " + defaultTextColor + ";font: 600 16pt Segoe UI Semibold");
    }
}

void ColorPickerDialog::on_blueSlider_valueChanged(int value) {
    ui->blueSpinBox->setValue(value);

    if(changeTextColor) {
        ui->resultLabel->setStyleSheet("color: " + getRGB(ui->redSpinBox->value(), ui->greenSpinBox->value(), value) + ";" + "background-color: " + defaultBackColor + ";font: 600 16pt Segoe UI Semibold");
    }
    else {
        ui->resultLabel->setStyleSheet("background-color: " + getRGB(ui->redSpinBox->value(), ui->greenSpinBox->value(), value) + ";" + "color: " + defaultTextColor + ";font: 600 16pt Segoe UI Semibold");
    }
}


/* Edit SpinBoxes */
void ColorPickerDialog::on_redSpinBox_valueChanged(int arg1) {
    ui->reedSlider->setValue(arg1);

    if(changeTextColor) {
        ui->resultLabel->setStyleSheet("color: " + getRGB(arg1, ui->greenSpinBox->value(), ui->blueSpinBox->value()) + ";" + "background-color: " + defaultBackColor + ";font: 600 16pt Segoe UI Semibold");
    }
    else {
        ui->resultLabel->setStyleSheet("background-color: " + getRGB(arg1, ui->greenSpinBox->value(), ui->blueSpinBox->value()) + ";" + "color: " + defaultTextColor + ";font: 600 16pt Segoe UI Semibold");
    }
}

void ColorPickerDialog::on_greenSpinBox_valueChanged(int arg1) {
    ui->greenSlider->setValue(arg1);

    if(changeTextColor) {
        ui->resultLabel->setStyleSheet("color: " + getRGB(ui->redSpinBox->value(), arg1, ui->blueSpinBox->value()) + ";" + "background-color: " + defaultBackColor + ";font: 600 16pt Segoe UI Semibold");
    }
    else {
        ui->resultLabel->setStyleSheet("background-color: " + getRGB(ui->redSpinBox->value(), arg1, ui->blueSpinBox->value()) + ";" + "color: " + defaultTextColor + ";font: 600 16pt Segoe UI Semibold");
    }
}

void ColorPickerDialog::on_blueSpinBox_valueChanged(int arg1) {
    ui->blueSlider->setValue(arg1);

    if(changeTextColor) {
        ui->resultLabel->setStyleSheet("color: " + getRGB(ui->redSpinBox->value(), ui->greenSpinBox->value(), arg1) + ";" + "background-color: " + defaultBackColor + ";font: 600 16pt Segoe UI Semibold");
    }
    else {
        ui->resultLabel->setStyleSheet("background-color: " + getRGB(ui->redSpinBox->value(), ui->greenSpinBox->value(), arg1) + ";" + "color: " + defaultTextColor + ";font: 600 16pt Segoe UI Semibold");
    }
}
