//
// Created by gabriele on 09/01/26.
//

#include "ListaSpesa.h"
#include <iterator>

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


bool ListaSpesa::aggiungiProdotto(const Prodotto& p) {
    for (const auto& esistente : prodotti) {
        if (esistente == p) {
            return false;
        }
    }

    // Se arriva qui, non ha trovato duplicati. Aggiunge.
    prodotti.push_back(p);
    notify();
    return true;
}

bool ListaSpesa::rimuoviProdotto(int indice) {
    if (indice < 0 or indice >= prodotti.size()) {
        return false;
    }
    // Punto all'inizio della lista
    auto it = prodotti.begin();

    // Avanzo fino all'elemento che voglio cancellare
    std::advance(it, indice);

    prodotti.erase(it);
    notify();
    return true;
}

bool ListaSpesa::modificaProdotto(int indice, int nuovaQuantita, float nuovoPrezzo) {
    if (indice < 0 or indice >= prodotti.size()) {
        return false;
    }
    int contatore = 0;
    for (auto& p : prodotti) {
        if (contatore == indice) {
            p.setQuantita(nuovaQuantita);
            p.setPrezzo(nuovoPrezzo);
            notify();
            return true;
        }
        contatore++;
    }
    return false;
}

const std::list<Prodotto>& ListaSpesa::getProdotti() const {
    return prodotti;
}

std::string ListaSpesa::getNomeListaSpesa() const {
    return nomeLista;
}