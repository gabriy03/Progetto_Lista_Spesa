//
// Created by gabriele on 09/01/26.
//

#include "Prodotto.h"
#include <cctype>

Prodotto::Prodotto(std::string nome, std::string marca, std::string categoria, int quantita, float prezzo)
    : nome(nome), marca(marca), categoria(categoria), quantita(quantita), prezzo(prezzo) {


    // Converto nome in MAIUSCOLO
    // Ho messo la & per modificare direttamente i caratteri della stringa
    for (char &c : this->nome) {
        c = std::toupper(c);
    }

    // Converto marca in MAIUSCOLO
    for (char &c : this->marca) {
        c = std::toupper(c);
    }

    // Converto marca in MAIUSCOLO
    for (char &c : this->categoria) {
        c = std::toupper(c);
    }
}

std::string Prodotto::getNome() const {
    return nome;
}

std::string Prodotto::getMarca() const {
    return marca;
}

std::string Prodotto::getCategoria() const {
    return categoria;
}

int Prodotto::getQuantita() const {
    return quantita;
}

float Prodotto::getPrezzo() const {
    return prezzo;
}

void Prodotto::setQuantita(int nuovaQuantita) {
    quantita = nuovaQuantita;
}

void Prodotto::setPrezzo(float nuovoPrezzo) {
    prezzo = nuovoPrezzo;
}

float Prodotto::getCostoTotale() const {
    return quantita * prezzo;
}

bool Prodotto::operator==(const Prodotto &altro) const {
    // Due prodotti sono uguali se hanno stesso Nome e Marca
    if ((this->nome == altro.nome) && (this->marca == altro.marca)) {
        return true;
    }
    return false;
}