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
        ui->redSpinBox->setValue(defTextColorR);
        ui->reedSlider->setValue(defTextColorR);

        ui->greenSpinBox->setValue(defTextColorG);
        ui->greenSlider->setValue(defTextColorG);

        ui->blueSpinBox->setValue(defTextColorB);
        ui->blueSlider->setValue(defTextColorB);
    }
    else {
        ui->redSpinBox->setValue(defBackColorR);
        ui->reedSlider->setValue(defBackColorR);

        ui->greenSpinBox->setValue(defBackColorG);
        ui->greenSlider->setValue(defBackColorG);

        ui->blueSpinBox->setValue(defBackColorB);
        ui->blueSlider->setValue(defBackColorB);
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

/* reset button */
void ColorPickerDialog::on_resetBtn_clicked() {
    QMessageBox confirmBox;

    confirmBox.setText(tr("The application will proceed with resetting the options, are u sure that you want to continue?"));
    confirmBox.addButton(tr("Yes"), QMessageBox::YesRole);

    QAbstractButton* noBtn = confirmBox.addButton(tr("No"), QMessageBox::YesRole);
    confirmBox.exec();

    if(confirmBox.clickedButton() == noBtn) { return; }

    if(changeTextColor) {
        defTextColorR = 218;
        defTextColorG = 218;
        defTextColorB = 218;

        defaultTextColor = "rgb(218,218,218)";

        ui->redSpinBox->setValue(defTextColorR);
        ui->reedSlider->setValue(defTextColorR);

        ui->greenSpinBox->setValue(defTextColorG);
        ui->greenSlider->setValue(defTextColorG);

        ui->blueSpinBox->setValue(defTextColorB);
        ui->blueSlider->setValue(defTextColorB);
    }
    else {
        defBackColorR = 39;
        defBackColorG = 39;
        defBackColorB = 39;

        defaultBackColor = "rgb(39,39,39)";

        ui->redSpinBox->setValue(defBackColorR);
        ui->reedSlider->setValue(defBackColorR);

        ui->greenSpinBox->setValue(defBackColorG);
        ui->greenSlider->setValue(defBackColorG);

        ui->blueSpinBox->setValue(defBackColorB);
        ui->blueSlider->setValue(defBackColorB);
    }

    ui->resultLabel->setStyleSheet("color: " + defaultTextColor + ";" + "background-color: " + defaultBackColor + ";font: 600 16pt Segoe UI Semibold");

}

/* Done button */
void ColorPickerDialog::on_doneBn_clicked() {
    if(changeTextColor) {
        defaultTextColor = "rgb(" + QString::number(ui->redSpinBox->value()) + ",";
        defaultTextColor.append(QString::number(ui->greenSpinBox->value()) + ",");
        defaultTextColor.append(QString::number(ui->blueSpinBox->value()) + ")");

        defTextColorR = ui->redSpinBox->value();
        defTextColorG = ui->greenSpinBox->value();
        defTextColorB = ui->blueSpinBox->value();
    }
    else {
        defaultBackColor = "rgb(" + QString::number(ui->redSpinBox->value()) + ",";
        defaultBackColor.append(QString::number(ui->greenSpinBox->value()) + ",");
        defaultBackColor.append(QString::number(ui->blueSpinBox->value()) + ")");

        defBackColorR = ui->redSpinBox->value();
        defBackColorG = ui->greenSpinBox->value();
        defBackColorB = ui->blueSpinBox->value();
    }

    this->close(); return;
}

