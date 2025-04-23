//
// Created by Alessio Masala on 26/03/25.
//

#include <gtest/gtest.h>
#include "../Utente.h"

TEST(UtenteTest, CostruttoreInizializzaCorrettamente) {
    Utente u("Mario", "Rossi", "RSSMRA99A01H501X");
    EXPECT_EQ(u.getNome(), "Mario");
    EXPECT_EQ(u.getCognome(), "Rossi");
    EXPECT_EQ(u.getCf(), "RSSMRA99A01H501X");
}

TEST(UtenteTest, SetNomeAggiornaNome) {
    Utente u("Mario", "Rossi", "RSSMRA99A01H501X");
    u.setNome("Luca");
    EXPECT_EQ(u.getNome(), "Luca");
}

TEST(UtenteTest, DisplayRestituisceStringaCorretta) {
    Utente u("Anna", "Verdi", "VRDANN99B41F205X");
    string expected = "Nome: Anna Cognome: Verdi Codice Fiscale: VRDANN99B41F205X";
    EXPECT_EQ(u.display(), expected);
}

TEST(UtenteTest, OperatoreStreamOutput) {
    Utente u("Elisa", "Bianchi", "BNCLSE01H50A662Y");
    stringstream ss;
    ss << u;
    EXPECT_EQ(ss.str(), "Elisa Bianchi");
}