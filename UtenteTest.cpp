//
// Created by gabriele on 08/01/26.
//

#include "gtest/gtest.h"
#include "Utente.h"

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