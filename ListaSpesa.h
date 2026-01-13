//
// Created by gabriele on 09/01/26.
//

#ifndef PROGETTOLISTASPESA_LISTASPESA_H
#define PROGETTOLISTASPESA_LISTASPESA_H

#include "Subject.h"
#include "Prodotto.h"
#include <list>
#include <string>

// ListaSpesa è il Concrete Subject
class ListaSpesa : public Subject {

public:

    explicit ListaSpesa(const std::string& nome);

    virtual ~ListaSpesa() {}

    // --- METODI DEL PATTERN OBSERVER ---
    void aggiungiObserver(Observer* o) override;
    void rimuoviObserver(Observer* o) override;
    void notify() override;

    // --- METODI DELLA LISTA ---
    void aggiungiProdotto(const Prodotto& p);
    void rimuoviProdotto(const Prodotto& p);
    bool modificaProdotto(int indice, int nuovaQuantita, float nuovoPrezzo);

    // Utile poi per i Test e per la Stampa
    const std::list<Prodotto>& getProdotti() const;
    std::string getNomeListaSpesa() const;

private:
    std::string nomeLista;
    std::list<Prodotto> prodotti;
    std::list<Observer*> observers;
};

#endif //PROGETTOLISTASPESA_LISTASPESA_H