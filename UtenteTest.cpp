//
// Created by gabriele on 08/01/26.
//

#include "gtest/gtest.h"
#include "Utente.h"

// Testiamo che il costruttore salvi correttamente i dati
TEST(UtenteTest, CostruttoreEGetter) {
    Utente u("MarioRossi", "password123");
    EXPECT_EQ(u.getNickname(), "MarioRossi");
    EXPECT_EQ(u.getPassword(), "password123");
}

// Testiamo che il login funzioni solo con le credenziali giuste
TEST(UtenteTest, FunzionamentoLogin) {
    Utente u("MarioRossi", "password123");

    // Caso Positivo
    EXPECT_TRUE(u.login("MarioRossi", "password123"));

    // Caso Negativo (Password errata)
    EXPECT_FALSE(u.login("MarioRossi", "sbagliata"));

    // Caso Negativo (Nickname errato)
    EXPECT_FALSE(u.login("LuigiVerdi", "password123"));
}

// Testiamo il cambio password
TEST(UtenteTest, ModificaPassword) {
    Utente u("MarioRossi", "vecchiaPass");

    // Modifichiamo la password
    u.modificaPassword("nuovaPass");

    // La vecchia password non deve più funzionare
    EXPECT_FALSE(u.login("MarioRossi", "vecchiaPass"));

    // La nuova password deve funzionare
    EXPECT_TRUE(u.login("MarioRossi", "nuovaPass"));
}