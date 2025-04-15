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

    Data d(1, 3, 2025);
    Data d1(1, 3, 2025);
    Data d2(4, 3, 2025);
    Data d3(4, 3, 2025);

    Transazione t(d, "Stipendio", 1000, true);
    Transazione t1(d1, "spesa", 50, false);
    Transazione t2(d2, "Volo", 300, false);
    Transazione t3(d3, "Telefono", 500, false);

    Transazione tr(d, "TFR", 1000, true);
    Transazione tr1(d1,  "Carburatore", 450, false);
    Transazione tr2(d2, "Candele", 250, false);
    Transazione tr3(d3, "Liquido di Raffreddamento", 30, false);

    c.addTransazione(t);
    c.addTransazione(t1);
    c.addTransazione(t2);
    c.addTransazione(t3);

    c1.addTransazione(tr);
    c1.addTransazione(tr1);
    c1.addTransazione(tr2);
    c1.addTransazione(tr3);

    c.cercaTransData("1/3/2025");
    c1.cercaTransData("4/3/2025");




    return 0;
}
