//
// Created by gabriele on 09/01/26.
//

#ifndef PROGETTOLISTASPESA_PRODOTTO_H
#define PROGETTOLISTASPESA_PRODOTTO_H

#include <string>

class Prodotto {

public:

    Prodotto(std::string nome, std::string marca, std::string categoria, int quantita, float prezzo);

    std::string getNome() const;
    std::string getMarca() const;
    std::string getCategoria() const;
    int getQuantita() const;
    float getPrezzo() const;


    void setQuantita(int nuovaQuantita);
    void setPrezzo(float nuovoPrezzo);


    // Calcola il totale (quantità * prezzo)
    float getCostoTotale() const;

    // Insegno all'operatore (==) a confrontare il NOME + MARCA di due prodotti
    // Mi servirà per non aggiungere due volte lo stesso prodotto a una lista
    bool operator==(const Prodotto& altro) const;

private:
    std::string nome;
    std::string marca;
    std::string categoria;
    int quantita;
    float prezzo;
};


#endif //PROGETTOLISTASPESA_PRODOTTO_H