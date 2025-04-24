#include <gtest/gtest.h>
#include "../Notifica.h"
#include <sstream>
#include <fstream>

// Redirect cout temporaneamente per catturare l'output
class CoutRedirect {
    std::streambuf* old_buf;
    std::ostringstream oss;
public:
    CoutRedirect() {
        old_buf = std::cout.rdbuf(oss.rdbuf());
    }

    ~CoutRedirect() {
        std::cout.rdbuf(old_buf);
    }

    std::string getOutput() const {
        return oss.str();
    }
};

// notifica si registra a conto
TEST(NotificaTest, NotificaSiRegistraAConto) {
    Utente u("Marco", "Test", "TSTMRC01X00X000X");
    Conto conto(u);
    Notifica* notifica = new Notifica(&conto);

    Data d(1, 1, 2024);
    Transazione t(d, "Deposito", 50.0, true);

    CoutRedirect cr;
    conto.addTransazione(t);

    std::string output = cr.getOutput();
    EXPECT_NE(output.find("Nuova Transazione sul conto di"), std::string::npos);
    EXPECT_NE(output.find("Deposito"), std::string::npos);
    EXPECT_NE(output.find("50"), std::string::npos);

    delete notifica;
}

// notifica si rimuove alla distruzione
TEST(NotificaTest, NotificaSiRimuoveAllaDistruzione) {
    Utente u("Laura", "Debug", "DBGLRA02Y00Y000Y");
    Conto conto(u);

    {
        Notifica notifica(&conto); // Alla fine del blocco verrà distrutto e rimosso
    }

    Data d(2, 2, 2024);
    Transazione t(d, "Prelievo", 25.0, false);

    CoutRedirect cr;
    conto.addTransazione(t); // Non dovrebbe stampare nulla, observer è stato rimosso

    std::string output = cr.getOutput();
    EXPECT_TRUE(output.empty());
}


// notifica stampa ultima transazione
TEST(NotificaTest, StampaUltimaTransazioneDaUpdate) {
    Utente u("Alessia", "Rossi", "RSSALS03Z00Z000Z");
    Conto conto(u);
    Notifica notifica(&conto);

    Data d(3, 3, 2024);
    Transazione t(d, "Pagamento", 30.0, false);

    CoutRedirect cr;
    conto.addTransazione(t);

    std::string output = cr.getOutput();
    EXPECT_NE(output.find("Pagamento"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
}
