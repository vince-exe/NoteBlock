#include "file_helper.h"

#include <QFileInfo>
#include <QDir>

#include <sys/stat.h>

FileHelper::FileHelper() {}

std::string FileHelper::getDirName(std::string fullPath) {
    int i = fullPath.length() - 1;
    while(fullPath[i--] != '/');

    return fullPath.substr(0, i + 1);
}

std::string FileHelper::getFileName(std::string fullPath) {
    int i = fullPath.length() - 1;
    while(fullPath[i--] != '/');

    return fullPath.substr(i + 2, fullPath.length() - 1);
}

bool FileHelper::IsPathExist(const std::string &s) {
    struct stat buffer;

    return (stat (s.c_str(), &buffer) == 0);
}

bool FileHelper::isFileExist(const QString &s) {
    QFileInfo checkFile(s);

    return checkFile.exists() && checkFile.isFile();
}

void FileHelper::storeInformations(FILE *f, std::string &buffer) {
    for(int i = 0; i < int(buffer.length()); i++) {
        putc(buffer[i], f);
    }
}

void FileHelper::readInformations(FILE *f, std::string &s_buffer) {
    char buffer[1024];
    s_buffer.clear();

    while(fgets(buffer, 1024, f)) {
        s_buffer.append(buffer);
    }
};
