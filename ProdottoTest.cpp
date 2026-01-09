//
// Created by gabriele on 09/01/26.
//

#include "gtest/gtest.h"
#include "Prodotto.h"

TEST(ProdottoTest, CostruttoreEGetter) {

    Prodotto p("Latte", "Intero", "Alimentari", 2, 1.50);

    EXPECT_EQ(p.getNome(), "Latte");
    EXPECT_EQ(p.getDescrizione(), "Intero");
    EXPECT_EQ(p.getCategoria(), "Alimentari");
    EXPECT_EQ(p.getQuantita(), 2);
    EXPECT_FLOAT_EQ(p.getPrezzo(), 1.50);
}

TEST(ProdottoTest, CalcoloCostoTotale) {
    Prodotto p("Pasta", "Spaghetti n.5", "Alimentari", 3, 2.00);
    EXPECT_FLOAT_EQ(p.getCostoTotale(), 6.00);
}

TEST(ProdottoTest, OperatoreUguaglianza) {
    Prodotto p1("Pasta", "Spaghetti n.1", "Alimentari", 1, 1.00);
    Prodotto p2("Pasta", "Spaghetti n.1", "Alimentari", 5, 1.00);
    Prodotto p3("Pasta", "Penne", "Alimentari", 1, 1.00);

    // p1 e p2 sono lo stesso prodotto
    EXPECT_TRUE(p1 == p2);

    // p1 e p3 sono prodotti diversi
    EXPECT_FALSE(p1 == p3);

    // p2 e p3 sono prodotti diversi
    EXPECT_FALSE(p2 == p3);
}