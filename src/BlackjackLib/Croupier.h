#pragma once

#include "ListeChaine.h"
#include "Carte.h"

class Croupier {

public:
    Croupier();

    ~Croupier();

    void recevoirCarte(const Carte &p_carte);

    int calculerScore() const;

    bool verifierBlackjack();

    bool verifierBuste() const;

    ListeChaine<Carte> &obtenirMain();

private:
    ListeChaine<Carte> m_main;
};