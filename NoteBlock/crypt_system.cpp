#include "crypt_system.h"

#include <random>

int CryptSystem::privateKey;

bool CryptSystem::criptedStatus;

CryptSystem::CryptSystem() {};

std::string CryptSystem::crypt(std::string message, int key) {
    std::string msg;
    for(int i = 0; i < int(message.length()); i++) {
        msg += message[i] + key;
    }

    return msg;
}

std::string CryptSystem::decrypt(std::string message, int key) {
    std::string msg;
    for(int i = 0; i < int(message.length()); i++) {
        msg += message[i] - key;
    }

    return msg;
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
