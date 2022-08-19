#include "options_dialog_utilities.h"

/* used to store the content in the message box */
std::string messageBuffer;

bool fileCreated = false;

bool changeTextColor = false;

bool IsPathExist(const std::string &s) {
  struct stat buffer;

  return (stat (s.c_str(), &buffer) == 0);
}

void warningMessage(const std::string &title, const std::string &warningMessage) {
    QMessageBox warningBox;

    warningBox.warning(0, QString::fromStdString(title), QString::fromStdString(warningMessage));
    warningBox.setFixedSize(550, 300);
}

void storeInformations(FILE *f, std::string &buffer) {
    for(int i = 0; i < int(buffer.length()); i++) {
        putc(buffer[i], f);
    }
}

void infoMessage(const std::string &title, const std::string &infoMessage) {
    QMessageBox infoBox;

    infoBox.information(0, QString::fromStdString(title), QString::fromStdString(infoMessage));
    infoBox.setFixedSize(550, 300);
}

void errorBox(const std::string &title, const std::string &errorMessage) {
    QMessageBox errorBox;

    errorBox.information(0, QString::fromStdString(title), QString::fromStdString(errorMessage));
    errorBox.setFixedSize(550, 300);
}
