#include "utilities.h"

void warningMessage(const std::string &title, const std::string &warningMessage) {
    QMessageBox warningBox;

    warningBox.warning(0, QString::fromStdString(title), QString::fromStdString(warningMessage));
    warningBox.setFixedSize(550, 300);
}

void infoMessage(const std::string &title, const std::string &infoMessage) {
    QMessageBox infoBox;

    infoBox.information(0, QString::fromStdString(title), QString::fromStdString(infoMessage));
    infoBox.setFixedSize(550, 300);
}

void errorBox(const std::string &title, const std::string &errorMessage) {
    QMessageBox errorBox;

    errorBox.critical(0, QString::fromStdString(title), QString::fromStdString(errorMessage));
    errorBox.setFixedSize(550, 300);
}
