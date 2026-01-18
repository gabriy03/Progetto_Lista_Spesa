//
// Created by gabriele on 08/01/26.
//

#include "Utente.h"
#include <iostream>
#include <fstream>
#include <sstream>


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

void Utente::modificaNickName(const std::string& nuovoNick) {
    nickname = nuovoNick;
}

void Utente::modificaPassword(const std::string &nuovaPass) {
    password = nuovaPass;
}

void Utente::update() {
    std::cout << "Ding! L'utente " << nickname << " ha notato un cambiamento nella lista!" << std::endl;
}

void Utente::aggiungiListaPermessa(const std::string& nomeFile) {
    listePermesse.push_back(nomeFile);
}

void Utente::rimuoviListaPermessa(const std::string& nomeFile) {
    listePermesse.remove(nomeFile);
}

const std::list<std::string>& Utente::getListePermesse() const {
    return listePermesse;
}

bool Utente::salvaUtenti(const std::string& nomeFile, const std::list<Utente*>& elencoUtenti) {
    // Apro il file per scriverci dentro
    std::ofstream file(nomeFile);

    if (!file.is_open()) {
        return false;
    }

    //  Salvo Nick; Pass; liste (a cui ha accesso l'utente) di ciascun utente su diverse righe
    for (const auto* u : elencoUtenti) {
        file << u->getNickname() << ";"
             << u->getPassword();

        for (const auto& nomeLista : u->getListePermesse()) {
            file << ";" << nomeLista;
        }

        // Vado a capo per il prossimo utente
        file << "\n";
    }

    file.close();
    return true;
}

bool Utente::caricaUtenti(const std::string& nomeFile, std::list<Utente*>& elencoUtenti) {
    // Prendo il file da caricare
    std::ifstream file(nomeFile);

    if (!file.is_open()) {
        return false;
    }

    std::string riga;

    // Leggo il file riga per riga
    while (std::getline(file, riga)) {

        if (riga.empty())   // Mi serve per saltare eventuali righe vuote
            continue;

        std::stringstream ss(riga);
        std::string nick, pass, nomeFileLista;

        // Divido la riga usando il punto e virgola ';' come divisorio
        // I primi due pezzi sono sempre Nick e Password
        std::getline(ss, nick, ';');
        std::getline(ss, pass, ';');

        // Controllo se nome e password validi
        if (!nick.empty() && !pass.empty()) {

            // Creo il nuovo utente
            auto* nuovoUtente = new Utente(nick, pass);

            // Continuo a leggere finché ci sono file associati sulla riga
            while (std::getline(ss, nomeFileLista, ';')) {
                if (!nomeFileLista.empty()) {
                    nuovoUtente->aggiungiListaPermessa(nomeFileLista);
                }
            }

            // Aggiungo l'utente completo alla lista generale
            elencoUtenti.push_back(nuovoUtente);
        }
    }

    file.close();
    return true;
}