#include "main_dialog.h"
#include "ui_main_dialog.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog) {
    ui->setupUi(this);
}

MainDialog::~MainDialog() {
    delete ui;
}

void MainDialog::resizeEvent(QResizeEvent *event) {
    ui->textBox->setGeometry(0, 0, event->size().width(), event->size().height());
    ui->infoLabel->setGeometry(0, event->size().height() - 50, event->size().width(), 50);
}
