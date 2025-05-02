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

        cout << "------- Nuova Transazione sul conto di " ;
        proprietarioConto();
        cout << " -------" << endl;

        while (std::getline(file, riga)) {
            ultimaRiga = riga; // Aggiorna l'ultima riga letta
        }
        cout << ultimaRiga << endl;
        file.close();

        cout<< "----- Saldo attuale: " << saldo << "€ -----"<<endl<<endl;
    }


    void cercaTransData(const string &data){
        string transazione;
        cout << endl << "Transazioni in data: " << data << " sul conto di ";
        proprietarioConto();
        cout<<endl;
        for(auto i = transazioni.begin();i != transazioni.end(); i++){
            if(i->getData() == data){
                transazione =  i->stampa();
                cout << transazione << endl;
            }
        }
    }

    void cercaTransImporto(double importo){
        string transazione;
        cout << endl << "Transazioni con importo: " << importo << " sul conto di ";
        proprietarioConto();
        cout<<endl;
        for(auto i = transazioni.begin();i != transazioni.end(); i++){
            if(i->getImporto() == importo){
                transazione =  i->stampa();
                cout << transazione << endl;
            }
        }
    }

    void eliminaTransazione(string data, string causale, double importo){
        cout << endl << "Transazione da eliminare: " << causale << endl;
        for(auto i = transazioni.begin();i != transazioni.end(); i++){
           if(i->getData() == data && i->getCausale() == causale && i->getImporto() == importo){
                transazioni.erase(i);
                cout << "Transazione eliminata: " << causale <<"| transazioni rimanenti: "<< endl;
                stampaTransazioni();
                break;
           }
        }
    }

    void stampaTransazioni(){
        string transazione;
        for(auto i = transazioni.begin();i != transazioni.end(); i++){
            transazione =  i->stampa();
            cout << transazione << endl;
            }
        }


private:
    Utente u;
    list<Transazione> transazioni;
    list<Observer*> _observers;
    double saldo;
};


#endif //ELABORATO_ALESSIO_MASALA_CONTO_H
