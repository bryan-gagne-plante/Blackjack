#pragma once

#include "Carte.h"
#include "Joueur.h"
#include "Croupier.h"
//#include "Blackjack.h" // PROB REF CIRCULAIRE

class IAffichage {
public:
    virtual bool demanderStand() = 0;

    virtual void afficherMain(const ListeChaine<Carte>& p_main) = 0;

    virtual void afficherScore(int p_score) = 0;

    virtual void afficherMessage(const std::string & p_message) = 0;

    virtual void afficherEtatJeuJoueur(Joueur & p_joueur) = 0;

    virtual void afficherEtatJeuCroupier(Croupier & p_croupier) = 0;

    //virtual void lancerInterfaceGraphique(Blackjack *p_partieBlackjack) = 0;
};
