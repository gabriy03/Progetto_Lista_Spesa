//
// Created by gabriele on 09/01/26.
//

#include "ListaSpesa.h"
#include <iterator>
#include <fstream> // Serve per leggere/scrivere File
#include <sstream> // Serve per leggere le righe

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

bool ListaSpesa::salvaSuFile(const std::string &nomeFile) const {
    // Apro il file per scriverci dentro
    std::ofstream file(nomeFile);

    // Controllo se il file si è aperto
    if (!file.is_open()) {
        return false;
    }

    // Scorro la lista e scrivo ogni prodotto su una riga separati da ";"
    for (const auto& p : prodotti) {
        file << p.getNome() << ";"
             << p.getMarca() << ";"
             << p.getCategoria() << ";"
             << p.getQuantita() << ";"
             << p.getPrezzo() << "\n";
    }

    // Chiudo il file
    file.close();
    return true;
}

bool ListaSpesa::caricaDaFile(const std::string& nomeFile) {
    // Prendo il file da caricare
    std::ifstream file(nomeFile);

    // Controllo se il file si apre
    if (!file.is_open()) {
        return false;
    }

    //Svuoto la lista attuale
    prodotti.clear();

    std::string riga;

    // Leggo il file riga per riga
    while (std::getline(file, riga)) {

        if (riga.empty())   // Mi serve per saltare eventuali righe vuote
            continue;

        std::stringstream ss(riga);
        std::string nome, marca, categoria, strQuantita, strPrezzo;

        // Divido la riga usando il punto e virgola ';' come divisorio
        std::getline(ss, nome, ';');
        std::getline(ss, marca, ';');
        std::getline(ss, categoria, ';');
        std::getline(ss, strQuantita, ';');
        std::getline(ss, strPrezzo, ';');

        // Controllo se abbiamo tutti gli attributi
        if (!nome.empty() && !marca.empty() && !categoria.empty() && !strQuantita.empty() && !strPrezzo.empty()) {

            // Mi proteggo da un'eventuale conversione sbagliata
            try {
                int q = std::stoi(strQuantita);
                float p = std::stof(strPrezzo);
                Prodotto nuovo(nome, marca, categoria, q, p);
                prodotti.push_back(nuovo);

            } catch (...) {
                // Se c'è stato un errore di conversione, il file è corrotto.
                prodotti.clear();
                file.close();
                return false;
            }
        }
    }
    // Se arrivo qui, tutto è andato bene
    file.close();
    notify();
    return true;
}

const std::list<Prodotto>& ListaSpesa::getProdotti() const {
    return prodotti;
}

std::string ListaSpesa::getNomeListaSpesa() const {
    return nomeLista;
}