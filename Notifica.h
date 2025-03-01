//
// Created by Alessio Masala on 27/02/25.
//

#ifndef ELABORATO_ALESSIO_MASALA_NOTIFICA_H
#define ELABORATO_ALESSIO_MASALA_NOTIFICA_H

#include "Observer.h"
#include "Conto.h"
#include "Transazione.h"


class Notifica : public Observer{
public:
    Notifica(Conto* conto) : conto(conto){
        conto->addObserver(this);
    }
    ~Notifica(){
        conto->removeObserver(this);
    }
    virtual void update() override {
        cout << "Nuova transazione effettuata!" << endl;
        cout << conto->lastTransazione()<<endl;
    }

private:
    Conto* conto;
};


#endif //ELABORATO_ALESSIO_MASALA_NOTIFICA_H
