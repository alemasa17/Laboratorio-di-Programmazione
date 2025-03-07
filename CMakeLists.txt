cmake_minimum_required(VERSION 3.25)
project(elaborato_Alessio_Masala)

set(CMAKE_CXX_STANDARD 17)

# Aggiungi FetchContent per scaricare Google Test e Google Mock
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

# Fai in modo che Google Test e Google Mock vengano scaricati e compilati
FetchContent_MakeAvailable(googletest)

# Aggiungi il tuo progetto principale
add_executable(elaborato_Alessio_Masala main.cpp Conto.h Transazione.h header.h Notifica.h Observer.h Subject.h Utente.h)

# Aggiungi l'eseguibile per i test
add_executable(test test-elaborato.cpp)

# Collega GoogleTest e GoogleMock al tuo eseguibile di test
target_link_libraries(test_elaborato gtest gmock gtest_main)

# Abilita i test
enable_testing()

# Aggiungi il test
add_test(NAME TestElaborato COMMAND test_elaborato)

# Collega anche il tuo progetto principale a GoogleTest e GoogleMock (opzionale)
target_link_libraries(elaborato_Alessio_Masala gtest gmock gtest_main)
