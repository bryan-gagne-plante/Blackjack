#pragma once

#include "Window/Window.h"
#include "Component/Label.h"
#include "Component/Button.h"
#include <IAffichage.h>

class GestionFenetre : public TGUIWSFML::Window::Window {
public:
    GestionFenetre();

    ~GestionFenetre();

    virtual void componentsInitialization();

    void afficherScore(int p_score);

    void afficherMain(const ListeChaine <Carte> &main);

    void afficherCarteDansLabel(std::string p_cheminCarte, TGUIWSFML::Component::Label *label);

    void afficherMessage(const std::string &message);

    bool gererHitStand();

    void hit();

    void stand();

    void nouvellePartie();

private:
    bool aClick = false;
    bool hitOuStand = false;

    TGUIWSFML::Component::Label *m_solde;
    TGUIWSFML::Component::Label *m_mise;
    TGUIWSFML::Component::Label *m_message;
    TGUIWSFML::Component::Label *m_score;

    TGUIWSFML::Component::Button *m_hit;
    TGUIWSFML::Component::Button *m_stand;

    TGUIWSFML::Component::Button *m_nouvellePartie;

    TGUIWSFML::Component::Label *m_imageCarte1;
    TGUIWSFML::Component::Label *m_imageCarte2;
    TGUIWSFML::Component::Label *m_imageCarte3;
    TGUIWSFML::Component::Label *m_imageCarte4;
    TGUIWSFML::Component::Label *m_imageCarte5;
    TGUIWSFML::Component::Label *m_imageCarte6;
    TGUIWSFML::Component::Label *m_imageCarte7;
};

