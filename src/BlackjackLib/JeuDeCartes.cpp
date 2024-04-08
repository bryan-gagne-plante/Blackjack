#include "JeuDeCartes.h"

JeuDeCartes::JeuDeCartes() {
    // Creer un jeu de 52 cartes
    for (int i = Coeur; i <= Pique; ++i) {
        for (int j = 1; j <= 13; ++j) {
            std::string cheminCarte = "";

            //TODO Isoler switch dans leur propres fonctions
            switch (i) {
                case 0:
                    cheminCarte += "hearts_";
                    break;
                case 1:
                    cheminCarte += "diamonds_";
                    break;
                case 2:
                    cheminCarte += "clubs_";
                    break;
                case 3:
                    cheminCarte += "spades_";
                    break;

                default:
                    cheminCarte += "err_";
                    break;
            }

            switch (j) {
                case 1:
                    cheminCarte += "ace";
                    break;
                case 11:
                    cheminCarte += "jack";
                    break;
                case 12:
                    cheminCarte += "queen";
                    break;
                case 13:
                    cheminCarte += "king";
                    break;
                default:
                    cheminCarte += std::to_string(j);
                    break;
            }

            Carte carte(j, static_cast<Symbole>(i), cheminCarte);
            m_jeuCartes.AjouterDebut(carte);
        }
    }
}

JeuDeCartes::~JeuDeCartes() = default;

void JeuDeCartes::BrasserJeuDeCarte() {
    m_jeuCartes.shuffle();
}

Carte JeuDeCartes::DistribuerUneCarte() {
    Carte carteDuDessus = m_jeuCartes.obtenir(0);
    m_jeuCartes.supprimerDebut();
    return carteDuDessus;
}

bool JeuDeCartes::JeuCarteVide() {
    return m_jeuCartes.nombreElements() == 0;
}

int JeuDeCartes::nombreCartesRestantes() {
    return m_jeuCartes.nombreElements();
}

void JeuDeCartes::AjouterDefausse(const ListeChaine<Carte> & p_chaine) {
    int nombreElements = p_chaine.nombreElements();

    for (int i = 0; i < nombreElements; ++i) {
        Carte carte = p_chaine.obtenir(i);
        m_jeuCartes.AjouterFin(carte);
    }
}



