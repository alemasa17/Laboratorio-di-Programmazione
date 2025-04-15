//
// Created by Alessio Masala on 02/04/25.
//


#include <iostream>
#include <stdexcept>
#include <ctime>

using namespace std;

class Data {
public:
    Data(int giorno, int mese, int anno) : giorno(giorno), mese(mese), anno(anno) {
        int annoCorrente = getAnnoCorrente();

        if (mese < 1 || mese > 12) {
            throw invalid_argument("Mese non valido! Deve essere tra 1 e 12.");
        }

        if (giorno < 1 || giorno > giorniNelMese(mese, anno)) {
            throw invalid_argument("Giorno non valido per il mese specificato.");
        }

        if (anno < 1900 || anno > annoCorrente) {
            throw invalid_argument("Anno non valido! Deve essere tra 1900 e l'anno corrente.");
        }
    }

    string prendiData() const {
        string data = to_string(giorno) + "/" + to_string(mese) + "/" + to_string(anno);
        return data;
    }

    // Funzione per ottenere l'anno corrente
    static int getAnnoCorrente() {
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        return now->tm_year + 1900;
    }

    // Funzione per verificare se un anno è bisestile
    static bool isBisestile(int anno) {
        return (anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0);
    }

    // Funzione per ottenere il numero di giorni di un mese specifico
    static int giorniNelMese(int mese, int anno) {
        static const int giorniPerMese[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if (mese == 2) // Febbraio
            return isBisestile(anno) ? 29 : 28;
        return giorniPerMese[mese - 1];
    }

private:
    int giorno, mese, anno;
};