//
// Created by gabriele on 09/01/26.
//

#include "Prodotto.h"

Prodotto::Prodotto(const std::string &nome, const std::string &descrizione, const std::string &categoria, int quantita, float prezzo)
    : nome(nome), descrizione(descrizione), categoria(categoria), quantita(quantita), prezzo(prezzo) {}

std::string Prodotto::getNome() const {
    return nome;
}

std::string Prodotto::getDescrizione() const {
    return descrizione;
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
    // Due prodotti sono uguali se hanno stesso Nome, Descrizione e Categoria.
    if ((nome == altro.nome) && (descrizione == altro.descrizione) && (categoria == altro.categoria)) {
        return true;
    }
    return false;
}