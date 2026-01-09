//
// Created by gabriele on 09/01/26.
//

#include "gtest/gtest.h"
#include "ListaSpesa.h"
#include "Utente.h"
#include "Prodotto.h"

TEST(ObserverTest, NotificaFunzionante) {

    // Creo una lista
    ListaSpesa lista("Spesa Vacanze");

    // Creo due Utenti
    Utente* mario = new Utente("Mario", "1234");
    Utente* luigi = new Utente("Luigi", "5678");

    // Mario e Luigi condividono la lista
    lista.aggiungiObserver(mario);
    lista.aggiungiObserver(luigi);

    // Aggiungo un prodotto, quindi mi aspetto che partano le notifiche
    std::cout << "--- Inizio Test Aggiunta ---" << std::endl;
    Prodotto p("Birra", "Cassa da 6", "Bibite", 2, 3.50);
    lista.aggiungiProdotto(p);
    std::cout << "--- Fine Test Aggiunta ---" << std::endl;

    // Verifico che ci sia il prodotto
    ASSERT_EQ(lista.getProdotti().size(), 1);

    // Luigi si scollega dalla lista
    lista.rimuoviObserver(luigi);

    // Rimuovo il prodotto. Adesso solamente Mario dovrebbe ricevere la notifica
    std::cout << "--- Inizio Test Rimozione ---" << std::endl;
    lista.rimuoviProdotto(p);
    std::cout << "--- Fine Test Rimozione ---" << std::endl;

    // Alla fine pulisco la memoria
    delete mario;
    delete luigi;
}