//
// Created by Alessio Masala on 27/02/25.
//

#ifndef ELABORATO_ALESSIO_MASALA_TRANSAZIONE_H
#define ELABORATO_ALESSIO_MASALA_TRANSAZIONE_H

#include "header.h"

class Transazione {
public:
    Transazione(string data, string causale, double importo, bool inOrOut, string mittOrRicev) : data(data), causale(causale), importo(importo), inOrOut(inOrOut), mittOrRicev(mittOrRicev) {

    }

    const string &getData() const {
        return data;
    }

    void setData(const string &data) {
        Transazione::data = data;
    }

    const string &getCausale() const {
        return causale;
    }

    const string &getMittOrRicev() const {
        return mittOrRicev;
    }

    void setMittOrRicev(const string &mittOrRicev) {
        Transazione::mittOrRicev = mittOrRicev;
    }

    double getImporto() const {
        return importo;
    }

    const bool &getInorOut() const {
        return inOrOut;
    }



private:
    string data;
    string causale;
    string mittOrRicev;
    double importo;
    bool inOrOut;
};


#endif //ELABORATO_ALESSIO_MASALA_TRANSAZIONE_H
