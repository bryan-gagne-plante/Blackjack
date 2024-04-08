#include <thread>
#include "Blackjack.h"

Blackjack::Blackjack(IAffichage *p_affichage) : m_affichage(p_affichage) {

};

Blackjack::~Blackjack() = default;

void Blackjack::jouerMancheConsole() {
    if (initialiserManche()) {
        m_affichage->afficherMessage("Vous avez mise: 10$");
        m_affichage->afficherMessage("Votre solde est de: " + std::to_string(m_joueur.obtenirSolde()) + "$");
    } else {
        m_affichage->afficherMessage("Vous n'avez plus d'argent. Vous ne pouvez plus jouer.");
        return;
    }

    distribuerMainInitiales();

    m_affichage->afficherMessage("DESTRIBUTION DES CARTES ... \n");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    m_affichage->afficherMessage("Le croupier recoit une carte.");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    m_affichage->afficherMessage("Le croupier distribue une carte au joueur.");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    m_affichage->afficherMessage("Le croupier recoit une carte.");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    m_affichage->afficherMessage("Le croupier distribue une carte au joueur. \n");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    m_affichage->afficherMessage("Etat Jeu Croupier");
    m_affichage->afficherEtatJeuCroupier(m_croupier);
    m_affichage->afficherMessage("Carte cachee \n");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    m_affichage->afficherMessage("Etat Jeu Joueur");
    m_affichage->afficherEtatJeuJoueur(m_joueur);

    // Si le joueur a un blackjack initial, la manche s'arrête
    if (!m_joueur.verifierBlackjack()) {
        jouerTourJoueur();

        // Si le joueur a déjà perdu, la manche s'arrête
        if (!m_joueur.verifierBuste()) {
            jouerTourCroupier();
        }
    }

    gererGagnantConsole();
    repriseCartesParticipants();
}

void Blackjack::lancerMenuConsole() {
    char choix;
    do {
        m_affichage->afficherMessage("Voulez-vous jouer une nouvelle manche? (o/n): ");
        std::cin >> choix;

        if (choix == 'o' || choix == 'O') {
            jouerMancheConsole();
        } else if (choix == 'n' || choix == 'N') {
            m_affichage->afficherMessage("Merci d'avoir joue. A la prochaine!\n");
            break;
        } else {
            m_affichage->afficherMessage("Choix invalide. Essayez encore.\n");
        }

    } while (true);
}

//void Blackjack::lancerInterfaceGraphique() {
//    m_affichage->lancerInterfaceGraphique(this);
//}

bool Blackjack::initialiserManche() {
    bool reussi = true;

    if (m_jeuDeCartes.nombreCartesRestantes() == 52) {
        m_jeuDeCartes.BrasserJeuDeCarte();
    }

    if (m_joueur.verifierSolde()) {
        m_joueur.placerMiseInitial();
    } else {
        reussi = false;
    }

    return reussi;
}

void Blackjack::distribuerMainInitiales() {
    for (int i = 0; i < 2; ++i) {
        verifierEtBrasserSiBesoin();
        m_joueur.recevoirCarte(m_jeuDeCartes.DistribuerUneCarte());
    }

    m_joueur.obtenirMain().trier(Carte::comparerCartes);

    verifierEtBrasserSiBesoin();
    m_croupier.recevoirCarte(m_jeuDeCartes.DistribuerUneCarte());
}

void Blackjack::verifierEtBrasserSiBesoin() {
    if (m_jeuDeCartes.nombreCartesRestantes() == 0) {
        m_jeuDeCartes.AjouterDefausse(m_defausse);
        m_defausse.vider();
        m_jeuDeCartes.BrasserJeuDeCarte();
    }
}

void Blackjack::jouerTourJoueur() {
    bool jStand = false;
    bool jBuste = false;

    while (!jStand && !jBuste) {

        jStand = m_affichage->demanderStand();

        // Si le joueur ne veut pas "stand", il reçoit une nouvelle carte
        if (!jStand) {
            m_affichage->afficherMessage("\nVous recevez une nouvelle carte.");

            // Pause pour l'effet dramatique
            std::this_thread::sleep_for(std::chrono::seconds(1));

            verifierEtBrasserSiBesoin();
            Carte carteJoueur = m_jeuDeCartes.DistribuerUneCarte();
            m_joueur.recevoirCarte(carteJoueur);
            m_joueur.obtenirMain().trier(Carte::comparerCartes);
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));

        m_affichage->afficherMessage("\nEtat Jeu Joueur");
        m_affichage->afficherEtatJeuJoueur(m_joueur);

        if (m_joueur.calculerScore() >= 21) {
            jBuste = true;
            jStand = true;
        }
    }
}

void Blackjack::jouerTourCroupier() {
    // Ajout de la deuxieme cartes ici pour les besoin de l'affichage par injection de dependance.
    verifierEtBrasserSiBesoin();
    m_croupier.recevoirCarte(m_jeuDeCartes.DistribuerUneCarte());
    m_croupier.obtenirMain().trier(Carte::comparerCartes);

    // Afficher le score du croupier pour le début de son tour
    m_affichage->afficherMessage("\nEtat Jeu Croupier");
    m_affichage->afficherEtatJeuCroupier(m_croupier);

    while (m_croupier.calculerScore() < 17) {
        m_affichage->afficherMessage("\nLe croupier pioche une nouvelle carte.");
        std::this_thread::sleep_for(std::chrono::seconds(1));

        verifierEtBrasserSiBesoin();
        Carte carteCroupier = m_jeuDeCartes.DistribuerUneCarte();
        m_croupier.recevoirCarte(carteCroupier);
        m_croupier.obtenirMain().trier(Carte::comparerCartes);
        m_affichage->afficherMessage("\nEtat Jeu Croupier");
        m_affichage->afficherEtatJeuCroupier(m_croupier);
    }
}

Resultat Blackjack::determinerResultat() {
    Resultat resultat;
    int scoreJoueur = m_joueur.calculerScore();
    int scoreCroupier = m_croupier.calculerScore();

    if (m_joueur.verifierBlackjack() && m_croupier.verifierBlackjack()) {
        resultat = Resultat::DOUBLE_BLACKJACK;
    } else if (m_joueur.verifierBlackjack()) {
        resultat = Resultat::JOUEUR_BLACKJACK;
    } else if (m_croupier.verifierBlackjack()) {
        resultat = Resultat::CROUPIER_BLACKJACK;
    } else if (m_joueur.verifierBuste()) {
        resultat = Resultat::JOUEUR_BUSTE;
    } else if (m_croupier.verifierBuste()) {
        resultat = Resultat::CROUPIER_BUSTE;
    } else if (scoreJoueur > scoreCroupier) {
        resultat = Resultat::JOUEUR_GAGNE;
    } else if (scoreCroupier > scoreJoueur) {
        resultat = Resultat::CROUPIER_GAGNE;
    } else {
        resultat = Resultat::EGALITE;
    }

    return resultat;
}

void Blackjack::gererGagnantConsole() {
    Resultat resultat = determinerResultat();

    switch (resultat) {
        case Resultat::JOUEUR_BUSTE:
            m_affichage->afficherMessage("Vous avez depasse 21. Le croupier a gagne !");
            m_joueur.perdreMise();
            break;

        case Resultat::CROUPIER_BUSTE:
            m_affichage->afficherMessage("Le croupier a depasse 21. Vous avez gagne !");
            m_joueur.gagnerMise();
            break;

        case Resultat::JOUEUR_GAGNE:
            m_affichage->afficherMessage("Vous avez gagne !");
            m_joueur.gagnerMise();
            break;

        case Resultat::CROUPIER_GAGNE:
            m_affichage->afficherMessage("Le croupier a gagne !");
            m_joueur.perdreMise();
            break;

        case Resultat::EGALITE:
            m_affichage->afficherMessage("Egalite !");
            m_joueur.gagner(1); // Récupérer la mise
            break;

        case Resultat::JOUEUR_BLACKJACK:
            m_affichage->afficherMessage("Vous avez un blackjack !");
            m_joueur.gagneMiseBlackjack();
            break;

        case Resultat::CROUPIER_BLACKJACK:
            m_affichage->afficherMessage("Le croupier a un blackjack !");
            m_joueur.perdreMise();
            break;

        case Resultat::DOUBLE_BLACKJACK:
            m_affichage->afficherMessage("Egalite! Vous avez tous les deux un blackjack.");
            m_joueur.gagner(1); // Récupérer la mise
            break;
    }

    m_affichage->afficherMessage("\nVotre solde est de: " + std::to_string(m_joueur.obtenirSolde()) + "$");
}

void Blackjack::repriseCartesParticipants() {
    for (int i = 0; i < m_joueur.obtenirMain().nombreElements(); ++i) {
        m_defausse.AjouterDebut(m_joueur.obtenirMain().obtenir(i));
    }

    for (int i = 0; i < m_croupier.obtenirMain().nombreElements(); ++i) {
        m_defausse.AjouterDebut(m_croupier.obtenirMain().obtenir(i));
    }

    m_joueur.obtenirMain().vider();
    m_croupier.obtenirMain().vider();
}

