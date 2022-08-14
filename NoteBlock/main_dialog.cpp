#include "main_dialog.h"
#include "ui_main_dialog.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog) {
    ui->setupUi(this);

    ui->widthLabel->setText("Width: " + QString::number(this->size().width()));
    ui->heightLabel->setText("Height: " + QString::number(this->size().height()));
    ui->zoomLabel->setText("Zoom: 100%");
}

MainDialog::~MainDialog() {
    delete ui;
}

void MainDialog::resizeEvent(QResizeEvent *event) {
    ui->textBox->setGeometry(0, 0, event->size().width(), event->size().height());
    ui->infoLabel->setGeometry(0, event->size().height() - 50, event->size().width(), 50);

    ui->heightLabel->setGeometry(event->size().width() - 151, ui->infoLabel->geometry().y() + 10, 111, 31);
    ui->widthLabel->setGeometry(ui->heightLabel->geometry().x() - 170, ui->infoLabel->geometry().y() + 10, 111, 31);
    ui->zoomLabel->setGeometry(ui->widthLabel->geometry().x() - 170, ui->infoLabel->geometry().y() + 10, 111, 31);

    ui->widthLabel->setText("Width: " + QString::number(event->size().width()));
    ui->heightLabel->setText("Height: " + QString::number(event->size().height()));
}
