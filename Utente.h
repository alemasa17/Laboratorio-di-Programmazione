//
// Created by Alessio Masala on 27/02/25.
//

#ifndef ELABORATO_ALESSIO_MASALA_UTENTE_H
#define ELABORATO_ALESSIO_MASALA_UTENTE_H

#include "header.h"

class Utente {
public:
    Utente(string nome, string cognome, string cf) : nome(nome), cognome(cognome), cf(cf) {}

    const string &getNome() const {
        return nome;
    }
    void setNome(const string &nome) {
        Utente::nome = nome;
    }
    const string &getCognome() const {
        return cognome;
    }
    void setCognome(const string &cognome) {
        Utente::cognome = cognome;
    }
    const string &getCf() const {
        return cf;
    }

    void setCf(const string &cf) {
        Utente::cf = cf;
    }
    void display(){
        cout << "Nome: " << nome << " Cognome: " << cognome << " Codice Fiscale: " << cf << endl;
    }

private:
    string nome;
    string cognome;
    string cf;
};


#endif //ELABORATO_ALESSIO_MASALA_UTENTE_H
