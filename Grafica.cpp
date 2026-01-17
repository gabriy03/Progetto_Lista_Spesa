//
// Created by gabriele on 17/01/26.
//

#include "Grafica.h"
#include <iostream>
#include <iomanip>
#include <list>

bool Grafica::ordinaProdotti(const Prodotto& a, const Prodotto& b) {
    if (a.getCategoria() != b.getCategoria()) {
        if (a.getCategoria() < b.getCategoria())
            return true;
        else
            return false;
    }
    if (a.getNome() < b.getNome())
        return true;
    else
        return false;
}

std::string Grafica::adattaTesto(std::string testo, int lunghezzaMax) {
    if (testo.length() > lunghezzaMax) {
        return testo.substr(0, lunghezzaMax - 3) + "...";
    }
    return testo;
}

void Grafica::stampaResoconto(const ListaSpesa& lista) {
    std::list<Prodotto> prodottiOrdinati = lista.getProdotti();
    prodottiOrdinati.sort(ordinaProdotti);

    // Mi serve per pulire lo schermo
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    std::cout << "\n====================================================================================================\n";
    std::cout << "                                  RESOCONTO: " << lista.getNomeListaSpesa() << "\n";
    std::cout << "====================================================================================================\n";

    std::cout << std::left
              << std::setw(35) << "PRODOTTO"
              << std::setw(20) << "MARCA"
              << std::setw(20) << "CATEGORIA"
              << std::setw(10) << "QUANTITA'"
              << std::setw(15) << "PREZZO UNITARIO"
              << "\n";
    std::cout << "----------------------------------------------------------------------------------------------------\n";

    float totaleComplessivo = 0;

    for (const auto& p : prodottiOrdinati) {
        std::cout << std::left
                  << std::setw(35) << adattaTesto(p.getNome(), 32)
                  << std::setw(20) << adattaTesto(p.getMarca(), 17)
                  << std::setw(20) << adattaTesto(p.getCategoria(), 17)
                  << std::setw(10) << p.getQuantita()
                  << std::fixed << std::setprecision(2) << p.getPrezzo() << " €"
                  << "\n";

        totaleComplessivo += p.getCostoTotale();
    }

    std::cout << "----------------------------------------------------------------------------------------------------\n";
    std::cout << "                                                                     TOTALE: "
              << std::fixed << std::setprecision(2) << totaleComplessivo << " €\n";
    std::cout << "====================================================================================================\n\n";

    std::cout << "Premi INVIO per tornare al menu...";

    // Mi serve per pulire un eventuale INVIO rimasto salvato
    if (std::cin.peek() == '\n')
        std::cin.ignore();
    std::cin.get();
}