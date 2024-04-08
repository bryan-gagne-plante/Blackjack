#include "Croupier.h"

Croupier::Croupier() = default;

Croupier::~Croupier() = default;

void Croupier::recevoirCarte(const Carte &p_carte) {
    m_main.AjouterDebut(p_carte);
}

int Croupier::calculerScore() const {
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

bool Croupier::verifierBlackjack() {
    return m_main.nombreElements() == 2 && calculerScore() == 21;
}

bool Croupier::verifierBuste() const {
    return calculerScore() > 21;
}

ListeChaine<Carte> &Croupier::obtenirMain() {
    return this->m_main;
}