//
// Created by gabriele on 08/01/26.
//

#include "gtest/gtest.h"
#include "Utente.h"
#include <cstdio>

// Testo che il costruttore salvi correttamente i dati
TEST(UtenteTest, CostruttoreEGetter) {
    Utente u("MarioRossi", "password123");
    EXPECT_EQ(u.getNickname(), "MarioRossi");
    EXPECT_EQ(u.getPassword(), "password123");
}

// Testo che il login funzioni solo con le credenziali giuste
TEST(UtenteTest, FunzionamentoLogin) {
    Utente u("MarioRossi", "password123");

    // Caso Positivo
    EXPECT_TRUE(u.login("MarioRossi", "password123"));

    // Caso Negativo (Password errata)
    EXPECT_FALSE(u.login("MarioRossi", "sbagliata"));

    // Caso Negativo (Nickname errato)
    EXPECT_FALSE(u.login("LuigiVerdi", "password123"));
}

// Testo il cambio Nickname
TEST(UtenteTest, ModificaNickName) {
    Utente u("MarioRossi", "password123");

    // Controllo che il Nickname inserito sia giusto
    ASSERT_EQ(u.getNickname(), "MarioRossi");

    //Modifico il NickName
    u.modificaNickName("nuovoNick");

    // Il vecchio Nickname non deve più funzionare
    EXPECT_FALSE(u.login("MarioRossi", "password123"));

    // Il nuovo Nickname deve funzionare
    EXPECT_TRUE(u.login("nuovoNick", "password123"));
}

// Testo il cambio Password
TEST(UtenteTest, ModificaPassword) {
    Utente u("MarioRossi", "vecchiaPass");

    // Controllo che la Password inserita sia giusta
    ASSERT_EQ(u.getPassword(), "vecchiaPass");

    // Modifico la password
    u.modificaPassword("nuovaPass");

    // La vecchia password non deve più funzionare
    EXPECT_FALSE(u.login("MarioRossi", "vecchiaPass"));

    // La nuova password deve funzionare
    EXPECT_TRUE(u.login("MarioRossi", "nuovaPass"));
}

TEST(UtenteTest, SalvataggioCaricamento) {

    // --- PREPARO I DATI ---
    std::string fileTest = "test_utenti_temp.txt";
    std::list<Utente*> utentiOriginali;

    // Creo Mario con 2 liste
    auto* u1 = new Utente("Mario", "1234");
    u1->aggiungiListaPermessa("casa.txt");
    u1->aggiungiListaPermessa("mamma.txt");
    utentiOriginali.push_back(u1);

    // Creo Luigi con 0 liste
    auto* u2 = new Utente("Luigi", "5678");
    utentiOriginali.push_back(u2);

    // --- SALVATAGGIO ---
    bool salvataggio = Utente::salvaUtenti(fileTest, utentiOriginali);
    EXPECT_TRUE(salvataggio);

    // --- CARICAMENTO ---
    std::list<Utente*> utentiCaricati;
    bool caricamento = Utente::caricaUtenti(fileTest, utentiCaricati);
    EXPECT_TRUE(caricamento);

    // --- VERIFICA DEI DATI ---
    // Ci devono essere 2 utenti
    ASSERT_EQ(utentiCaricati.size(), 2);

    // Controllo il primo (Mario)
    Utente* marioCaricato = utentiCaricati.front();
    EXPECT_EQ(marioCaricato->getNickname(), "Mario");
    EXPECT_EQ(marioCaricato->getPassword(), "1234");

    // Mario deve avere le sue 2 liste
    std::list<std::string> listeMario = marioCaricato->getListePermesse();
    ASSERT_EQ(listeMario.size(), 2);
    EXPECT_EQ(listeMario.front(), "casa.txt");
    EXPECT_EQ(listeMario.back(), "mamma.txt");

    // Controllo il secondo (Luigi)
    Utente* luigiCaricato = utentiCaricati.back();
    EXPECT_EQ(luigiCaricato->getNickname(), "Luigi");
    EXPECT_EQ(luigiCaricato->getPassword(), "5678");
    // Luigi non aveva liste
    EXPECT_TRUE(luigiCaricato->getListePermesse().empty());

    // --- PULIZIA ---
    // Cancello memoria allocata e file test
    for (auto* u : utentiOriginali)
        delete u;
    for (auto* u : utentiCaricati)
        delete u;
    std::remove(fileTest.c_str());
}