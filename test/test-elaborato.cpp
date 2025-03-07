 //
// Created by Alessio Masala on 05/03/25.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>  // Includi Google Mock
#include "../Utente.h"
#include "../Transazione.h"
#include "../Conto.h"
#include "../Notifica.h"

// Te
// st per la classe Utente
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
Transazione trans("2025-03-01", "Pagamento", 100.0, "IN", "Mittente");

EXPECT_EQ(trans.getData(), "2025-03-01");
EXPECT_EQ(trans.getCausale(), "Pagamento");
EXPECT_EQ(trans.getImporto(), 100.0);
EXPECT_EQ(trans.getInorOut(), "IN");
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

Transazione trans("2025-03-01", "Deposito", 100.00, "IN", "Mittente");
conto.addTransazione(trans);

EXPECT_EQ(conto.getSaldo(), 100.00);
}

TEST(ContoTest, AggiungiTransazioneOut) {
Utente utente("Alessio", "Masala", "CF12345");
Conto conto(utente);

Transazione transIn("2025-03-01", "Deposito", 100.00, "IN", "Mittente");
Transazione transOut("2025-03-02", "Prelievo", 50.00, "OUT", "Ricevente");

conto.addTransazione(transIn);
conto.addTransazione(transOut);

EXPECT_EQ(conto.getSaldo(), 50.0);
}

TEST(ContoTest, StampaTransazioni) {
Utente utente("Alessio", "Masala", "CF12345");
Conto conto(utente);

Transazione trans("2025-03-01", "Deposito", 100.00, "IN", "Mittente");
conto.addTransazione(trans);

testing::internal::CaptureStdout();
conto.stampaTransazioni();
std::string output = testing::internal::GetCapturedStdout();
EXPECT_NE(output.find("Deposito"), std::string::npos);
}

// Test per la classe Notifica
 class MockObserver : public Observer {
 public:
     // Mock del metodo update
     MOCK_METHOD(void, update, (), (override));
 };


TEST(NotificaTest, RiceviNotifica) {
Utente utente("Alessio", "Masala", "CF12345");
Conto conto(utente);
MockObserver mockObserver;

conto.addObserver(&mockObserver);

EXPECT_CALL(mockObserver, update()).Times(1);

Transazione trans("2025-03-01", "Deposito", 100.00, "In", "Mittente");
conto.addTransazione(trans);
}


