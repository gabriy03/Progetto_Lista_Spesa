//
// Created by gabriele on 09/01/26.
//

#include "gtest/gtest.h"
#include "ListaSpesa.h"

TEST(ListaSpesaTest, GestioneProdotti) {
    ListaSpesa lista("Spesa Casa");

    // Verifico se il nome corrisponde
    EXPECT_EQ(lista.getNomeListaSpesa(), "Spesa Casa");

    // Creo due prodotti e li aggiungo alla lista
    Prodotto p1("latte", "mukki", "alimentari", 1, 1.50);
    Prodotto p2("pane integrale", "coop", "alimentari", 2, 1.00);
    lista.aggiungiProdotto(p1);
    lista.aggiungiProdotto(p2);

    // Verifico che ci siano 2 prodotti
    ASSERT_EQ(lista.getProdotti().size(), 2);

    // Verifico che i prodotti siano salvati in MAIUSCOLO
    EXPECT_EQ(lista.getProdotti().front().getNome(), "LATTE");
    EXPECT_EQ(lista.getProdotti().front().getMarca(), "MUKKI");
    EXPECT_EQ(lista.getProdotti().back().getNome(), "PANE INTEGRALE");
    EXPECT_EQ(lista.getProdotti().back().getMarca(), "COOP");


    // Verifico che il primo sia il Latte
    EXPECT_EQ(lista.getProdotti().front().getNome(), "LATTE");

    // Rimuovo il Pane
    lista.rimuoviProdotto(1);

    // Verifico se ne rimane solo 1 (il Latte)
    ASSERT_EQ(lista.getProdotti().size(), 1);
    EXPECT_EQ(lista.getProdotti().front().getNome(), "LATTE");

    // Verifico se funziona la modifica
    // Modifico il Latte (Indice 0): Quantità 1->5, Prezzo 1.50->0.80
    bool risultato = lista.modificaProdotto(0, 5, 0.80);

    ASSERT_TRUE(risultato);

    // Controllo se i dati sono cambiati
    const auto& p = lista.getProdotti();
    const Prodotto& primoProdotto = p.front();

    EXPECT_EQ(primoProdotto.getQuantita(), 5);
    EXPECT_FLOAT_EQ(primoProdotto.getPrezzo(), 0.80);
    // Verifico che il totale sia aggiornato (5 * 0.80 = 4.0)
    EXPECT_FLOAT_EQ(primoProdotto.getCostoTotale(), 4.0);

    // TEST FALLIMENTO: Provo a modificare indice 99 (non esiste)
    bool risultatoFallito = lista.modificaProdotto(99, 1, 1.0);
    EXPECT_FALSE(risultatoFallito);
}

TEST(ListaSpesaTest, NoDuplicati) {
    ListaSpesa lista("Picnic");
    // Creiamo un prodotto
    Prodotto p1("acqua", "sant'anna", "Bibite", 6, 0.50);

    // Primo inserimento va bene
    ASSERT_TRUE(lista.aggiungiProdotto(p1));

    // Secondo inserimento (stesso oggetto) deve fallire
    ASSERT_FALSE(lista.aggiungiProdotto(p1));
}