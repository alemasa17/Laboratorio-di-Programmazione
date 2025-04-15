//
// Created by Alessio Masala on 26/03/25.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>  // Includi Google Mock
#include "../Utente.h"
#include "../Transazione.h"
#include "../Conto.h"
#include "../Notifica.h"


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