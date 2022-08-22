#ifndef OPTIONS_DIALOG_UTILITIES_H
#define OPTIONS_DIALOG_UTILITIES_H

#include <QMessageBox>

#include <sys/stat.h>
#include <iostream>
#include <string>

/* used to store the content in the message box */
extern std::string messageBuffer;

/* used to check if the user has successfully created the file */
extern bool fileCreated;

/* used to check if the users wants to change the text color or background color */
extern bool changeTextColor;

/* return true if the given path exist */
bool IsPathExist(const std::string &s);

/* return true if the file exist */
bool isFileExist(const QString &s);

/* create a WarningBox ( 550 300 ) with the given title and message */
void warningMessage(const std::string &title, const std::string &warningMessage);

/* create an InfoBox ( 550 300 ) with the given title and message */
void infoMessage(const std::string &title, const std::string &infoMessage);

/* ceate an ErrorBox ( 550 300 ) with the given title and message */
void errorBox(const std::string &title, const std::string &errorMessage);

/* store the informations in the file */
void storeInformations(FILE* f, std::string& buffer);

/* read the informations from the opened file */
void readOpenInformations(FILE* f, std::string &s_buffer);

#endif // OPTIONS_DIALOG_UTILITIES_H
