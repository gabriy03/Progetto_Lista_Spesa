//
// Created by gabriele on 09/01/26.
//

#include "gtest/gtest.h"
#include "Prodotto.h"

TEST(ProdottoTest, CostruttoreEGetter) {

    Prodotto p("latte", "mukki", "alimentari", 2, 1.50);

    EXPECT_EQ(p.getNome(), "LATTE");
    EXPECT_EQ(p.getMarca(), "MUKKI");
    EXPECT_EQ(p.getCategoria(), "ALIMENTARI");
    EXPECT_EQ(p.getQuantita(), 2);
    EXPECT_FLOAT_EQ(p.getPrezzo(), 1.50);
}

TEST(ProdottoTest, ConversioneMaiuscolo) {

    Prodotto p("latte", "granarolo", "alimentari", 1, 1.50);

    // Mi aspetto che sia diventato tutto MAIUSCOLO
    EXPECT_EQ(p.getNome(), "LATTE");
    EXPECT_EQ(p.getMarca(), "GRANAROLO");
    EXPECT_EQ(p.getCategoria(), "ALIMENTARI");
}

TEST(ProdottoTest, CalcoloCostoTotale) {
    Prodotto p("spaghetti", "barilla", "alimentari", 3, 2.00);
    EXPECT_FLOAT_EQ(p.getCostoTotale(), 6.00);
}

TEST(ProdottoTest, OperatoreUguaglianza) {
    Prodotto p1("penne rigate", "barilla", "alimentari", 1, 3.00);
    Prodotto p2("penne rigate", "barilla", "alimentari", 5, 3.00);
    Prodotto p3("penne", "coop", "alimentari", 1, 1.50);

    // p1 e p2 sono lo stesso prodotto
    EXPECT_TRUE(p1 == p2);

    // p1 e p3 sono prodotti diversi
    EXPECT_FALSE(p1 == p3);

    // p2 e p3 sono prodotti diversi
    EXPECT_FALSE(p2 == p3);
}