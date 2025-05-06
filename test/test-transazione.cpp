#include <gtest/gtest.h>
#include "../Transazione.h"

// costruttore valido non lancia eccezioni
TEST(TransazioneTest, CostruttoreValidoNonLanciaEccezioni) {
    Data d(1, 1, 2024);
    EXPECT_NO_THROW(Transazione t(d, "Affitto", 500.0, true));
}

// costruttore con importo negativo lancia eccezione
TEST(TransazioneTest, CostruttoreConImportoNegativoLanciaEccezione) {
    Data d(1, 1, 2024);
    EXPECT_THROW(Transazione t(d, "Errore", -50.0, false), invalid_argument);
}

// test sui getters
TEST(TransazioneTest, GettersRestituisconoValoriCorretti) {
    Data d(10, 5, 2023);
    Transazione t(d, "Stipendio", 1500.0, true);

    EXPECT_EQ(t.getData(), "10/5/2023");
    EXPECT_EQ(t.getCausale(), "Stipendio");
    EXPECT_DOUBLE_EQ(t.getImporto(), 1500.0);
    EXPECT_TRUE(t.getInorOut());
}

// test su setData
TEST(TransazioneTest, CambiandoLaDataNonCambiaLOriginale) {
    Data d1(1, 1, 2024);
    Transazione t(d1, "Acquisto", 100.0, false);
    Data d2(2, 2, 2024);

    t.setData(d2);

    EXPECT_EQ(t.getData(), "2/2/2024");
}

// test su toString
TEST(TransazioneTest, ToStringRestituisceStringaCorretta) {
    Data data(15, 4, 2024);
    Transazione t(data, "Affitto", 750.50, false);  // false = Uscita

    std::string atteso = "15/4/2024 - Uscita - 750.500000 - Affitto";

    EXPECT_EQ(t.toString(), atteso);
}
