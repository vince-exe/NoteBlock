#include "utilities.h"

#include <QFileInfo>

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

    errorBox.critical(0, QString::fromStdString(title), QString::fromStdString(errorMessage));
    errorBox.setFixedSize(550, 300);
}

bool isFileExist(const QString &s) {
    QFileInfo checkFile(s);

    return checkFile.exists() && checkFile.isFile();
}

void readOpenInformations(FILE *f, std::string &s_buffer) {
    char buffer[1024];
    s_buffer.clear();

    while(fgets(buffer, 1024, f)) {
        s_buffer.append(buffer);
    }
}

std::string getDirName(std::string fullPath) {
    int i = fullPath.length() - 1;
    while(fullPath[i--] != '/');

    return fullPath.substr(0, i + 1);
}

std::string getFileName(std::string fullPath) {
    int i = fullPath.length() - 1;
    while(fullPath[i--] != '/');

    return fullPath.substr(i + 2, fullPath.length() - 1);
}
