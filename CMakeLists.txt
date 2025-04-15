cmake_minimum_required(VERSION 3.25)
project(elaborato_Alessio_Masala)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Abilita i test
enable_testing()

# Scarica e configura GoogleTest automaticamente
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Eseguibile principale (senza test)
add_executable(elaborato_Alessio_Masala main.cpp Data.h)

# Eseguibile per i test
add_executable(runTests
        test/test-main.cpp
        test/test-utente.cpp
        test/test-transazione.cpp
        test/test-conto.cpp
        test/test-notifica.cpp
        test/test-data.cpp)

# Linka GoogleTest ai test
target_link_libraries(runTests gtest gtest_main)
target_include_directories(runTests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Comando per eseguire tutti i test
add_test(NAME RunAllTests COMMAND runTests)
