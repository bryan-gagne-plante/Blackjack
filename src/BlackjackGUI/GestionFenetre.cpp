#include "Event/MouseEvent.h"

#include "GestionFenetre.h"
#include <iostream>
#include <array>
#include <thread>
#include "Blackjack.h"

GestionFenetre::GestionFenetre()
        : Window(1280, 720, "Cheap Blackjack"),
          m_solde(nullptr),
          m_mise(nullptr),
          m_message(nullptr),
          m_score(nullptr),
          m_hit(nullptr),
          m_stand(nullptr),
          m_nouvellePartie(nullptr),
          m_imageCarte1(nullptr),
          m_imageCarte2(nullptr),
          m_imageCarte3(nullptr),
          m_imageCarte4(nullptr),
          m_imageCarte5(nullptr),
          m_imageCarte6(nullptr),
          m_imageCarte7(nullptr) {
    ;
}

GestionFenetre::~GestionFenetre() {
    this->m_components.clear();

    delete this->m_solde;
    this->m_solde = nullptr;

    delete this->m_mise;
    this->m_mise = nullptr;

    delete this->m_message;
    this->m_message = nullptr;

    delete this->m_score;
    this->m_score = nullptr;

    delete this->m_hit;
    this->m_hit = nullptr;

    delete this->m_stand;
    this->m_stand = nullptr;

    delete this->m_nouvellePartie;
    this->m_nouvellePartie = nullptr;

    delete this->m_imageCarte1;
    this->m_imageCarte1 = nullptr;

    delete this->m_imageCarte2;
    this->m_imageCarte2 = nullptr;

    delete this->m_imageCarte3;
    this->m_imageCarte3 = nullptr;

    delete this->m_imageCarte4;
    this->m_imageCarte4 = nullptr;

    delete this->m_imageCarte5;
    this->m_imageCarte5 = nullptr;

    delete this->m_imageCarte6;
    this->m_imageCarte6 = nullptr;

    delete this->m_imageCarte7;
    this->m_imageCarte7 = nullptr;
}

void GestionFenetre::componentsInitialization() {
    this->m_solde = new TGUIWSFML::Component::Label();
    this->m_solde->text("Solde");
    this->m_solde->top(65);
    this->m_solde->left(1);
    this->m_solde->cornerRadius(10);
    this->addComponent(this->m_solde);

    this->m_mise = new TGUIWSFML::Component::Label();
    this->m_mise->text("Mise");
    this->m_mise->top(165);
    this->m_mise->left(1);
    this->m_mise->cornerRadius(10);
    this->addComponent(this->m_mise);

    this->m_message = new TGUIWSFML::Component::Label();
    this->m_message->text("Message");
    this->m_message->top(265);
    this->m_message->left(1);
    this->m_message->cornerRadius(10);
    this->addComponent(this->m_message);

    this->m_score = new TGUIWSFML::Component::Label();
    this->m_score->text("Message");
    this->m_score->top(365);
    this->m_score->left(1);
    this->m_score->cornerRadius(10);
    this->addComponent(this->m_score);

    this->m_hit = new TGUIWSFML::Component::Button(550, 400, 50, 15, "Hit");
    this->addComponent(this->m_hit);
    this->m_hit->addMouseClickHandler([&](const TGUIWSFML::Event::MouseEvent &me) { this->hit(); });

    this->m_stand = new TGUIWSFML::Component::Button(650, 400, 50, 15, "Stand");
    this->addComponent(this->m_stand);
    this->m_hit->addMouseClickHandler([&](const TGUIWSFML::Event::MouseEvent &me) { this->stand(); });

    this->m_nouvellePartie = new TGUIWSFML::Component::Button(650, 400, 50, 15, "Stand");
    this->addComponent(this->m_nouvellePartie);
    this->m_nouvellePartie->addMouseClickHandler(
            [&](const TGUIWSFML::Event::MouseEvent &me) { this->nouvellePartie(); });

    this->m_imageCarte1 = new TGUIWSFML::Component::Label(350, 25, 234, 333, "");
    this->m_imageCarte1->backgroundTexture(texture("svg_playing_cards/backs/png_96_dpi/astronaut"));
    this->addComponent(this->m_imageCarte1);

    this->m_imageCarte2 = new TGUIWSFML::Component::Label(400, 25, 234, 333, "");
    this->m_imageCarte2->backgroundTexture(texture("svg_playing_cards/backs/png_96_dpi/astronaut"));
    this->addComponent(this->m_imageCarte2);

    this->m_imageCarte3 = new TGUIWSFML::Component::Label(450, 25, 234, 333, "");
    this->m_imageCarte3->backgroundTexture(texture("svg_playing_cards/backs/png_96_dpi/astronaut"));
    this->addComponent(this->m_imageCarte3);

    this->m_imageCarte4 = new TGUIWSFML::Component::Label(500, 25, 234, 333, "");
    this->m_imageCarte4->backgroundTexture(texture("svg_playing_cards/backs/png_96_dpi/astronaut"));
    this->addComponent(this->m_imageCarte4);

    this->m_imageCarte5 = new TGUIWSFML::Component::Label(550, 25, 234, 333, "");
    this->m_imageCarte5->backgroundTexture(texture("svg_playing_cards/backs/png_96_dpi/astronaut"));
    this->addComponent(this->m_imageCarte5);

    this->m_imageCarte6 = new TGUIWSFML::Component::Label(600, 25, 234, 333, "");
    this->m_imageCarte6->backgroundTexture(texture("svg_playing_cards/backs/png_96_dpi/astronaut"));
    this->addComponent(this->m_imageCarte6);

    this->m_imageCarte7 = new TGUIWSFML::Component::Label(650, 25, 234, 333, "");
    this->m_imageCarte7->backgroundTexture(texture("svg_playing_cards/backs/png_96_dpi/astronaut"));
    this->addComponent(this->m_imageCarte7);
}

void GestionFenetre::afficherScore(int p_score) {
    this->m_score->text(std::to_string(p_score));
}

void GestionFenetre::afficherMain(const ListeChaine <Carte> &main) {
    int nbCarteMax = 7;
    int nbCarteAfficher = 0;

    std::array < TGUIWSFML::Component::Label * ,
            7 > labels = {m_imageCarte1, m_imageCarte2, m_imageCarte3, m_imageCarte4, m_imageCarte5, m_imageCarte6,
                          m_imageCarte7};

    int nombreDeCartesDansLaMain = main.nombreElements();

    for (int i = 0; i < nombreDeCartesDansLaMain; ++i) {
        if (nbCarteAfficher < nbCarteMax) {
            Carte carte = main.obtenir(i);
            std::string cheminCarte = carte.ObtenirCheminImage(); // Supposition bas�e sur votre exemple pr�c�dent
            afficherCarteDansLabel(cheminCarte, labels[nbCarteAfficher]);
            nbCarteAfficher++;
        }
    }
}

void GestionFenetre::afficherCarteDansLabel(std::string p_cheminCarte, TGUIWSFML::Component::Label *label) {
    std::string chemin = "svg_playing_cards/fronts/png_96_dpi/";
    chemin += p_cheminCarte;

    if (!texture(chemin)) {
        std::cout << "Erreur de chargement de la texture" << std::endl;
    } else {
        label->backgroundTexture(texture(chemin));
    }
}

void GestionFenetre::afficherMessage(const std::string &message) {
    this->m_message->text(message);
}

bool GestionFenetre::gererHitStand() {
    while (!this->aClick) {
        // Mon code n'a malheureusement pas ete penser pour utiliser un patern d'observer
        // donc je me vois dans l'obligation d'en "coder" un ici.
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    this->aClick = false;
    return this->hitOuStand;
}

void GestionFenetre::hit() {
    this->hitOuStand = true;
    this->aClick = true;

}

void GestionFenetre::stand() {
    this->hitOuStand = false;
    this->aClick = true;
}

void GestionFenetre::nouvellePartie() {

}
