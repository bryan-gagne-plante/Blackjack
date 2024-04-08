//
// Created by bryan on 2023-08-31.
//

#pragma once

#include "ListeChaine.h"
#include "Carte.h"

class JeuDeCartes {
public:
    JeuDeCartes();

    ~JeuDeCartes();

    void BrasserJeuDeCarte();

    Carte DistribuerUneCarte();

    int nombreCartesRestantes();

    bool JeuCarteVide();

    void AjouterDefausse(const ListeChaine<Carte> & p_chaine);

private:
    ListeChaine<Carte> m_jeuCartes;


};
