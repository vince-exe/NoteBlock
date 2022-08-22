#include "main_dialog.h"
#include "ui_main_dialog.h"

#include <QShortcut>
#include <QPushButton>
#include <QStyle>

#include <windows.h>
#include <lmcons.h>

#include "options.h"

/* forms */
#include "options_menu_dialog.h"

#include "options_dialog_utilities.h"
#include "open_file_dialog.h"

const QString noteBookStyleSheet = "font: 600 18pt Segoe UI Variable Text Semibold;background-color: rgb(39, 39, 39);color: rgb(218, 218, 218);border: 0px solid rgb(39, 39, 39);padding-top: 16px;padding-left: 20px;padding-right: 20px;padding-bottom: 45px;";

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog) {
    ui->setupUi(this);

    ui->widthLabel->setText("Width: " + QString::number(this->size().width()));
    ui->heightLabel->setText("Height: " + QString::number(this->size().height()));

    /* get the host name */
    TCHAR username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;

    GetUserName((TCHAR*)username, &username_len);

    QString hostName = QString::fromWCharArray(username);
    Options::defaultPathOption = "C:/Users/" + hostName;

    /* open the option file */
    FILE* f = fopen(Options::sysCurrentOptionsPath, "r");

    if(!f) {
        errorBox("Error", "The application failed to load the system files");
        exit(-1);
    }

    Options::readOptions(f);
    fclose(f);

    QFont newFont = QFont(Options::defaultFontStyle);
    ui->textBox->setStyleSheet(noteBookStyleSheet + "font-family: " + newFont.family() + "; font-style: normal" + "; font-size: " + QString::number(Options::defaultFontSize) + "pt;" + "color: " + Options::defaultTextColor + ";background-color: " + Options::defaultBackColor);
}

MainDialog::~MainDialog() {
    delete ui;
}

void MainDialog::resizeEvent(QResizeEvent *event) {
    ui->textBox->setGeometry(0, 0, event->size().width(), event->size().height());
    ui->infoLabel->setGeometry(0, event->size().height() - 50, event->size().width(), 50);

    ui->heightLabel->setGeometry(event->size().width() - 151, ui->infoLabel->geometry().y() + 10, 111, 31);
    ui->widthLabel->setGeometry(ui->heightLabel->geometry().x() - 170, ui->infoLabel->geometry().y() + 10, 111, 31);
    ui->openSaveBtn->setGeometry(ui->widthLabel->geometry().x() - 170, ui->infoLabel->geometry().y() + 10, 111, 31);

    ui->widthLabel->setText("Width: " + QString::number(event->size().width()));
    ui->heightLabel->setText("Height: " + QString::number(event->size().height()));
}

/* open the options dialog */
void MainDialog::on_openSaveBtn_clicked() {
    /* store the content of the message box in the buffer */
    messageBuffer = ui->textBox->toPlainText().toStdString();

    OptionsMenuDialog optionDialog;
    optionDialog.setModal(true);
    optionDialog.show();
    optionDialog.exec();

    if(fileCreated) {
        ui->textBox->clear();
        fileCreated = false;
    }
    QFont newFont = QFont(Options::defaultFontStyle);

    ui->textBox->setStyleSheet(noteBookStyleSheet + "font-family: " + newFont.family() + "; font-style: normal" + "; font-size: " + QString::number(Options::defaultFontSize) + "pt;" + "color: " + Options::defaultTextColor + ";background-color: " + Options::defaultBackColor);

    if(OpenFileDialog::fileOpened) {
        ui->textBox->setPlainText(QString::fromStdString(messageBuffer));

        QTextCursor cursor = ui->textBox->textCursor();
        cursor.atEnd();
        ui->textBox->setTextCursor(cursor);
    }
}
