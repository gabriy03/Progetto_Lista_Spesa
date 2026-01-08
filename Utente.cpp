//
// Created by gabriele on 08/01/26.
//

#include "Utente.h"


Utente::Utente(const std::string &nomeUtente, const std::string &pass)
    : nickname(nomeUtente), password(pass) {}


std::string Utente::getNickname() const {
    return nickname;
}

std::string Utente::getPassword() const {
    return password;
}


bool Utente::login(const std::string &inputNick, const std::string &inputPass) const {
    if (nickname == inputNick && password == inputPass) {
        return true;
    }
    return false;
}


void Utente::modificaPassword(const std::string &nuovaPass) {
    password = nuovaPass;
}