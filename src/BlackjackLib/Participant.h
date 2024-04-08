#pragma once

template<class type>
class Participant {

public:
    Participant();

    virtual ~Participant();

    Participant(const Participant<type> &p_objetACopier);

    Participant(const Participant<type> &&p_objetADeplacer);

    virtual void
    InitialiserTasDeCartes() = 0; // ici j'initialise le tas de cartes pour pourvoir en recevoir des cartes et tout
    virtual void recevoirCarte(int p_carte) = 0; //ici c'est une carte que �a prend
    virtual int calculerScore() const = 0;

    virtual bool verifierBlackjack() = 0;

    virtual bool aBuste() = 0;

    virtual void viderMain() = 0;

    virtual int *getCarte();

    virtual int getNbCarte();

    virtual int getCapaciteCarte();

    virtual int getProchaineCarte();

    virtual bool estJoueur() const;

private:
    int *m_carte;
    int m_nbCartes;
    int m_capaciteMaxCartes;
    int m_prochaineCarte;
};

