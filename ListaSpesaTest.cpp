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
    Prodotto p1("Latte", "Intero", "Alimentari", 1, 1.50);
    Prodotto p2("Pane", "Integrale", "Alimentari", 2, 3.00);
    lista.aggiungiProdotto(p1);
    lista.aggiungiProdotto(p2);

    // Verifico che ci siano 2 prodotti
    ASSERT_EQ(lista.getProdotti().size(), 2);

    // Verifico che il primo sia il Latte
    EXPECT_EQ(lista.getProdotti().front().getNome(), "Latte");

    // Rimuovo il Pane
    lista.rimuoviProdotto(p2);

    // Verifico se ne rimane solo 1 (il Latte)
    ASSERT_EQ(lista.getProdotti().size(), 1);
    EXPECT_EQ(lista.getProdotti().front().getNome(), "Latte");

    // Verifico se funziona la modifica
    // Modifico il Latte (Indice 0): Quantità 1->5, Prezzo 1.50->0.80
    bool risultato = lista.modificaProdotto(0, 5, 0.80);

    ASSERT_TRUE(risultato);

    // Controllo se i dati sono cambiati
    const auto& prodotti = lista.getProdotti();
    const Prodotto& primoProdotto = prodotti.front();

    EXPECT_EQ(primoProdotto.getQuantita(), 5);
    EXPECT_FLOAT_EQ(primoProdotto.getPrezzo(), 0.80);
    // Verifico che il totale sia aggiornato (5 * 0.80 = 4.0)
    EXPECT_FLOAT_EQ(primoProdotto.getCostoTotale(), 4.0);

    // TEST FALLIMENTO: Provo a modificare indice 99 (non esiste)
    bool risultatoFallito = lista.modificaProdotto(99, 1, 1.0);
    EXPECT_FALSE(risultatoFallito);
}