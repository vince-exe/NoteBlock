#ifndef UTILITIES_H
#define UTILITIES_H

#include <QMessageBox>

#include <sys/stat.h>
#include <iostream>
#include <string>

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

/* take as paramater the full path of the file, and return only the path of the directory */
std::string getDirName(std::string fullPath);

/* take as paramater the full path of the file, and return only the name of the file */
std::string getFileName(std::string fullPath);

/* take as paramater a full file name + .txt and return only the name of it */

#endif // UTILITIES_H
