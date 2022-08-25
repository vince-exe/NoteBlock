#include "crypt_system.h"

#include <random>
#include <QString>
#include <QDebug>

int CryptSystem::privateKey;

bool CryptSystem::criptedStatus;

bool CryptSystem::decryptStatus;

CryptSystem::CryptSystem() {};

void CryptSystem::crypt(std::string message, int key, FILE* f) {
    for(int i = 0; i < int(message.length()); i++) {
        putc(message[i] + key, f);
    }
}

std::string CryptSystem::decrypt(int key, FILE* f) {
    std::string decMsg;
    char buffer[1024];

    while(fgets(buffer, 1024, f)) {
        for(int i = 0; i < strlen(buffer); i++) {
            decMsg.push_back(buffer[i] - key);
        }
    }

    return decMsg;
}

void CryptSystem::generateKey() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(CryptSystem::minimum, CryptSystem::maxnimum);

    CryptSystem::privateKey = dist6(rng);
}

int CryptSystem::getKey() {
    return CryptSystem::privateKey;
}
