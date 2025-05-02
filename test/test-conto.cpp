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

// stampa tutte le transazioni (verifica che non crashi)
TEST(ContoTest, StampaTransazioniNonCrasha) {
    Utente u("Elena", "Russo", "RSSLEN99E41H501W");
    Conto conto(u);

    Data d(5, 5, 2025);
    Transazione t1(d, "Versamento", 200.0, true);
    Transazione t2(d, "Prelievo", 80.0, false);

    conto.addTransazione(t1);
    conto.addTransazione(t2);

    EXPECT_NO_THROW(conto.stampaTransazioni());
}

// cerca per data - output non testabile direttamente, ma controlliamo che non lanci errori
TEST(ContoTest, CercaTransazioniPerDataNonCrasha) {
    Utente u("Fabio", "Conti", "CNTFBA88H12F205K");
    Conto conto(u);

    Data d1(1, 4, 2025);
    Data d2(2, 4, 2025);

    conto.addTransazione(Transazione(d1, "Entrata", 100.0, true));
    conto.addTransazione(Transazione(d2, "Uscita", 30.0, false));

    EXPECT_NO_THROW(conto.cercaTransData("2025-04-02"));
}

// cerca per importo - cerca valore preciso
TEST(ContoTest, CercaTransazioniPerImportoNonCrasha) {
    Utente u("Chiara", "Gallo", "GLLCHR90T41F205L");
    Conto conto(u);

    Data d(3, 3, 2025);
    conto.addTransazione(Transazione(d, "Pagamento", 75.5, false));

    EXPECT_NO_THROW(conto.cercaTransImporto(75.5));
}

