// Injection de dependance + Polymorphisme

#include "IAffichageConsole.h"
#include "Joueur.h"
#include "Croupier.h"
#include <iostream>

void IAffichageConsole::afficherCarte(const Carte &carte) {
    std::string symbole = Carte::symboleToString(carte.ObtenirSymbole());
    std::cout << carte.ObtenirValeur() << " de " << symbole << std::endl;
}

void IAffichageConsole::afficherMessage(const std::string &message) {
    std::cout << message << std::endl;
}

void IAffichageConsole::afficherMain(const ListeChaine<Carte> &main) {
    std::cout << "main: " << std::endl;
    for (int i = 0; i < main.nombreElements(); ++i) {
        afficherCarte(main.obtenir(i));
    }
}

void IAffichageConsole::afficherScore(int score) {
    std::cout << "score: " << score << std::endl;
}

void IAffichageConsole::afficherEtatJeuJoueur(Joueur &joueur) {
    afficherMain(joueur.obtenirMain());
    afficherScore(joueur.calculerScore());
}

void IAffichageConsole::afficherEtatJeuCroupier(Croupier &croupier) {
    afficherMain(croupier.obtenirMain());
    afficherScore(croupier.calculerScore());
}

//void IAffichageConsole::lancerInterfaceGraphique(Blackjack* p_partieBlackjack)
//{
//    ;
//}

bool IAffichageConsole::demanderStand() {
    std::string reponse;
    bool stand = false;

    std::cout << "Voulez-vous tirer une carte? (o/n) : ";
    std::cin >> reponse;

    if (reponse == "o" || reponse == "O") {
        stand = false;
    } else if (reponse == "n" || reponse == "N") {
        stand = true;
    } else {
        std::cout << "Veuillez entrer une reponse valide." << std::endl;
        return demanderStand();
    }

    return stand;
}
