#include "add_folder_dialog.h"
#include "ui_add_folder_dialog.h"

AddFolderDialog::AddFolderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFolderDialog)
{
    ui->setupUi(this);
}

AddFolderDialog::~AddFolderDialog()
{
    delete ui;
}
