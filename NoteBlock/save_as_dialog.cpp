#include "save_as_dialog.h"
#include "ui_save_as_dialog.h"

#include <QKeyEvent>
#include <QModelIndex>
#include <QDir>
#include <QMessageBox>

#include <iostream>

#include "utilities.h"
#include "options_dialog.h"
#include "options.h"
#include "file_helper.h"
#include "msg_box_handler.h"
#include "main_dialog.h"

/* forms */
#include "save_as_utilities.h"

/* initialize all the static variables */
QString SaveAsDialog::dirName;

bool SaveAsDialog::cancelBtnPressed = false;

QString SaveAsDialog::selOption;

void SaveAsDialog::keyPressEvent(QKeyEvent *event) {
   if(event->key() == Qt::Key_Return && ui->pathBox->hasFocus())  {
      if(FileHelper::IsPathExist(ui->pathBox->text().toStdString())) {
          dirmodel->setRootPath(ui->pathBox->text());
          ui->treeView->setRootIndex(dirmodel->index(ui->pathBox->text()));
      }
      else {
          MsgBoxHandler::warningMessage("Warning", "Please enter a correct path");
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
    dirmodel->setReadOnly(false);
    dirmodel->setNameFilters({"*.txt"});
    dirmodel->setNameFilterDisables(false);

    ui->optionsComboBox->addItems({"New Folder", "Delete"});

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
    if(FileHelper::IsPathExist(ui->pathBox->text().toStdString())) {
        dirmodel->setRootPath(ui->pathBox->text());
        ui->treeView->setRootIndex(dirmodel->index(ui->pathBox->text()));
    }
    else {
        MsgBoxHandler::warningMessage("Warning", "Please enter a correct path");
        ui->pathBox->setText(Options::defaultPathOption);
        ui->treeView->setRootIndex(dirmodel->index(Options::defaultPathOption));
        return;
    }
}

void SaveAsDialog::on_doneBtn_clicked() {
    if(!ui->fileNameBox->text().length()) {
        MsgBoxHandler::warningMessage("Warning", "File name cannot be empty");
        return;
    }

    QString fileName = ui->fileNameBox->text();
    if(fileName.contains(".txt")) { fileName = fileName.remove(".txt"); }

    QString f_ = ui->pathBox->text() + "/" + fileName + ".txt";
    std::string fullPath = f_.toStdString();

    FILE* f = fopen(fullPath.c_str(), "r");

    /* check if the file already exist */
    if(f) {
        MsgBoxHandler::warningMessage("Warning", "There is already a file named " + ui->fileNameBox->text().toStdString());
        ui->fileNameBox->clear();

        OptionsDialog::fileCreated = false;
        return;
    }
    fclose(f);

    f = fopen(fullPath.c_str(), "w");
    if(!f) {
        MsgBoxHandler::warningMessage("Warning", "The application can't create the file in the given path");
        ui->fileNameBox->clear();
        ui->pathBox->setText(Options::defaultPathOption);
        ui->treeView->setRootIndex(dirmodel->index(Options::defaultPathOption));

        OptionsDialog::fileCreated = false;
        return;
    }

    /* store the content in the file */
    FileHelper::storeInformations(f, MainDialog::messageBuffer);
    fclose(f);

    ui->pathBox->setText(Options::defaultPathOption);
    ui->treeView->setRootIndex(dirmodel->index(Options::defaultPathOption));
    ui->fileNameBox->clear();

    MsgBoxHandler::infoMessage("Success", "Successfully saved the file");
    OptionsDialog::fileCreated = true;
    this->close();
}

/* execute the selected option */
void SaveAsDialog::on_doOptionBtn_clicked() {
    /* check if the user selected an item */
    QModelIndexList indexes = ui->treeView->selectionModel()->selectedIndexes();
    QModelIndex index;

    SaveAsUtilities saveUtilitiesDialog;

    QMessageBox confirmBox;
    QAbstractButton* noBtn;

    if (indexes.size() <= 0) {
        MsgBoxHandler::warningMessage("Warning", "Select a directory");
        return;
    }

    /* get the single index */
    index = indexes.at(0);

    switch(ui->optionsComboBox->currentIndex()) {
        /* New Folder */
        case 0:
            SaveAsDialog::selOption = "Add";
            saveUtilitiesDialog.setModal(true);
            saveUtilitiesDialog.show();
            saveUtilitiesDialog.exec();

            if(SaveAsDialog::cancelBtnPressed) { return; }

            if(QDir((ui->pathBox->text() + "\\" + SaveAsDialog::dirName)).exists()) {
                MsgBoxHandler::warningMessage("Warning", "There is already a folder with this name");
                return;
            }

            dirmodel->mkdir(index, SaveAsDialog::dirName);
            ui->treeView->setModel(dirmodel);

            MsgBoxHandler::infoMessage("Info", "New folder created");
            break;

        /* Delete Folder */
        case 1:
            confirmBox.setText(tr("The application will proceed with removing the folder, are you sure that you want to continue?"));
            confirmBox.addButton(tr("Yes"), QMessageBox::YesRole);
            noBtn = confirmBox.addButton(tr("No"), QMessageBox::YesRole);

            /* show the message box */
            confirmBox.exec();
            if(confirmBox.clickedButton() == noBtn) { return; }

            dirmodel->remove(index);
            ui->treeView->setModel(dirmodel);
            break;

        default:
            return;
    }
}
