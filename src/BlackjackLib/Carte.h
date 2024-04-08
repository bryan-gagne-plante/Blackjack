#pragma once

#include <string>

enum Symbole {
    Coeur,
    Carreau,
    Trefle,
    Pique
};

class Carte {
public:
    Carte(int p_valeur, Symbole p_symbole, std::string p_cheminImage);

    ~Carte();

    Symbole ObtenirSymbole() const;

    static std::string symboleToString(Symbole p_symbole);

    int ObtenirValeur() const;

    std::string ObtenirCheminImage() const;

    bool operator>(const Carte & p_autreCarte) const;

    static int comparerCartes(const Carte & p_carte1, const Carte & p_carte2);

private:
    int m_valeur;
    Symbole m_symbole;
    std::string m_cheminImage;
};