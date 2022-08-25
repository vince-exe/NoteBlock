#ifndef UTILITIES_H
#define UTILITIES_H

#include <QMessageBox>
#include <iostream>
#include <string>

/* create a WarningBox ( 550 300 ) with the given title and message */
void warningMessage(const std::string &title, const std::string &warningMessage);

/* create an InfoBox ( 550 300 ) with the given title and message */
void infoMessage(const std::string &title, const std::string &infoMessage);

/* ceate an ErrorBox ( 550 300 ) with the given title and message */
void errorBox(const std::string &title, const std::string &errorMessage);

#endif // UTILITIES_H
