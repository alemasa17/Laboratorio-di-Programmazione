#include <gtest/gtest.h>
#include <gmock/gmock.h>  // Includi Google Mock
#include "../Utente.h"
#include "../Transazione.h"
#include "../Conto.h"
#include "../Notifica.h"


TEST(TransazioneTest, Costruttore) {
    Transazione trans("2025-03-01", "Pagamento", 100.0, true, "Mittente");

    EXPECT_EQ(trans.getData(), "2025-03-01");
    EXPECT_EQ(trans.getCausale(), "Pagamento");
    EXPECT_EQ(trans.getImporto(), 100.0);
    EXPECT_TRUE(trans.getInorOut()); // Ora booleano
    EXPECT_EQ(trans.getMittOrRicev(), "Mittente");
}



