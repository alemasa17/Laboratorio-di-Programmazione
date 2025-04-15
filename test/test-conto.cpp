//
// Created by Alessio Masala on 26/03/25.
//


#include <gtest/gtest.h>
#include "../Utente.h"
#include "../Transazione.h"
#include "../Conto.h"
#include "../Notifica.h"
#include "../Data.h"



TEST(ContoTest, Costruttore) {
    Utente utente("Alessio", "Masala", "CF12345");
    Conto conto(utente);

    EXPECT_EQ(conto.getSaldo(), 0.0);
}

TEST(ContoTest, AggiungiTransazioneIn) {
    Utente utente("Alessio", "Masala", "CF12345");
    Conto conto(utente);

    Transazione trans("2025-03-01", "Deposito", 100.00, true);
    conto.addTransazione(trans);

    EXPECT_EQ(conto.getSaldo(), 100.00);
}

TEST(ContoTest, AggiungiTransazioneOut) {
    Utente utente("Alessio", "Masala", "CF12345");
    Conto conto(utente);

    Transazione transIn("2025-03-01", "Deposito", 100.00, true, "Mittente");
    Transazione transOut("2025-03-02", "Prelievo", 50.00, false, "Ricevente");

    conto.addTransazione(transIn);
    conto.addTransazione(transOut);

    EXPECT_EQ(conto.getSaldo(), 50.00);
}

TEST(ContoTest, VerificaScritturaFile) {
    Utente utente("Alessio", "Masala", "CF67890");
    Conto conto(utente);

    Transazione trans1("2025-03-01", "Deposito", 2000.00, true);
    conto.addTransazione(trans1);

    // Leggiamo il file
    std::ifstream file("Transazioni.txt");
    std::string contenuto, riga;
    while (std::getline(file, riga)) {
    contenuto += riga + "\n";
    }
    file.close();

    // Controlliamo che il file contenga i dati giusti
    EXPECT_NE(contenuto.find("CF67890"), std::string::npos);
    EXPECT_NE(contenuto.find("Stipendio"), std::string::npos);
    EXPECT_NE(contenuto.find("2000"), std::string::npos);
}
