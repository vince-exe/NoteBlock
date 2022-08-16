#ifndef OPTIONS_DIALOG_UTILITIES_H
#define OPTIONS_DIALOG_UTILITIES_H

#include <QMessageBox>

#include <sys/stat.h>
#include <iostream>
#include <string>

/* return true if the given path exist */
bool IsPathExist(const std::string &s);

/* create a WarningBox ( 550 300 ) with the given title and message */
void warningMessage(const std::string &title, const std::string &warningMessage);

#endif // OPTIONS_DIALOG_UTILITIES_H
