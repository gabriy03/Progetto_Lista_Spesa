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
    std::cout << "\n--- Inizio Test Aggiunta Prodotto ---" << std::endl;
    Prodotto p("Birra", "Cassa da 6", "Bibite", 2, 3.50);
    lista.aggiungiProdotto(p);
    std::cout << "--- Fine Test Aggiunta ---" << std::endl;

    // Verifico che ci sia il prodotto
    ASSERT_EQ(lista.getProdotti().size(), 1);

    //Modifico un prodotto. Mario e Luigi dovrebbero ricevere la notifica
    std::cout << "\n--- Inizio Test Modifica Prodotto ---" << std::endl;
    lista.modificaProdotto(0,3,3.00);
    std::cout << "--- Fine Test Modifica Prodotto ---" << std::endl;

    // Luigi si scollega dalla lista
    lista.rimuoviObserver(luigi);

    // Rimuovo il prodotto. Adesso solamente Mario dovrebbe ricevere la notifica
    std::cout << "\n--- Inizio Test Rimozione ---" << std::endl;
    lista.rimuoviProdotto(0);
    std::cout << "--- Fine Test Rimozione ---\n" << std::endl;

    // Verifico che il prodotto non ci sia più
    ASSERT_EQ(lista.getProdotti().size(), 0);

    // Alla fine pulisco la memoria
    delete mario;
    delete luigi;
}