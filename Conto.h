//
// Created by Alessio Masala on 27/02/25.
//

#ifndef ELABORATO_ALESSIO_MASALA_CONTO_H
#define ELABORATO_ALESSIO_MASALA_CONTO_H

#include "header.h"
#include "Utente.h"
#include "Transazione.h"
#include "Subject.h"
#include "Observer.h"
#include "fstream"



class Conto : public Subject{
public:
    Conto(Utente utente) : u(utente), saldo(0){
        file.open("Transazioni.txt", std::ios::in | std::ios::out | std::ios::trunc);
        file.close();
    }


    virtual void addObserver(Observer* newObserver) override {
        _observers.push_back(newObserver);
    }
    virtual void removeObserver(Observer* delObserver) override {
        _observers.remove(delObserver);
    }
    void addTransazione(Transazione transazione){
        fstream file;
        transazioni.push_back(transazione);
        if (transazione.getInorOut() == "IN"){
            saldo += transazione.getImporto();
            file << "Hai ricevuto "<<transazione.getImporto() << "€ da: " << transazione.getMittOrRicev() << " per " << transazione.getCausale() << endl;
            file << "Saldo attuale: " << saldo << endl<<endl;
        } else {
            saldo -= transazione.getImporto();
            file << "Hai dato "<<transazione.getImporto() << "€ a " << transazione.getMittOrRicev() << " per " << transazione.getCausale() << endl;
            file << "Saldo attuale: " << saldo << endl<<endl;
        }
        notify();
        file.close();
    }

    virtual void notify() override {
        for(list<Observer*>::iterator itr = _observers.begin(); itr != _observers.end(); ++itr) {
            (*itr)->update();
            (*itr)->draw();
        }
    }

    void getSaldo(){
        cout << "Saldo attuale: " << saldo << endl;
    }
    void setSaldo(double saldo) {
        Conto::saldo = saldo;
    }

    void stampaTransazioni(){
        ifstream file;
        string riga;
        while (std::getline(file, riga)) { // Legge riga per riga
            std::cout << riga << std::endl;
        }
        file.close()
    }

    const Transazione& lastTransazione() const{ return transazioni.back();}


private:
    Utente u;
    list<Transazione> transazioni;
    list<Observer*> _observers;
    double saldo;
    fstream file;
};


#endif //ELABORATO_ALESSIO_MASALA_CONTO_H
