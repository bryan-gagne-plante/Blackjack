#pragma once

#include "IAffichage.h"
#include "Carte.h"
#include "ListeChaine.h"
#include "Joueur.h"
#include "Croupier.h"
#include "Blackjack.h"

class IAffichageConsole : public IAffichage {
public:
    bool demanderStand() override;

    void afficherCarte(const Carte &carte);

    void afficherMain(const ListeChaine<Carte> &main);

    void afficherScore(int score);

    void afficherMessage(const std::string &message) override;

    void afficherEtatJeuJoueur(Joueur &joueur) override;

    void afficherEtatJeuCroupier(Croupier &croupier) override;

    //void lancerInterfaceGraphique(Blackjack* p_partieBlackjack) override;
};
