#include <gtest/gtest.h>
#include <gmock/gmock.h>  // Includi Google Mock
#include "../Utente.h"
#include "../Transazione.h"
#include "../Conto.h"
#include "../Notifica.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);  // Inizializza Google Test
    return RUN_ALL_TESTS();  // Esegui tutti i test
}

// Test per la classe Utente
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

// Test per la classe Transazione
TEST(TransazioneTest, Costruttore) {
    Transazione trans("2025-03-01", "Pagamento", 100.0, true, "Mittente");

    EXPECT_EQ(trans.getData(), "2025-03-01");
    EXPECT_EQ(trans.getCausale(), "Pagamento");
    EXPECT_EQ(trans.getImporto(), 100.0);
    EXPECT_TRUE(trans.getInorOut()); // Ora booleano
    EXPECT_EQ(trans.getMittOrRicev(), "Mittente");
}

// Test per la classe Conto
TEST(ContoTest, Costruttore) {
    Utente utente("Alessio", "Masala", "CF12345");
    Conto conto(utente);

    EXPECT_EQ(conto.getSaldo(), 0.0);
}

TEST(ContoTest, AggiungiTransazioneIn) {
    Utente utente("Alessio", "Masala", "CF12345");
    Conto conto(utente);

    Transazione trans("2025-03-01", "Deposito", 100.00, true, "Mittente");
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

TEST(ContoTest, StampaTransazioni) {
    Utente utente("Alessio", "Masala", "CF12345");
    Conto conto(utente);

    Transazione trans("2025-03-01", "Deposito", 100.00, true, "Mittente");
    conto.addTransazione(trans);

    testing::internal::CaptureStdout();
    conto.stampaTransazioni();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Deposito"), std::string::npos);
}

// Test per la classe Notifica
class MockObserver : public Observer {
public:
    MOCK_METHOD(void, update, (), (override));
};

TEST(NotificaTest, RiceviNotifica) {
    Utente utente("Alessio", "Masala", "CF12345");
    Conto conto(utente);
    MockObserver mockObserver;

    conto.addObserver(&mockObserver);

    EXPECT_CALL(mockObserver, update()).Times(1);

    Transazione trans("2025-03-01", "Deposito", 100.00, true, "Mittente");
    conto.addTransazione(trans);
}

TEST(ContoTest, StampaTransazioniFile) {
    Utente utente("Alessio", "Masala", "CF12345");
    Conto conto(utente);

    // Aggiungiamo transazioni
    Transazione trans1("2025-03-01", "Bonifico", 150.00, true, "Mario Rossi");
    Transazione trans2("2025-03-02", "Prelievo", 50.00, false, "Bancomat");

    conto.addTransazione(trans1);
    conto.addTransazione(trans2);

    // Cattura l'output della stampa transazioni
    testing::internal::CaptureStdout();
    conto.stampaTransazioni();
    std::string output = testing::internal::GetCapturedStdout();

    // Controlliamo che le transazioni siano presenti
    EXPECT_NE(output.find("Bonifico"), std::string::npos);
    EXPECT_NE(output.find("Prelievo"), std::string::npos);
    EXPECT_NE(output.find("Saldo attuale: 100"), std::string::npos); // 150 - 50 = 100€
}

TEST(ContoTest, VerificaScritturaFile) {
    Utente utente("Alessio", "Masala", "CF67890");
    Conto conto(utente);

    Transazione trans1("2025-03-10", "Stipendio", 2000.00, true, "Datore di lavoro");
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

