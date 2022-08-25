#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <iostream>
#include <string>

#include <QString>

class FileHelper {

public:
    FileHelper();

    /* take as paramater the full path of the file, and return only the path of the directory */
    static std::string getDirName(std::string fullPath);

    /* take as paramater the full path of the file, and return only the name of the file */
    static std::string getFileName(std::string fullPath);

    /* return true if the given path exist */
    static bool IsPathExist(const std::string &s);

    /* return true if the file exist */
    static bool isFileExist(const QString &s);

    /* store the content of the buffer in the file ( character by character ) */
    static void storeInformations(FILE* f, std::string& buffer);

    /* read the content from the opened file, and store it in the given buffer */
    static void readInformations(FILE* f, std::string &s_buffer);
};

#endif // FILEHELPER_H
