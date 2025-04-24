#include <gtest/gtest.h>
#include "../Conto.h"

// Mock Observer per testare il notify
class MockObserver : public Observer {
public:
    bool notified = false;
    void update() override {
        notified = true;
    }
};


// conto inizializzato con 0.0
TEST(ContoTest, ContoSiInizializzaConSaldoZero) {
    Utente u("Mario", "Rossi", "RSSMRA00A01H501A");
    Conto conto(u);

    EXPECT_DOUBLE_EQ(conto.getSaldo(), 0.0);
}

// conto notifica observer
TEST(ContoTest, AddTransazioneAggiornaSaldoENotificaObserver) {
    Utente u("Luca", "Verdi", "VRDLUC90B01F205Z");
    Conto conto(u);
    MockObserver obs;
    conto.addObserver(&obs);

    Data d(1, 1, 2024);
    Transazione t(d, "Bonifico", 100.0, true);
    conto.addTransazione(t);

    EXPECT_DOUBLE_EQ(conto.getSaldo(), 100.0);
    EXPECT_TRUE(obs.notified);
}

// saldo diminuisce con transazione negativa
TEST(ContoTest, AggiuntaTransazioneUscitaRiduceSaldo) {
    Utente u("Giulia", "Bianchi", "BNCGLI95C41F205Y");
    Conto conto(u);

    Data d(1, 1, 2024);
    Transazione t(d, "Acquisto", 50.0, false); // Uscita
    conto.addTransazione(t);

    EXPECT_DOUBLE_EQ(conto.getSaldo(), -50.0);
}

// test su ultima transazione
TEST(ContoTest, StampaUltimaTransazioneNonCrasha) {
    Utente u("Andrea", "Neri", "NRIAND88D01F205X");
    Conto conto(u);

    Data d(2, 2, 2024);
    Transazione t(d, "Prova", 10.0, true);
    conto.addTransazione(t);

    // Non testiamo l'output, ma verifichiamo che la funzione non lanci eccezioni
    EXPECT_NO_THROW(conto.stampaUltimaTransazione());
}
