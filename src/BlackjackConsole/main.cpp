#include "Blackjack.h"
#include "IAffichageConsole.h"

int main() {
    IAffichageConsole affichageConsole;
    Blackjack blackjack(&affichageConsole);

    blackjack.lancerMenuConsole();
}