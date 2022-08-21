#include "folder_utilities.h"
#include "ui_folder_utilities.h"

#include "save_as_utilities.h"

FolderUtilities::FolderUtilities(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FolderUtilities) {
    ui->setupUi(this);

    Save
}

FolderUtilities::~FolderUtilities()
{
    delete ui;
}
