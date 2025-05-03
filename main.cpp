#include <iostream>

#include "Conto.h"
#include "Utente.h"
#include "Transazione.h"
#include "Notifica.h"


int main() {
    Utente u("Alessio", "Masala", "MSLSLS99A01H501A");
    Utente ut("Cristian", "Polisi", "PLSCST02A21B036H");

    Conto c(u);
    Conto c1(ut);

    Notifica n(&c);
    Notifica n1(&c1);

    Data d(5, 3, 2025);
    Data d1(1, 3, 2025);
    Data d2(4, 3, 2025);
    Data d3(4, 3, 2025);

    Transazione t(d, "Stipendio", 1000, true);
    Transazione t1(d1, "spesa", 50, false);
    Transazione t2(d1, "Volo", 300, false);
    Transazione t3(d3, "Telefono", 500, false);


    Transazione tr(d, "TFR", 1000, true);
    Transazione tr1(d1,  "Carburatore", 450, false);
    Transazione tr2(d2, "Candele", 250, false);
    Transazione tr3(d2, "Liquido di Raffreddamento", 30, false);

    c.addTransazione(t);
    c.addTransazione(t1);
    c.addTransazione(t2);
    c.addTransazione(t3);

    c1.addTransazione(tr);
    c1.addTransazione(tr1);
    c1.addTransazione(tr2);
    c1.addTransazione(tr3);


    cout<< "----- Transazioni conto 1 di importo 1000: -----" << endl;
    for (const auto& t : c.cercaTransImporto(1000)) {
        cout << t.toString() << endl;
    }
    cout<< "----- Transazioni conto 2 di importo 450: -----" << endl;
    for(const auto& t1 : c1.cercaTransImporto(450)){
        cout << t1.toString() << endl;
    }

    cout << endl << endl;

    cout<< "----- Transazioni conto 1 in data 1/3/2025: -----" << endl;
    for (const auto& t : c.cercaTransData("1/3/2025")) {
        cout << t.toString() << endl;
    }
    cout<< "----- Transazioni conto 2 in data 1/3/2025: -----" << endl;
    for (const auto& t : c1.cercaTransData("1/3/2025")) {
        cout << t.toString() << endl;
    }

    cout << endl << endl;


    // elimina transazione primo conto
    cout<<"----- Eliminazione transazione sul conto 1 in data 1/3/2025, causale Stipendio, importo 1000 -----"<<endl;
    if(c.eliminaTransazione("1/3/2025", "Stipendio", 1000))
        cout << "Transazione eliminata con successo" << endl;
    else
        cout << "Transazione non trovata" << endl;

    // elimina transazione secondo conto
    cout<<"----- Eliminazione transazione sul conto 2 in data 1/3/2025, causale Carburatore, importo 450 -----"<<endl;
    if(c1.eliminaTransazione("1/3/2025", "Carburatore", 450))
        cout << "Transazione eliminata con successo" << endl;
    else
        cout << "Transazione non trovata" << endl;


    return 0;
}
