#include <gtest/gtest.h>
#include "../Conto.h"
#include "../Transazione.h"


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


TEST(ContoTest, CercaTransazioniPerDataRitornaCorretti) {
    Utente u("Marco", "Blu", "BLUMRC90D01H501B");
    Conto conto(u);

    Data d1(10, 4, 2024);
    Data d2(11, 4, 2024);

    Transazione t1(d1, "Bonifico", 100.0, true);
    Transazione t2(d1, "Pagamento", 50.0, false);
    Transazione t3(d2, "Altro", 30.0, true);

    conto.addTransazione(t1);
    conto.addTransazione(t2);
    conto.addTransazione(t3);

    auto risultati = conto.cercaTransData(d1.toString());

    ASSERT_EQ(risultati.size(), 2);
    for (const auto& t : risultati) {
        EXPECT_EQ(t.getData(), d1.toString());
    }
}

TEST(ContoTest, CercaTransazioniPerImportoRitornaCorretti) {
    Utente u("Sofia", "Gialli", "GLLSFI80E01F205Z");
    Conto conto(u);

    Data d(1, 3, 2024);
    conto.addTransazione(Transazione(d, "Ricarica", 20.0, true));
    conto.addTransazione(Transazione(d, "Spesa", 20.0, false));
    conto.addTransazione(Transazione(d, "Altro", 15.0, true));

    auto risultati = conto.cercaTransImporto(20.0);

    ASSERT_EQ(risultati.size(), 2);
    for (const auto& t : risultati) {
        EXPECT_DOUBLE_EQ(t.getImporto(), 20.0);
    }
}

TEST(ContoTest, EliminaTransazioneRiesceQuandoEsiste) {
    Utente u("Luigi", "Neri", "NRILGU70A01F205K");
    Conto conto(u);

    Data d(15, 3, 2024);
    Transazione t(d, "Affitto", 500.0, false);
    conto.addTransazione(t);

    // Verifica che venga trovata ed eliminata
    bool risultato = conto.eliminaTransazione(d.toString(), "Affitto", 500.0);
    EXPECT_TRUE(risultato);

    // Verifica che non ci siano più transazioni
    auto risultati = conto.cercaTransImporto(500.0);
    EXPECT_TRUE(risultati.empty());
}

TEST(ContoTest, EliminaTransazioneFallisceQuandoNonEsiste) {
    Utente u("Elena", "Viola", "VLEELN65B01H501M");
    Conto conto(u);

    Data d(20, 3, 2024);
    conto.addTransazione(Transazione(d, "Spesa", 100.0, false));

    // Prova a eliminare una transazione che non esiste
    bool risultato = conto.eliminaTransazione(d.toString(), "Cinema", 50.0);
    EXPECT_FALSE(risultato);
}



