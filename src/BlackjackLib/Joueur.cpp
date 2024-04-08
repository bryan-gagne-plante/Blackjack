#include "Joueur.h"
#include <iostream>


Joueur::Joueur() : m_solde(100), m_miseActuelle(0) {}

Joueur::~Joueur() = default;

void Joueur::resetMise() {
    this->m_miseActuelle = 0;
}

void Joueur::placerMiseInitial() {
    this->m_miseActuelle += 10; // TODO SWITCH HARDCODED VALUE TO CONSTANT
    this->m_solde -= 10;
}

void Joueur::gagner(int p_multiplicateur) {
    this->m_solde += this->m_miseActuelle * p_multiplicateur;

    resetMise();
}

void Joueur::gagnerMise() {
    gagner(2);
}

void Joueur::gagneMiseBlackjack() {
    gagner(4);
}

void Joueur::perdreMise() {
    resetMise();
}

bool Joueur::verifierSolde() const {
    bool ALesMoyens = false;
    if (this->m_solde >= 10) {
        ALesMoyens = true;
    }
    return ALesMoyens;
}

int Joueur::obtenirSolde() const {
    return this->m_solde;
}

void Joueur::recevoirCarte(const Carte &p_carte) {
    if (m_main.nombreElements() < m_nbCarteMax) {
        m_main.AjouterDebut(p_carte);
    }
}

int Joueur::calculerScore() const {
    int score = 0;
    int nbAs = 0;

    for (int i = 0; i < m_main.nombreElements(); ++i) {
        int valeurCarte = m_main.obtenir(i).ObtenirValeur();

        valeurCarte = std::min(valeurCarte, 10);

        score += valeurCarte;

        if (valeurCarte == 1) {
            nbAs++;
        }
    }

    while (nbAs > 0 && score + 10 <= 21) {
        score += 10;
        --nbAs;
    }
    return score;
}

bool Joueur::verifierBlackjack() {
    return m_main.nombreElements() == 2 && calculerScore() == 21;
}

bool Joueur::verifierBuste() const {
    return calculerScore() > 21;
}

ListeChaine<Carte> &Joueur::obtenirMain() {
    return this->m_main;
}