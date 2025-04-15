//
// Created by Alessio Masala on 27/02/25.
//

#ifndef ELABORATO_ALESSIO_MASALA_NOTIFICA_H
#define ELABORATO_ALESSIO_MASALA_NOTIFICA_H


#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

#include "Observer.h"
#include "Conto.h"
#include "Transazione.h"


class Notifica : public Observer{
public:
    Notifica(Conto* conto) : conto(conto){
        conto->addObserver(this);
    }
    ~Notifica() override{
        conto->removeObserver(this);
    }
    virtual void update() override {
        conto->stampaUltimaTransazione();
    }

private:
    Conto* conto;
};


#endif //ELABORATO_ALESSIO_MASALA_NOTIFICA_H
