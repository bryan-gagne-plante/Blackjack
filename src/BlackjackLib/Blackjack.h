#pragma once

#include <iostream>
#include "JeuDeCartes.h"
#include "Joueur.h"
#include "Croupier.h"
#include "IAffichage.h"

enum class Resultat {
    JOUEUR_BUSTE,
    CROUPIER_BUSTE,
    JOUEUR_GAGNE,
    CROUPIER_GAGNE,
    EGALITE,
    JOUEUR_BLACKJACK,
    CROUPIER_BLACKJACK,
    DOUBLE_BLACKJACK
};

class Blackjack {
public:
    Blackjack(IAffichage *p_affichage);

    ~Blackjack();

    void lancerMenuConsole();

    //void lancerInterfaceGraphique();
    
    void jouerMancheConsole(); // Probleme de referencement circulaire avec IAffichageGraphique

private:
    JeuDeCartes m_jeuDeCartes;
    ListeChaine<Carte> m_defausse;
    Croupier m_croupier;
    Joueur m_joueur;
    IAffichage *m_affichage;

    bool initialiserManche();

    void distribuerMainInitiales();

    void jouerTourJoueur();

    void jouerTourCroupier();

    void gererGagnantConsole();

    

    Resultat determinerResultat();

    void repriseCartesParticipants();

    void verifierEtBrasserSiBesoin();
};