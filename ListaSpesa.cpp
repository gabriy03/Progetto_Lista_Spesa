//
// Created by gabriele on 09/01/26.
//

#include "ListaSpesa.h"

ListaSpesa::ListaSpesa(const std::string& nome) : nomeLista(nome) {}


void ListaSpesa::aggiungiObserver(Observer* o) {
    observers.push_back(o);
}

void ListaSpesa::rimuoviObserver(Observer* o) {
    observers.remove(o);
}

void ListaSpesa::notify() {
    // Ciclo su tutti gli Observer e dico loro di aggiornarsi
    for (auto* observer : observers) {
        observer->update();
    }
}


void ListaSpesa::aggiungiProdotto(const Prodotto& p) {
    prodotti.push_back(p);
    // Notifico il cambiamento della lista agli altri utenti che condividono la lista
    notify();
}

void ListaSpesa::rimuoviProdotto(const Prodotto& p) {
    prodotti.remove(p);
    // Notifico il cambiamento della lista agli altri utenti che condividono la lista
    notify();
}

const std::list<Prodotto>& ListaSpesa::getProdotti() const {
    return prodotti;
}

std::string ListaSpesa::getNomeListaSpesa() const {
    return nomeLista;
}