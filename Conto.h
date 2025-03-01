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
        // Prova ad aprire il file in lettura
        file.open("Transazioni.txt", std::ios::in);

        // Se non esiste, crealo in modalità scrittura
        if (!file.is_open()) {
            file.close();  // Chiudi il file se non esiste
            file.open("Transazioni.txt", std::ios::out);  // Crea il file vuoto
        }
    }


    virtual void addObserver(Observer* newObserver) override {
        _observers.push_back(newObserver);
    }
    virtual void removeObserver(Observer* delObserver) override {
        _observers.remove(delObserver);
    }
    void addTransazione(Transazione transazione){
        file.open("Transazioni.txt", std::ios::app);
        transazioni.push_back(transazione);
        if (transazione.getInorOut() == "IN"){
            saldo += transazione.getImporto();
            file << "Movimento in Ingresso: "<< transazione.getImporto() << "€ | mittente: " << transazione.getMittOrRicev() << " | causale:" << transazione.getCausale() << endl;
            file << "Saldo attuale: " << saldo << endl<<endl;
        } else {
            saldo -= transazione.getImporto();
            file << "Movimento in Uscita: "<<transazione.getImporto() << "€ | ricevente: " << transazione.getMittOrRicev() << " | causale:" << transazione.getCausale() << endl;
            file << "Saldo attuale: " << saldo << endl<<endl;
        }
        file.flush();
        notify();
    }

    virtual void notify() override {
        for(list<Observer*>::iterator itr = _observers.begin(); itr != _observers.end(); ++itr) {
            (*itr)->update();
        }
    }

    void getSaldo(){
        cout << "Saldo attuale: " << saldo << endl;
    }
    void setSaldo(double saldo) {
        Conto::saldo = saldo;
    }

    void stampaTransazioni(){
        string riga;
        while (std::getline(file, riga)) { // Legge riga per riga
            std::cout << riga << std::endl;
        }
    }

    string lastTransazione() const{
        ifstream file("Transazioni.txt", std::ios::in);
        file.seekg(0);
        string riga, ultimaRiga;
        while (getline(file, riga)) {
            ultimaRiga = riga;
        }
        return ultimaRiga;
    }


private:
    Utente u;
    list<Transazione> transazioni;
    list<Observer*> _observers;
    double saldo;
    fstream file;
};


#endif //ELABORATO_ALESSIO_MASALA_CONTO_H
