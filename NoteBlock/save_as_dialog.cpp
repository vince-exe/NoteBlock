#include "save_as_dialog.h"
#include "ui_save_as_dialog.h"

#include <QKeyEvent>
#include <QModelIndex>
#include <QDir>

#include <iostream>

#include "options_dialog_utilities.h"
#include "options.h"

/* forms */
#include "add_folder_dialog.h"

QString addFolderName;

void makePathCorrect(QString* path) {
    for(int i = 0; i < int(path->length()); i++) {
        if(path[i] == '/') { path[i] = '\\'; }
    }
}

void SaveAsDialog::keyPressEvent(QKeyEvent *event) {
   if(event->key() == Qt::Key_Return && ui->pathBox->hasFocus())  {
      if(IsPathExist(ui->pathBox->text().toStdString())) {
          dirmodel->setRootPath(ui->pathBox->text());
          ui->treeView->setRootIndex(dirmodel->index(ui->pathBox->text()));
      }
      else {
          warningMessage("Warning", "Please enter a correct path");
          ui->pathBox->setText(Options::defaultPathOption);
          ui->treeView->setRootIndex(dirmodel->index(Options::defaultPathOption));
          return;
      }
   }
}

SaveAsDialog::SaveAsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveAsDialog) {

    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    dirmodel->setRootPath(Options::defaultPathOption);
    dirmodel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);

    ui->optionsComboBox->addItems({"New Folder", "Rename Folder", "Delete Folder"});

    ui->treeView->setModel(dirmodel);
    ui->treeView->setRootIndex(dirmodel->index(Options::defaultPathOption));
    ui->treeView->setColumnWidth(0, 175);
    ui->treeView->header()->hideSection(1);

    ui->pathBox->setText(Options::defaultPathOption);
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
    dirmodel->setRootPath(Options::defaultPathOption);

    ui->treeView->setRootIndex(dirmodel->index(Options::defaultPathOption));
    ui->pathBox->setText(Options::defaultPathOption);
}

void SaveAsDialog::on_fileNameBox_textChanged(const QString &arg1) {
    if(arg1.toStdString().length() > 30) { ui->fileNameBox->backspace(); }
}

/* go to the searched path */
void SaveAsDialog::on_goBtn_clicked() {
    if(IsPathExist(ui->pathBox->text().toStdString())) {
        dirmodel->setRootPath(ui->pathBox->text());
        ui->treeView->setRootIndex(dirmodel->index(ui->pathBox->text()));
    }
    else {
        warningMessage("Warning", "Please enter a correct path");
        ui->pathBox->setText(Options::defaultPathOption);
        ui->treeView->setRootIndex(dirmodel->index(Options::defaultPathOption));
        return;
    }
}

void SaveAsDialog::on_doneBtn_clicked() {
    if(!ui->fileNameBox->text().length()) {
        warningMessage("Warning", "File name cannot be empty");
        return;
    }

    QString fullPath = ui->pathBox->text() + "\\" + ui->fileNameBox->text() + ".txt";
    fullPath.replace('/', '\\');
    std::string fullPathString = fullPath.toStdString();

    FILE* f = fopen(fullPathString.c_str(), "r");
    /* check if the file already exist */
    if(f) {
        warningMessage("Warning", "There is already a file named " + ui->fileNameBox->text().toStdString());
        ui->fileNameBox->clear();

        fileCreated = false;
        return;
    }
    fclose(f);

    f = fopen(fullPathString.c_str(), "w");
    if(!f) {
        warningMessage("Warning", "The application can't create the file in the given path");
        ui->fileNameBox->clear();
        ui->pathBox->setText(Options::defaultPathOption);
        ui->treeView->setRootIndex(dirmodel->index(Options::defaultPathOption));

        fileCreated = false;
        return;
    }

    /* store the content in the file */
    storeInformations(f, messageBuffer);
    fclose(f);

    ui->pathBox->setText(Options::defaultPathOption);
    ui->treeView->setRootIndex(dirmodel->index(Options::defaultPathOption));
    ui->fileNameBox->clear();

    infoMessage("Success", "Successfully saved the file");
    fileCreated = true;
    this->close();
}

/* execute the selected option */
void SaveAsDialog::on_doOptionBtn_clicked() {
    /* check if the user selected an item */
    QModelIndexList indexes = ui->treeView->selectionModel()->selectedIndexes();
    QModelIndex index;

    AddFolderDialog addFolderDialog;

    if (indexes.size() <= 0) {
        warningMessage("Warning", "Select a directory");
        return;
    }

    /* get the single index */
    index = indexes.at(0);

    switch(ui->optionsComboBox->currentIndex()) {
        /* New Folder */
        case 0:
            addFolderDialog.setModal(true);
            addFolderDialog.show();
            addFolderDialog.exec();
            break;

        /* Rename Folder */
        case 1:
            qDebug() << "rename folder";
            break;

        /* Delete Folder */
        case 2:
            qDebug() << "delete folder";
            break;

        default:
            return;
    }
}
