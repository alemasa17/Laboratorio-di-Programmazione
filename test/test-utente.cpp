//
// Created by Alessio Masala on 26/03/25.
//

#include <gtest/gtest.h>
#include "../Utente.h"

// costruttore inizializza correttamente
TEST(UtenteTest, CostruttoreInizializzaCorrettamente) {
    Utente u("Mario", "Rossi", "RSSMRA99A01H501X");
    EXPECT_EQ(u.getNome(), "Mario");
    EXPECT_EQ(u.getCognome(), "Rossi");
    EXPECT_EQ(u.getCf(), "RSSMRA99A01H501X");
}

// test sul set
TEST(UtenteTest, SetNomeAggiornaNome) {
    Utente u("Mario", "Rossi", "RSSMRA99A01H501X");
    u.setNome("Luca");
    EXPECT_EQ(u.getNome(), "Luca");
}

// display restituisce stringa corretta
TEST(UtenteTest, DisplayRestituisceStringaCorretta) {
    Utente u("Anna", "Verdi", "VRDANN99B41F205X");
    string expected = "Nome: Anna Cognome: Verdi Codice Fiscale: VRDANN99B41F205X";
    EXPECT_EQ(u.display(), expected);
}

// test su sovraccarico
TEST(UtenteTest, OperatoreStreamOutput) {
    Utente u("Elisa", "Bianchi", "BNCLSE01H50A662Y");
    stringstream ss;
    ss << u;
    EXPECT_EQ(ss.str(), "Elisa Bianchi");
}