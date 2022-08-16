#include "options_dialog_utilities.h"

bool IsPathExist(const std::string &s) {
  struct stat buffer;

  return (stat (s.c_str(), &buffer) == 0);
}

void warningMessage(const std::string &title, const std::string &warningMessage) {
    QMessageBox warningBox;

    warningBox.warning(0, QString::fromStdString(title), QString::fromStdString(warningMessage));
    warningBox.setFixedSize(550, 300);
}
