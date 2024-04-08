//
// Created by bryan on 2023-08-31.
//

#include "Carte.h"
#include <utility>

Carte::Carte(int p_valeur, Symbole p_symbole, std::string p_cheminImage)
        : m_valeur(p_valeur),
          m_symbole(p_symbole),
          m_cheminImage(std::move(p_cheminImage)) {}

Carte::~Carte() = default;

Symbole Carte::ObtenirSymbole() const {
    return this->m_symbole;
}

int Carte::ObtenirValeur() const {
    return this->m_valeur;
}

std::string Carte::ObtenirCheminImage() const {
    return this->m_cheminImage;
}

std::string Carte::symboleToString(Symbole p_symbole) {
    switch (p_symbole) {
        case Coeur:
            return "Coeur";
        case Carreau:
            return "Carreau";
        case Trefle:
            return "Trefle";
        case Pique:
            return "Pique";
        default:
            return "Inconnu";
    }
}

bool Carte::operator>(const Carte & p_autreCarte) const {
    if (this->ObtenirValeur() == p_autreCarte.ObtenirValeur()) {
        return static_cast<int>(this->ObtenirSymbole()) > static_cast<int>(p_autreCarte.ObtenirSymbole());
    }
    return this->ObtenirValeur() > p_autreCarte.ObtenirValeur();
}

int Carte::comparerCartes(const Carte & p_carte1, const Carte & p_carte2) {
    if (p_carte1 > p_carte2) {
        return 1;
    } else if (p_carte2 > p_carte1) {
        return -1;
    }
    return 0; // En cas d'egalite (pas que le cas sois possible avec des cartes mais pour la bonne pratique...
}
