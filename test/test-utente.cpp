//
// Created by Alessio Masala on 26/03/25.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>  // Includi Google Mock
#include "../Utente.h"
#include "../Transazione.h"
#include "../Conto.h"
#include "../Notifica.h"


TEST(UtenteTest, Costruttore) {
    Utente utente("Alessio", "Masala", "CF12345");

    EXPECT_EQ(utente.getNome(), "Alessio");
    EXPECT_EQ(utente.getCognome(), "Masala");
    EXPECT_EQ(utente.getCf(), "CF12345");
}

TEST(UtenteTest, Setters) {
    Utente utente("Alessio", "Masala", "CF12345");

    utente.setNome("Marco");
    utente.setCognome("Rossi");
    utente.setCf("CF54321");

    EXPECT_EQ(utente.getNome(), "Marco");
    EXPECT_EQ(utente.getCognome(), "Rossi");
    EXPECT_EQ(utente.getCf(), "CF54321");
}