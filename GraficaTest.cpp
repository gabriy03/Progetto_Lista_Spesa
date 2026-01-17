//
// Created by gabriele on 17/01/26.
//

#include "gtest/gtest.h"
#include "Grafica.h"
#include "Prodotto.h"


TEST(GraficaTest, AdattaTesto) {
    // Caso 1: Testo corto (non deve cambiare)
    std::string corto = "ciao";
    std::string risultato1 = Grafica::adattaTesto(corto,10);
    EXPECT_EQ(risultato1.length(), 4);
    EXPECT_EQ(risultato1, "ciao");

    // Caso 2: Testo lungo (deve essere tagliato con i puntini)
    std::string lungo = "marmellata di fragole";
    std::string risultato2 = Grafica::adattaTesto(lungo, 10);
    // 10 caratteri totali: 7 lettere + 3 puntini
    EXPECT_EQ(risultato2.length(), 10);
    EXPECT_EQ(risultato2, "marmell...");
}

TEST(GraficaTest, LogicaOrdinamento) {
    Prodotto p1("acqua", "s.anna", "alimentari", 1, 1.00);
    Prodotto p2("frollini", "mulino bianco", "alimentari", 1, 2.00);
    Prodotto p3("ammorbidente", "coccolino", "casa", 1, 3.50);

    // TEST 1: Categorie diverse
    // Alimentari deve venire prima di Casa
    EXPECT_TRUE(Grafica::ordinaProdotti(p1, p3));

    // Casa non deve venire prima di Alimentari
    EXPECT_FALSE(Grafica::ordinaProdotti(p3, p1));

    // TEST 2: Stessa Categoria, Nomi diversi
    // Acqua deve venire prima di frollini
    EXPECT_TRUE(Grafica::ordinaProdotti(p1, p2));
}