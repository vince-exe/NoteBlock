#ifndef MSGBOXHANDLER_H
#define MSGBOXHANDLER_H

#include <iostream>
#include <string>

class MsgBoxHandler {
public:
    MsgBoxHandler();

    /* create a WarningBox ( 550 300 ) with the given title and message */
    static void warningMessage(const std::string &title, const std::string &warningMessage);

    /* create an InfoBox ( 550 300 ) with the given title and message */
    static void infoMessage(const std::string &title, const std::string &infoMessage);

    /* ceate an ErrorBox ( 550 300 ) with the given title and message */
    static void errorMessage(const std::string &title, const std::string &errorMessage);
};

#endif // MSGBOXHANDLER_H
