#include "open_file_dialog.h"
#include "ui_open_file_dialog.h"

#include <QMessageBox>

#include "options.h"
#include "utilities.h"
#include "file_helper.h"
#include "msg_box_handler.h"

/* forms */
#include "save_as_utilities.h"
#include "save_as_dialog.h"
#include "main_dialog.h"

bool OpenFileDialog::fileOpened = false;

QString OpenFileDialog::filePath;

OpenFileDialog::OpenFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFileDialog) {

    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    dirFilemodel->setRootPath(Options::defaultPathOption);
    dirFilemodel->setReadOnly(false);
    dirFilemodel->setNameFilters({"*.txt"});
    dirFilemodel->setNameFilterDisables(false);

    ui->optionsComboBox->addItems({"New Folder", "Delete"});

    ui->treeView->setModel(dirFilemodel);
    ui->treeView->setRootIndex(dirFilemodel->index(Options::defaultPathOption));
    ui->treeView->setColumnWidth(0, 175);
    ui->treeView->header()->hideSection(1);

    ui->pathBox->setText(Options::defaultPathOption);
    OpenFileDialog::fileOpened = false;
}

OpenFileDialog::~OpenFileDialog() {
    delete ui;
}

void OpenFileDialog::on_treeView_clicked(const QModelIndex &index) {
    /* set the current path of the absolute path of the selected folder */
    ui->pathBox->setText(dirFilemodel->filePath(index));
}

void OpenFileDialog::on_resetPathBtn_clicked() {
    /* set the default path as root path */
    dirFilemodel->setRootPath(Options::defaultPathOption);

    ui->treeView->setRootIndex(dirFilemodel->index(Options::defaultPathOption));
    ui->pathBox->setText(Options::defaultPathOption);
}

void OpenFileDialog::on_browseBtn_clicked() {
    if(FileHelper::IsPathExist(ui->pathBox->text().toStdString())) {
        dirFilemodel->setRootPath(ui->pathBox->text());
        ui->treeView->setRootIndex(dirFilemodel->index(ui->pathBox->text()));
    }
    else {
        MsgBoxHandler::warningMessage("Warning", "Please enter a correct path");
        ui->pathBox->setText(Options::defaultPathOption);
        ui->treeView->setRootIndex(dirFilemodel->index(Options::defaultPathOption));
        return;
    }
}

void OpenFileDialog::on_doOptionBtn_clicked() {
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

            dirFilemodel->mkdir(index, SaveAsDialog::dirName);
            ui->treeView->setModel(dirFilemodel);

            MsgBoxHandler::infoMessage("Info", "New folder created");
            break;

        /* Delete Folder/File */
        case 1:
            confirmBox.setText(tr("The application will proceed with removing the folder, are you sure that you want to continue?"));
            confirmBox.addButton(tr("Yes"), QMessageBox::YesRole);
            noBtn = confirmBox.addButton(tr("No"), QMessageBox::YesRole);

            /* show the message box */
            confirmBox.exec();
            if(confirmBox.clickedButton() == noBtn) { return; }

            dirFilemodel->remove(index);
            ui->treeView->setModel(dirFilemodel);
            break;

        default:
            return;
    }
}

/* open the file */
void OpenFileDialog::on_openBtn_clicked() {
    const QString &filePath = ui->pathBox->text();

    /* check if the file exist and if is effectively a file */
    if(!FileHelper::isFileExist(filePath)) {
        MsgBoxHandler::warningMessage("Warning", "Select a valid file");
        return;
    }

    FILE* f = fopen(filePath.toStdString().c_str(), "r");
    if(!f) {
        MsgBoxHandler::errorMessage("Error", "The application failed to load the file");
        return;
    }

    /* read the informations from the file and store it in the buffer */
    FileHelper::readInformations(f, MainDialog::messageBuffer);
    OpenFileDialog::filePath = filePath;
    OpenFileDialog::fileOpened = true;

    this->close(); return;
}
