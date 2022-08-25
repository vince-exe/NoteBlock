#ifndef CRYPTSYSTEM_H
#define CRYPTSYSTEM_H

#include <iostream>
#include <string>

class CryptSystem {
private:
    static int privateKey;

    const static int minimum = 100;

    const static int maxnimum = 1000;

public:
    CryptSystem();

    static bool criptedStatus;

    static bool decryptStatus;

    /* function to crypt a message using the Giulio Cesare cripation system */
    static std::string crypt(std::string message, int key);

    /* function to decrypt a message */
    static std::string decrypt(std::string message, int key);

    /* function to generate a random key */
    static void generateKey();

    static int getKey();
};

#endif // CRYPTSYSTEM_H
