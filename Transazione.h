//
// Created by Alessio Masala on 27/02/25.
//

#ifndef ELABORATO_ALESSIO_MASALA_TRANSAZIONE_H
#define ELABORATO_ALESSIO_MASALA_TRANSAZIONE_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

#include "Data.h"

class Transazione {
public:
    Transazione(Data d, string c, double i, bool io) : data(d), causale(c), importo(i), inOrOut(io) {
        if (importo < 0) {
            throw invalid_argument("L'importo non può essere negativo.");
        }
    }

    string getData() const {
        return data.prendiData();
    }

    void setData(const Data &data) {
        Transazione::data = Data(data);
    }

    const string &getCausale() const {
        return causale;
    }


    double getImporto() const {
        return importo;
    }

    const bool &getInorOut() const {
        return inOrOut;
    }

    string stampa(){
        string transazione, inorout;
        if(inOrOut){
            inorout = "Entrata";
        } else{
            inorout = "Uscita";
        }
        transazione = data.prendiData() + " - " + inorout + " - " + to_string(importo) + " - " + causale;
        return transazione;
    }



private:
    Data data;
    string causale;
    double importo;
    bool inOrOut;
};


#endif //ELABORATO_ALESSIO_MASALA_TRANSAZIONE_H
