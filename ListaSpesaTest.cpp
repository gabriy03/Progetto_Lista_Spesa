//
// Created by gabriele on 09/01/26.
//

#include "gtest/gtest.h"
#include "ListaSpesa.h"
#include <fstream>

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

TEST(ListaSpesaTest, SalvaECaricaDaFile) {
    std::string fileGiusto = "test_spesa.txt";
    std::string fileRotto = "test_spesa_rotto.txt";

    // --- CASO DI SUCCESSO ---
    ListaSpesa lista1("Lista Originale");
    lista1.aggiungiProdotto(Prodotto("Latte", "Mukki", "Alimentari", 2, 1.50));
    lista1.aggiungiProdotto(Prodotto("Pane", "Coop", "Alimentari", 1, 1.00));

    // Controllo che il Salvataggio sul file sia andato a buon fine
    ASSERT_TRUE(lista1.salvaSuFile(fileGiusto));

    ListaSpesa lista2("Lista Nuova");

    // Controllo che il caricamento del file sia andato a buon fine
    ASSERT_TRUE(lista2.caricaDaFile(fileGiusto));

    // Verifico i dati caricati
    ASSERT_EQ(lista2.getProdotti().size(), 2);
    // Primo Prodotto
    EXPECT_EQ(lista2.getProdotti().front().getNome(), "LATTE");
    EXPECT_EQ(lista2.getProdotti().front().getMarca(), "MUKKI");
    EXPECT_EQ(lista2.getProdotti().front().getCategoria(), "ALIMENTARI");
    EXPECT_EQ(lista2.getProdotti().front().getQuantita(), 2);
    EXPECT_EQ(lista2.getProdotti().front().getPrezzo(), 1.50);
    // Secondo Prodotto
    EXPECT_EQ(lista2.getProdotti().back().getNome(), "PANE");
    EXPECT_EQ(lista2.getProdotti().back().getMarca(), "COOP");
    EXPECT_EQ(lista2.getProdotti().back().getCategoria(), "ALIMENTARI");
    EXPECT_EQ(lista2.getProdotti().back().getQuantita(), 1);
    EXPECT_EQ(lista2.getProdotti().back().getPrezzo(), 1.00);


    // --- CASO DI FALLIMENTO (FILE CORROTTO) ---
    // Modifico il File in modo diretto
    std::ofstream Sbagliato(fileRotto);
    Sbagliato << "VINO;TAVERNELLO;ALCOLICI;due;3.5";
    Sbagliato.close();

    ListaSpesa lista3("Lista Sbagliata");

    // Mi aspetto un errore nel caricamento
    bool esito = lista3.caricaDaFile(fileRotto);
    ASSERT_FALSE(esito);

    // La lista deve essere vuota (perchè abbiamo pulito tutto nel catch)
    ASSERT_TRUE(lista3.getProdotti().empty());
}