#ifndef OPTIONS_DIALOG_UTILITIES_H
#define OPTIONS_DIALOG_UTILITIES_H

#include <QMessageBox>

#include <sys/stat.h>
#include <iostream>
#include <string>

/* used to store the content in the message box */
extern std::string messageBuffer;

/* return true if the given path exist */
bool IsPathExist(const std::string &s);

/* create a WarningBox ( 550 300 ) with the given title and message */
void warningMessage(const std::string &title, const std::string &warningMessage);

/* create an InfoBox ( 550 300 ) with the given title and message */
void infoMessage(const std::string &title, const std::string &infoMessage);

/* store the informations in the file */
void storeInformations(FILE* f, std::string& buffer);

#endif // OPTIONS_DIALOG_UTILITIES_H
