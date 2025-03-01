#include <iostream>

#include "Conto.h"
#include "Utente.h"
#include "Transazione.h"
#include "Notifica.h"


int main() {
    Utente u("Alessio", "Masala", "MSLSLS99A01H501A");
    Conto c(u);
    Notifica n(&c);

    Transazione t("01/03/2025", "Stipendio", 1000, "IN", "Datore di Lavoro");
    Transazione t1("02/03/2025", "Spesa", 30, "OUT", "Coop");
    Transazione t2("03/03/2025", "Volo", 500, "OUT", "Ryanair");
    Transazione t3("04/03/2025", "Telefono", 500, "OUT", "Mediaworld");

    c.addTransazione(t);
    c.addTransazione(t1);
    c.addTransazione(t2);
    c.addTransazione(t3);

    c.stampaTransazioni();






    return 0;
}
