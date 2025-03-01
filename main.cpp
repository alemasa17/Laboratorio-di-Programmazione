#include <iostream>

#include "Conto.h"
#include "Utente.h"
#include "Transazione.h"
#include "Notifica.h"


int main() {
    Utente u("Alessio", "Masala", "MSLSLS99A01H501A");
    Conto c(u);
    Notifica n(&c);
    c.addObserver(&n);

    Transazione t("27/02/2025", "Stipendio", 1000, true, 1000, "Azienda");
    Transazione t1("27/02/2025", "Affitto", -500, false, 500, "Proprietario");
    Transazione t2("27/02/2025", "Spesa", -100, false, 400, "Supermercato");
    Transazione t3("27/02/2025", "Ricarica", 50, true, 450, "Amico");


    c.addTransazione(t);
    c.addTransazione(t1);
    c.addTransazione(t2);
    c.addTransazione(t3);





    return 0;
}
