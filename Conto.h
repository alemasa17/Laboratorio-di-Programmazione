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
        file.open("Transazioni.txt", std::ios::in | std::ios::out | std::ios::trunc);  // Modalità "trunc" per svuotare il file esistente
        if (!file) {
            std::cerr << "File non esistente, creazione di Transazioni.txt...\n";
            file.close();  // Chiudi il file prima di provare a crearne uno nuovo
            file.open("Transazioni.txt", std::ios::out);  // Modalità solo scrittura per crearlo
        }
        // Verifica se l'apertura è andata a buon fine
        if (!file) {
            std::cerr << "Errore nell'aprire o creare il file!" << std::endl;
        } else {
            // Se il file è stato aperto correttamente, chiudilo per ora
            file.close();
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
            file <<u.getCf()<< " | Movimento in Ingresso: "<< transazione.getImporto() << "€ | mittente: " << transazione.getMittOrRicev() << " | causale:" << transazione.getCausale() << endl;
            file << "Saldo attuale: " << saldo << endl<<endl;
        } else {
            saldo -= transazione.getImporto();
            file <<u.getCf()<< " | Movimento in Uscita: "<<transazione.getImporto() << "€ | ricevente: " << transazione.getMittOrRicev() << " | causale:" << transazione.getCausale() << endl;
            file << "Saldo attuale: " << saldo << endl<<endl;
        }
        file.flush();
        file.close();
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
        /*
        ifstream file("Transazioni.txt", std::ios::in);
        string riga;

        cout<<endl<<"-------Transazioni conto di "<<u.getNome() << " "<< u.getCognome()<< "-------"<<endl;
        while (std::getline(file, riga)) { // Legge riga per riga
            std::cout << riga<<endl;
        }
        cout<<endl<<endl;
         */
        ifstream file("Transazioni.txt", std::ios::in);
        string riga;
        string cf_utente = u.getCf(); // Codice fiscale dell'utente attuale

        cout << endl << "------- Transazioni conto di " << u.getNome() << " " << u.getCognome() << " -------" << endl;

        while (getline(file, riga)) {
            if (riga.find(cf_utente) != string::npos) { // Controlla se la riga contiene il CF dell'utente
                cout << riga << endl;
            }
        }

        cout << endl << endl;
        file.close();
    }

    /*
    string lastTransazione() const {
        ifstream file("Transazioni.txt", std::ios::in);  // Apre il file in modalità lettura
        if (!file) {  // Verifica se il file è stato aperto correttamente
            cerr << "Errore nell'aprire il file per la lettura!" << endl;
            return "";  // Ritorna una stringa vuota se il file non è stato aperto
        }
        cout << "Ho aperto il file e ora cerco l'ultima transazione" << endl;
        string riga, ultimaRiga;
        while (getline(file, riga)) {
            ultimaRiga = riga;  // Memorizza ogni riga, alla fine avrai l'ultima
        }
        cout << "L'ultima transazione è: " << ultimaRiga << endl;
        file.close();  // Chiudi il file
        return ultimaRiga;  // Ritorna l'ultima riga letta
    }
     */

    void proprietarioConto() const {
        cout << u.getNome() << " " << u.getCognome()<<endl;
    }


private:
    Utente u;
    list<Transazione> transazioni;
    list<Observer*> _observers;
    double saldo;
    fstream file;
};


#endif //ELABORATO_ALESSIO_MASALA_CONTO_H
