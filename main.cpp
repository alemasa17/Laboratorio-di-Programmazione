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

    Transazione t("01/03/2025", "Stipendio", 1000, "IN", "Datore di Lavoro");
    Transazione t1("02/03/2025", "spesa", 12350, "OUT", "Coop");
    Transazione t2("03/03/2025", "Volo", 500, "OUT", "Ryanair");
    Transazione t3("04/03/2025", "Telefono", 500, "OUT", "Mediaworld");

    Transazione tr("05/03/2025", "TFR", 1000, "IN", "Datore di Lavoro");
    Transazione tr1("06/03/2025", "Carburatore", 450, "OUT", "Meccanico");
    Transazione tr2("07/03/2025", "Candele", 250, "OUT", "Meccanico");
    Transazione tr3("08/03/2025", "Licquido di Raffreddamento", 30, "OUT", "Meccanico");

    c.addTransazione(t);
    c.addTransazione(t1);
    c.addTransazione(t2);
    c.addTransazione(t3);

    c1.addTransazione(tr);
    c1.addTransazione(tr1);
    c1.addTransazione(tr2);
    c1.addTransazione(tr3);

    c.stampaTransazioni();
    c1.stampaTransazioni();





    return 0;
}
