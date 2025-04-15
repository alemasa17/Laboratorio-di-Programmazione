//
// Created by Alessio Masala on 27/02/25.
//

#ifndef ELABORATO_ALESSIO_MASALA_CONTO_H
#define ELABORATO_ALESSIO_MASALA_CONTO_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

#include "Utente.h"
#include "Transazione.h"
#include "Subject.h"
#include "Observer.h"
#include "fstream"



class Conto : public Subject{
public:
    Conto(Utente utente) : u(utente), saldo(0.0) {
        fstream file("Transazioni.txt", ios::trunc  | ios::out | ios::in); // apre in modalità append, crea se non esiste

        if (!file.is_open()) {
            // Tentativo di creazione esplicito se l'apertura è fallita (raro, ma può capitare)
            file.open("Transazioni.txt", ios::out);
            if (!file) {
                cerr << "Errore: impossibile creare il file Transazioni.txt" << endl;
            } else {
                cout << "File Transazioni.txt creato correttamente." << endl;
            }
        }
    }


    virtual void addObserver(Observer* newObserver) override {
        _observers.push_back(newObserver);
    }
    virtual void removeObserver(Observer* delObserver) override {
        _observers.remove(delObserver);
    }
    void addTransazione(Transazione transazione){
        ofstream file("Transazioni.txt", ios::app);
        transazioni.push_back(transazione);
        if (transazione.getInorOut()){
            saldo = saldo + transazione.getImporto();
            file <<u.getCf()<< " | Movimento in Ingresso: "<< transazione.getImporto() <<"€ | Data: " << transazione.getData() << " | causale:" << transazione.getCausale() << endl;
        } else{
            saldo = saldo - transazione.getImporto();
            file <<u.getCf()<< " | Movimento in Uscita: "<<transazione.getImporto() << "€ | Data: " << transazione.getData() << " | causale:" << transazione.getCausale() << endl;
        }
        file.close();
        notify();
    }

    virtual void notify() override {
        for(list<Observer*>::iterator itr = _observers.begin(); itr != _observers.end(); ++itr) {
            (*itr)->update();
        }
    }

    double getSaldo() const {
        return saldo;
    }

    void setSaldo(double saldo) {
        Conto::saldo = saldo;
    }


    void proprietarioConto() const {
        cout<<u;
    }


    void stampaUltimaTransazione(){
        ifstream file("Transazioni.txt");
        string riga, ultimaRiga;

        cout << "------- Nuova Transazione sul conto di " << u.getNome() << " " << u.getCognome() << " -------" << endl;
        while (std::getline(file, riga)) {
            ultimaRiga = riga; // Aggiorna l'ultima riga letta
        }
        cout << ultimaRiga << endl;
        file.close();

        cout<< "----- Saldo attuale: " << saldo << "€ -----"<<endl<<endl;
    }

    /*
    void stampaTransazioni(){
        ifstream file("Transazioni.txt", std::ios::in);
        string riga;
        string cf_utente = u.getCf(); // Codice fiscale dell'utente attuale

        cout << endl << "------- Transazioni conto di ";
        proprietarioConto();
        cout<< endl;

        while (getline(file, riga)) {
            if (riga.find(cf_utente) != string::npos) { // Controlla se la riga contiene il CF dell'utente
                cout << riga << endl;
            }
        }
        cout<< "----- Saldo attuale: " << saldo << "€ -----"<<endl<<endl;
        file.close();
    }
     */

    void cercaTransData(const string& data) {
        ifstream file("Transazioni.txt", std::ios::in);
        string riga;
        string cf_utente = u.getCf(); // Codice fiscale dell'utente attuale

        cout << endl << endl << "------- Transazioni conto di ";
        proprietarioConto();
        cout <<" in data: " << data << " -------" << endl;

        while (getline(file, riga)) {
            if (riga.find(cf_utente) != string::npos && riga.find(data) != string::npos){
                cout << riga << endl;
            }
        }
        cout<<endl;
        file.close();
    }




private:
    Utente u;
    list<Transazione> transazioni;
    list<Observer*> _observers;
    double saldo;
};


#endif //ELABORATO_ALESSIO_MASALA_CONTO_H
