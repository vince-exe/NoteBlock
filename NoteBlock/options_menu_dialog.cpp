#include "options_menu_dialog.h"
#include "ui_options_menu_dialog.h"

OptionsMenuDialog::OptionsMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsMenuDialog) {
    ui->setupUi(this);

    ui->titleLabel->setAlignment(Qt::AlignCenter);
}

OptionsMenuDialog::~OptionsMenuDialog() {
    delete ui;
}
