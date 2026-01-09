cmake_minimum_required(VERSION 4.1)
project(ProgettoListaSpesa)

# Impostiamo lo standard a C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download e Configurazione Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Includiamo la cartella corrente per trovare i file .h
include_directories(.)

# Definiamo i file sorgente del programma
set(SOURCE_FILES
        main.cpp
        Utente.cpp
        Utente.h
        Subject.h
        Observer.h
        Prodotto.h
        Prodotto.cpp
        ListaSpesa.h
        ListaSpesa.cpp
)

add_executable(ProgettoListaSpesa ${SOURCE_FILES})

add_executable(EseguiTest
        UtenteTest.cpp
        ProdottoTest.cpp
        ListaSpesaTest.cpp
        ObserverTest.cpp
        Utente.cpp
        Utente.h
        Subject.h
        Observer.h
        Prodotto.h
        Prodotto.cpp
        ListaSpesa.h
        ListaSpesa.cpp
)

target_link_libraries(EseguiTest gtest_main)