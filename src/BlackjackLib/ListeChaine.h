#pragma once

#include <stdexcept>
#include <cstdlib>
#include <ctime>

// Prototype de la classe ListeChaine pour le compilateur
template<typename T>
class ListeChaine;

template<typename T>
class Noeud {
    friend class ListeChaine<T>;

public:
    Noeud() : valeur(T()), addrNoeudSuivant(nullptr) {}

    explicit Noeud(const T &p_valeur) : valeur(p_valeur), addrNoeudSuivant(nullptr) {}

    T getValeur() {
        return valeur; // Ceci pour les tests unitaires
    }

private:
    T valeur;
    Noeud *addrNoeudSuivant;
};

template<typename T>
class ListeChaine {
public:
    ListeChaine() : tete(nullptr), queue(nullptr), m_nombreElement(0) {}

    ListeChaine(const ListeChaine<T> &p_listeACopier) : tete(nullptr), queue(nullptr), m_nombreElement(0) {
        Noeud<T> *temp = p_listeACopier.tete;
        while (temp != nullptr) {
            this->AjouterFin(temp->valeur); // TODO Err possible
            temp = temp->addrNoeudSuivant;
        }
    }

    ListeChaine(ListeChaine<T> &&p_listeADeplacer)

    noexcept {
        this->tete = p_listeADeplacer.tete;
        this->queue = p_listeADeplacer.queue;
        this->m_nombreElement = p_listeADeplacer.m_nombreElement;
    }

    ~ListeChaine() {
        vider();
    };

    void ValiderIndice(const int &p_indice) {
        if (p_indice < 0) {
            throw std::out_of_range("Indice invalide");
        }
    }

    void InsererAuDebut(Noeud<T> * p_nouveauNoeud) {
        p_nouveauNoeud->addrNoeudSuivant = tete;
        tete = p_nouveauNoeud;

        if (!queue) {
            queue = tete;
        }
    }

    void InsererAIndice(Noeud<T> * p_nouveauNoeud, const int & p_indice) {
        Noeud<T> *temp = tete;
        int count = 0;
        while (temp && count < p_indice - 1) {
            temp = temp->addrNoeudSuivant;
            count++;
        }

        if (!temp) {
            delete p_nouveauNoeud;
            throw std::out_of_range("Indice invalide");
        }

        p_nouveauNoeud->addrNoeudSuivant = temp->addrNoeudSuivant;
        temp->addrNoeudSuivant = p_nouveauNoeud;

        if (!p_nouveauNoeud->addrNoeudSuivant) {
            queue = p_nouveauNoeud;
        }
    }

    void Inserer(const T & p_val, const int & p_indice) {
        ValiderIndice(p_indice);

        Noeud<T> *nouveauNoeud = new Noeud<T>(p_val);

        if (p_indice == 0) {
            InsererAuDebut(nouveauNoeud);
        } else {
            InsererAIndice(nouveauNoeud, p_indice);
        }

        m_nombreElement++;
    }

    void AjouterDebut(const T &val) {
        Inserer(val, 0);
    }

    void AjouterFin(const T &val) {
        Noeud<T> *nouveauNoeud = new Noeud<T>(val);

        if (queue) {
            queue->addrNoeudSuivant = nouveauNoeud;
        } else {
            tete = nouveauNoeud;
        }
        queue = nouveauNoeud;
        m_nombreElement++;
    }

    void supprimerDebut() {
        if (!tete) return;

        Noeud<T> *temp = tete;
        tete = tete->addrNoeudSuivant;
        delete temp;

        if (!tete) {
            queue = nullptr;
        }

        m_nombreElement--;
    }

    void supprimerFin() {
        if (!tete) return;

        if (tete == queue) {
            delete tete;
            tete = nullptr;
            queue = nullptr;
            return;
        }

        Noeud<T> *temp = tete;

        while (temp->addrNoeudSuivant != queue) {
            temp->addrNoeudSuivant = temp->addrNoeudSuivant;
        }

        delete queue;
        queue = temp;
        queue->addrNoeudSuivant = nullptr;

        m_nombreElement--;
    }

    void supprimerAIndice(const int &p_indice) {
        ValiderIndice(p_indice);
        if (!tete) return;

        if (p_indice == 0) {
            supprimerDebut();
        } else {
            int count = 0;
            Noeud<T> *temp = tete;
            Noeud<T> *prev = nullptr;

            while (temp && count != p_indice) {
                prev = temp;
                temp = temp->addrNoeudSuivant;
                count++;
            }

            if (!temp) return;

            prev->addrNoeudSuivant = temp->addrNoeudSuivant;

            if (temp == queue) {
                queue = prev;
            }

            delete temp;

            m_nombreElement--;
        }
    }

    void vider() {
        Noeud<T> *temp = tete;

        while (temp) {
            Noeud<T> *suivant = temp->addrNoeudSuivant;
            delete temp;
            temp = suivant;
        }

        tete = nullptr;
        queue = nullptr;
        m_nombreElement = 0;
    }

    T obtenir(const int &p_indice) const {
        Noeud<T> *temp = tete;
        int count = 0;

        while (temp && count != p_indice) {
            temp = temp->addrNoeudSuivant;
            count++;
        }

        if (!temp) {
            throw std::out_of_range("Indice invalide");
        }

        return temp->valeur;
    }

    int nombreElements() const {
        return m_nombreElement;
    }

    ListeChaine &operator=(const ListeChaine &p_listeACopier) {
        if (this == &p_listeACopier) {
            return *this;
        }

        vider();

        Noeud<T> *temp = p_listeACopier.tete;

        while (temp != nullptr) {
            this->AjouterFin(temp->valeur);
            temp = temp->addrNoeudSuivant;
        }

        return *this;
    }

    ListeChaine &operator=(ListeChaine &&p_listeADeplacer)

    noexcept {
        vider();

        this->tete = p_listeADeplacer.tete;
        this->queue = p_listeADeplacer.queue;

        p_listeADeplacer.tete = nullptr;
        p_listeADeplacer.queue = nullptr;

        return *this;
    }

    ListeChaine &operator+=(ListeChaine &&p_listeAAjouter) {
        this->queue->addrNoeudSuivant = p_listeAAjouter.tete;

        p_listeAAjouter.tete = nullptr;
        p_listeAAjouter.queue = nullptr;

        return *this;
    }

    void parcourir(void (*p_fonction)(const T &)) {
        Noeud<T> *temp = tete;

        while (temp != nullptr) {
            p_fonction(temp->valeur);
            temp = temp->addrNoeudSuivant;
        }
    }

    // Buble sort par manque de temps. Source utiliser pour aide : https://www.geeksforgeeks.org/bubble-sort/
    // O(n2)
    // utilisation dans le TP avec la methode comparerCarte de la classe carte.
    void trier(int (*p_fonctionTri)(const T &, const T &)) {
        if (m_nombreElement < 2) return;

        bool enchangee;
        do {
            enchangee = false;
            Noeud<T> *temp = tete;
            Noeud<T> *precedent = nullptr;

            while (temp && temp->addrNoeudSuivant) {
                if (p_fonctionTri(temp->valeur, temp->addrNoeudSuivant->valeur) > 0) {

                    T tempValeur = temp->valeur;
                    temp->valeur = temp->addrNoeudSuivant->valeur;
                    temp->addrNoeudSuivant->valeur = tempValeur;
                    enchangee = true;
                }

                precedent = temp;
                temp = temp->addrNoeudSuivant;
            }
        } while (enchangee);
    }

    void shuffle() {
        std::srand(std::time(nullptr));

        if (m_nombreElement < 2) return;

        //Creation du tableau des adresses memoire des noeud de la liste pour suffle.
        Noeud<T> **tableauNoeuds = new Noeud<T> *[m_nombreElement];
        Noeud<T> *temp = tete;
        int index = 0;

        // Remplir le tableau jusqua nullptr
        while (temp != nullptr) {
            tableauNoeuds[index++] = temp;
            temp = temp->addrNoeudSuivant;
        }

        // Fisher-Yates. Source utiliser pour aide : https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
        for (int i = m_nombreElement - 1; i > 0; i--) {
            int j = std::rand() % (i + 1);
            
            T tempValeur = tableauNoeuds[i]->valeur;
            tableauNoeuds[i]->valeur = tableauNoeuds[j]->valeur;
            tableauNoeuds[j]->valeur = tempValeur;
        }

        delete[] tableauNoeuds;
    }

    Noeud<T> *GetTete() {
        return tete; // ceci pour les tests unitaires
    }

    Noeud<T> *GetQueue() {
        return queue; // ceci pour les tests unitaires
    }

private:
    Noeud<T> *tete, *queue;
    int m_nombreElement{};
};