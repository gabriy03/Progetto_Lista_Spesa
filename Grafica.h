//
// Created by gabriele on 17/01/26.
//

#ifndef GRAFICA_H
#define GRAFICA_H

#include "ListaSpesa.h"
#include "Prodotto.h"
#include <string>

class Grafica {
public:
    static bool ordinaProdotti(const Prodotto& a, const Prodotto& b);
    static std::string adattaTesto(std::string testo, int lunghezzaMax);
    static void stampaResoconto(const ListaSpesa& lista);
};

#endif // GRAFICA_H