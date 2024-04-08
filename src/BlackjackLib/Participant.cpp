#include "Participant.h"
#include <iostream>

template<class type>
int *Participant<type>::getCarte() {
    return this->m_carte;
}

template<class type>
int Participant<type>::getNbCarte() {
    return this->m_nbCartes;
}

template<class type>
int Participant<type>::getCapaciteCarte() {
    return this->m_capaciteMaxCartes;
}

template<class type>
int Participant<type>::getProchaineCarte() {
    return this->m_prochaineCarte;
}

template<class type>
Participant<type>::Participant() {
    m_nbCartes = 0;
    m_capaciteMaxCartes = 10;
    m_carte = new int[m_capaciteMaxCartes];
}

template<class type>
Participant<type>::~Participant() {

    delete[] m_carte;
}

template<class type>
Participant<type>::Participant(const Participant<type> &p_objetACopier) {
    m_nbCartes = p_objetACopier.m_nbCartes;
    m_capaciteMaxCartes = p_objetACopier.m_capaciteMaxCartes;
    m_carte = new int[m_capaciteMaxCartes];
    for (int i = 0; i < m_nbCartes; ++i) {
        m_carte[i] = p_objetACopier.m_carte[i];
    }
}

template<class type>
Participant<type>::Participant(const Participant<type> &&p_objetADeplacer) {

    m_nbCartes = p_objetADeplacer.m_nbCartes;
    m_capaciteMaxCartes = p_objetADeplacer.m_capaciteMaxCartes;
    m_carte = p_objetADeplacer.carte;

    p_objetADeplacer.m_nbCartes = 0;
    p_objetADeplacer.m_capaciteMaxCartes = 0;
    p_objetADeplacer.m_carte = nullptr;
}

template<class type>
bool Participant<type>::estJoueur() const {
    return false;
}
