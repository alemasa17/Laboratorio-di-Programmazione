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



    void cercaTransData(const string &data) {
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

    void eliminaTrans(const string &data, string causale, string importo){
        std::ifstream file("Transazioni.txt");
        std::ofstream fileTemp("Transazioni_temp.txt");
        string riga, rigaDaEliminare;
        string cf_utente = u.getCf(); // Codice fiscale dell'utente attuale


        cout << endl << endl << "------- Elimino Transazione conto di ";
        proprietarioConto();
        cout <<" in data: " << data << ", di importo: " << importo << ", con causale: "<< causale << " -------" << endl;

        while (getline(file, riga)) {
            if (riga.find(cf_utente) != string::npos && riga.find(data) != string::npos && riga.find(causale) != string::npos && riga.find(importo) != string::npos){
                rigaDaEliminare = riga;
                cout << "Trovata transazione da eliminare: " << rigaDaEliminare << endl;
            }
        }

        file.clear();        // Pulisce eventuali errori nel flusso
        file.seekg(0, ios::beg); // Torna all'inizio del file

        while (getline(file, riga)) {
            if (riga != rigaDaEliminare) { // Scrive solo le righe che non sono da eliminare
                fileTemp << riga << endl;
            }
        }

        remove("Transazioni.txt"); // Rimuove il file originale
        rename("Transazioni_temp.txt", "Transazioni.txt"); // Rinomina il file temporaneo
        fileTemp.close();
        cout << "Transazione eliminata " << rigaDaEliminare << endl;
        cout << "------- Listato dopo rimozione ------- "<<endl;
        stampaTransazioni();

    }


    void stampaTransazioni(){
        ifstream file("Transazioni.txt", std::ios::in);
        string riga;
        string cf_utente = u.getCf(); // Codice fiscale dell'utente attuale


        while (getline(file, riga)) {
            if (riga.find(cf_utente) != string::npos) { // Controlla se la riga contiene il CF dell'utente
                cout << riga << endl;
            }
        }
        file.close();
    }



private:
    Utente u;
    list<Transazione> transazioni;
    list<Observer*> _observers;
    double saldo;
};


#endif //ELABORATO_ALESSIO_MASALA_CONTO_H
