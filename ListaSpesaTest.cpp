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

    // Rimuovo il Latte
    lista.rimuoviProdotto(p1);

    // Verifico se ne rimane solo 1 (il Pane)
    ASSERT_EQ(lista.getProdotti().size(), 1);
    EXPECT_EQ(lista.getProdotti().front().getNome(), "Pane");
}