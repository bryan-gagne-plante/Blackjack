#pragma once

#include "IAffichage.h"
#include "Window/Window.h"
#include "Component/Label.h"
#include "Component/Button.h"
#include "Blackjack.h"

// Un gros probleme qui est survenue est que nous avons fait l'erreur de faire la partie console en premier sans regarder comment le UI interagissait avec ses composants.
// Nous avons donc cree blackjack comme le coeur de notre application avec de l'injection de dependances par IAffichage et du polymorphisme par heritage.
// Cependant, le UI doit avoir sa propre instance de blackjack pour lancer le jeu car l'execution du code bloque a .show()
// De ce fait, nous avons cree un probleme de dependance circulaire qui fait en sorte que nous devrions refaire la majorite de la logique de blackjack (je crois du moins).
// 
// C'est malheureux mais notre manque de preparation a fait en sorte que malgre le code fonctionnel de la classe IAffichageGraphique, il nous est impossible de lancer le jeu...
// J'ignore si du code qui est inexecutable peux valoir quelque chose s'il est fonctionnel mais au cas ou je vais donc laisser les preuves de notre tentative de developpement dans le TP.

class IAffichageGraphique : public IAffichage, public TGUIWSFML::Window::Window {
public:
    IAffichageGraphique();

    ~IAffichageGraphique();

    bool demanderStand() override;

    void afficherMain(const ListeChaine <Carte> &p_main) override;

    void afficherCarteDansLabel(std::string p_cheminCarte, TGUIWSFML::Component::Label *label);

    void afficherScore(int p_score) override;

    void afficherMessage(const std::string &p_message) override;

    void afficherEtatJeuJoueur(Joueur &p_joueur) override;

    void afficherEtatJeuCroupier(Croupier &p_croupier) override;

    //void lancerInterfaceGraphique(Blackjack* p_partieBlackjack) override; // Probleme dependance circulaire

    virtual void componentsInitialization();

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

