#pragma once

#include "ListeChaine.h"
#include "Carte.h"

class Joueur {

public:
    Joueur();

    ~Joueur();

    void resetMise();

    void placerMiseInitial();

    void gagner(int p_multiplicateur);

    void gagnerMise();

    void gagneMiseBlackjack();

    void perdreMise();

    int obtenirSolde() const;

    bool verifierSolde() const;

    void recevoirCarte(const Carte & p_carte);

    int calculerScore() const;

    bool verifierBlackjack();

    bool verifierBuste() const;

    ListeChaine<Carte> &obtenirMain();

private:
    ListeChaine<Carte> m_main;
    int m_solde;
    int m_miseActuelle;
    const int m_nbCarteMax = 7;


};