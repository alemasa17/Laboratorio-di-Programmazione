//
// Created by Alessio Masala on 27/02/25.
//

#ifndef ELABORATO_ALESSIO_MASALA_UTENTE_H
#define ELABORATO_ALESSIO_MASALA_UTENTE_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

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
    string display() const {
        return "Nome: " + nome + " Cognome: " + cognome + " Codice Fiscale: " + cf;
    }

    // Sovraccarico dell'operatore <<
    friend ostream& operator<<(ostream& os, const Utente& u) {
        os << u.nome << " " << u.cognome;
        return os;
    }

private:
    string nome;
    string cognome;
    string cf;
};


#endif //ELABORATO_ALESSIO_MASALA_UTENTE_H
