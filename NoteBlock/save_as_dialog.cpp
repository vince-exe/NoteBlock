#include "save_as_dialog.h"
#include "ui_save_as_dialog.h"

#include <QKeyEvent>

#include <windows.h>
#include <lmcons.h>
#include <iostream>

#include "options_dialog_utilities.h"

QString defaultPath = "";

void SaveAsDialog::keyPressEvent(QKeyEvent *event) {
   if(event->key() == Qt::Key_Return && ui->pathBox->hasFocus())  {
      if(IsPathExist(ui->pathBox->text().toStdString())) {
          dirmodel->setRootPath(ui->pathBox->text());
          ui->treeView->setRootIndex(dirmodel->index(ui->pathBox->text()));
      }
      else {
          warningMessage("Warning", "Please enter a correct path");
          ui->pathBox->setText(defaultPath);
          return;
      }
   }
}

SaveAsDialog::SaveAsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveAsDialog) {

    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    TCHAR username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;

    GetUserName((TCHAR*)username, &username_len);

    QString hostName = QString::fromWCharArray(username);
    defaultPath = "C:/Users/" + hostName;

    dirmodel->setRootPath(defaultPath);
    dirmodel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);

    ui->treeView->setModel(dirmodel);
    ui->treeView->setRootIndex(dirmodel->index(defaultPath));
    ui->treeView->setColumnWidth(0, 175);
    ui->treeView->header()->hideSection(1);

    ui->pathBox->setText(defaultPath);
}

SaveAsDialog::~SaveAsDialog() {
    delete ui;
}

void SaveAsDialog::on_treeView_clicked(const QModelIndex &index) {
    /* set the current path of the absolute path of the selected folder */
    ui->pathBox->setText(dirmodel->filePath(index));
}

void SaveAsDialog::on_pushButton_clicked() {
    /* set the default path as root path */
    dirmodel->setRootPath(defaultPath);

    ui->treeView->setRootIndex(dirmodel->index(defaultPath));
    ui->pathBox->setText(defaultPath);
}

