//
// Created by Alessio Masala on 02/04/25.
//


#include "../Data.h"
#include <gtest/gtest.h>

// Test costruttore con data valida
TEST(TestData, CostruttoreDataValida) {
    EXPECT_NO_THROW(Data(15, 6, 2023));  // Data valida
    EXPECT_NO_THROW(Data(29, 2, 2024));  // Anno bisestile
    EXPECT_NO_THROW(Data(1, 1, 2000));   // Primo giorno dell'anno
    EXPECT_NO_THROW(Data(31, 12, 2022)); // Ultimo giorno dell'anno
}

// Test costruttore con giorno non valido
TEST(TestData, GiornoNonValido) {
    EXPECT_THROW(Data(32, 1, 2023), std::invalid_argument);  // 32 gennaio
    EXPECT_THROW(Data(0, 1, 2023), std::invalid_argument);   // 0 gennaio
    EXPECT_THROW(Data(31, 4, 2023), std::invalid_argument);  // Aprile ha 30 giorni
}

// Test costruttore con febbraio non valido
TEST(TestData, FebbraioNonValido) {
    EXPECT_THROW(Data(30, 2, 2023), std::invalid_argument); // Febbraio ha max 28 giorni
    EXPECT_THROW(Data(29, 2, 2023), std::invalid_argument); // 2023 NON è bisestile
    EXPECT_NO_THROW(Data(29, 2, 2024)); // 2024 è bisestile
}

// Test costruttore con mese non valido
TEST(TestData, MeseNonValido) {
    EXPECT_THROW(Data(10, 0, 2023), std::invalid_argument);  // Mese 0 non esiste
    EXPECT_THROW(Data(15, 13, 2023), std::invalid_argument); // Mese 13 non esiste
}

// Test costruttore con anno non valido
TEST(TestData, AnnoNonValido) {
    int annoCorrente = Data::getAnnoCorrente();
    EXPECT_THROW(Data(10, 5, 1899), std::invalid_argument);  // Anno troppo vecchio
    EXPECT_THROW(Data(10, 5, annoCorrente + 1), std::invalid_argument); // Anno futuro
}

// Test stampaData (controlliamo solo che non dia errori)
TEST(TestData, StampaData) {
    Data d(10, 10, 2023);
    EXPECT_NO_THROW(d.toString());
}