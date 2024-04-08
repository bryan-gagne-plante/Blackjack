#include "CppUnitTest.h"

#include "ListeChaine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackjackLibTests {

	TEST_CLASS(ListeChaineeTests) {
		public:
			TEST_METHOD(InsererAuDebut_VerifierSiCaInsereAvecListeVide_True) {

				//Arranger
				ListeChaine<int> listeChaine;
				Noeud<int>* nouveauNoeud = new Noeud<int>(5);

				//Agir
				listeChaine.InsererAuDebut(nouveauNoeud);

				//Auditer
				Assert::IsTrue(nouveauNoeud->getValeur() == listeChaine.GetTete()->getValeur());
				Assert::IsTrue(nouveauNoeud->getValeur() == listeChaine.GetQueue()->getValeur());
			}
			TEST_METHOD(InsererAuDebut_VerifierSiCaInsereAvecListeNonVide_True) {

				//Arranger
				ListeChaine<int> listeChaine;
				Noeud<int>* nouveauNoeud1 = new Noeud<int>(5);
				Noeud<int>* nouveauNoeud2 = new Noeud<int>(5);
				listeChaine.InsererAuDebut(nouveauNoeud1);

				//Agir
				listeChaine.InsererAuDebut(nouveauNoeud2);

				//Auditer
				Assert::IsTrue(nouveauNoeud2->getValeur() == listeChaine.GetTete()->getValeur());
				Assert::IsTrue(nouveauNoeud1->getValeur() == listeChaine.GetQueue()->getValeur());
			}
			TEST_METHOD(Inserer_InsertionAIndiceOQuandVide_True) {

				//Arranger
				ListeChaine<int> listeChaine;
				int valeurAInserer = 2;

				//Agir
				listeChaine.Inserer(valeurAInserer, 0);
				int resultatAttendueTete = listeChaine.GetTete()->getValeur();
				int resultatAttendueQueue = listeChaine.GetTete()->getValeur();

				//Auditer
				Assert::IsTrue(valeurAInserer == resultatAttendueTete);
				Assert::IsTrue(valeurAInserer == resultatAttendueQueue);
			}
			TEST_METHOD(Inserer_InsertionAIndiceXQuandNonVide_True) {

				//Arranger
				ListeChaine<int> listeChaine;
				int valeurAInserer1 = 2;
				int valeurAInserer2 = 3;
				listeChaine.Inserer(valeurAInserer1, 0);

				//Agir
				listeChaine.Inserer(valeurAInserer2, 0);
				int resultatAttendueTete = listeChaine.GetTete()->getValeur();
				int resultatAttendueQueue = listeChaine.GetQueue()->getValeur();

				//Auditer
				Assert::IsTrue(valeurAInserer2 == resultatAttendueTete);
				Assert::IsTrue(valeurAInserer1 == resultatAttendueQueue);
			}
			TEST_METHOD(Inserer_InsertionAIndiceXQuandIndiceInvalide_outOfRange) {

				//Arranger
				ListeChaine<int> listeChaine;
				int valeurAInserer = 2;
				int indice = -2;

				//Agir Auditer
				Assert::ExpectException<std::out_of_range>([&] {
					listeChaine.Inserer(valeurAInserer, indice);
					});
			}

			TEST_METHOD(AjouterFin_VerifierSiCaAjouteAvecListeVide_True) {

				//Arranger
				ListeChaine<int> listeChaine;
				int valeurAAjoutee = 2;

				//Agir
				listeChaine.AjouterFin(valeurAAjoutee);

				//Auditer
				Assert::IsTrue(1 == listeChaine.nombreElements());
				Assert::IsTrue(valeurAAjoutee == listeChaine.GetTete()->getValeur());
				Assert::IsTrue(valeurAAjoutee == listeChaine.GetQueue()->getValeur());
			}

			TEST_METHOD(AjouterFin_VerifierSiCaAjouteAvecListeNonVide_True) {

				//Arranger
				ListeChaine<int> listeChaine;
				int valeurAAjoutee1 = 5;
				int valeurAAjoutee2 = 54;
				listeChaine.AjouterFin(valeurAAjoutee1);

				//Agir
				listeChaine.AjouterFin(valeurAAjoutee2);

				//Auditer
				Assert::IsTrue(2 == listeChaine.nombreElements());
				Assert::IsTrue(valeurAAjoutee1 == listeChaine.GetTete()->getValeur());
				Assert::IsTrue(valeurAAjoutee2 == listeChaine.GetQueue()->getValeur());
			}

			TEST_METHOD(supprimerDebut_VerifierSiCaSupprimeLePremierElement_True) {

				//Arranger
				ListeChaine<int> listeChaine;
				int valeurAAjoutee1 = 5;
				int valeurAAjoutee2 = 54;
				listeChaine.AjouterFin(valeurAAjoutee1);

				//Agir
				listeChaine.AjouterFin(valeurAAjoutee2);
				listeChaine.supprimerDebut();

				//Auditer
				Assert::IsTrue(1 == listeChaine.nombreElements());
				Assert::IsTrue(valeurAAjoutee2 == listeChaine.GetTete()->getValeur());
				Assert::IsTrue(valeurAAjoutee2 == listeChaine.GetQueue()->getValeur());
			}

			TEST_METHOD(supprimerDebut_SupprimerPourUneListeVide_RienFire) {

				//Arranger
				ListeChaine<int> listeChaine;

				//Agir
				listeChaine.supprimerDebut();

				//Auditer
				Assert::IsTrue(0 == listeChaine.nombreElements());
			}

			TEST_METHOD(supprimerFin_SupprimerPourUneListeVide_RienFire) {

				//Arranger
				ListeChaine<int> listeChaine;

				//Agir
				listeChaine.supprimerFin();

				//Auditer
				Assert::IsTrue(0 == listeChaine.nombreElements());
			}

			TEST_METHOD(supprimerFin_VerifierSiCaSupprimeLeDernierElement_True) {

				//Arranger
				ListeChaine<int> listeChaine;
				int valeurAAjoutee1 = 5;
				int valeurAAjoutee2 = 54;
				listeChaine.AjouterDebut(valeurAAjoutee1);

				//Agir
				listeChaine.AjouterDebut(valeurAAjoutee2);
				listeChaine.supprimerFin();

				//Auditer
				Assert::IsTrue(1 == listeChaine.nombreElements());
				Assert::IsTrue(valeurAAjoutee2 == listeChaine.GetTete()->getValeur());
				Assert::IsTrue(valeurAAjoutee2 == listeChaine.GetQueue()->getValeur());
			}

			TEST_METHOD(supprimerAIndice_SuppressionAIndiceOQuandNonVide_True) {

				//Arranger
				ListeChaine<int> listeChaine;
				listeChaine.AjouterDebut(1);

				//Agir
				listeChaine.supprimerAIndice(0);

				//Auditer
				Assert::IsTrue(0 == listeChaine.nombreElements());
			}
			
			TEST_METHOD(supprimerAIndice_SuppressionAIndiceXQuandNonVide_True) {

				//Arranger
				ListeChaine<int> listeChaine;
				int valeurAAjoutee1 = 5;
				listeChaine.AjouterDebut(valeurAAjoutee1);
				listeChaine.AjouterDebut(valeurAAjoutee1 + 1);
				listeChaine.AjouterDebut(valeurAAjoutee1 + 2);
				//Agir
				listeChaine.supprimerAIndice(1);

				//Auditer
				Assert::IsTrue(2 == listeChaine.nombreElements());
				Assert::IsTrue(valeurAAjoutee1 + 2 == listeChaine.GetTete()->getValeur());
				Assert::IsTrue(valeurAAjoutee1 == listeChaine.GetQueue()->getValeur());
			}
			
			TEST_METHOD(supprimerAIndice_SuppressionAIndiceXQuandIndiceInvaide_OutOfRange) {

				//Arranger
				ListeChaine<int> listeChaine;
				int valeur1 = 2;
				int indice = -2;
				listeChaine.AjouterDebut(valeur1);

				//Agir Auditer
				Assert::ExpectException<std::out_of_range>([&] {
					listeChaine.supprimerAIndice(indice);
					});
			}

			TEST_METHOD(vider_ViderQuandListeDejaVide_rien) {

				//Arranger
				ListeChaine<int> listeChaine;

				// Auditer
				listeChaine.vider();

				//Agir 
				Assert::IsTrue(0 == listeChaine.nombreElements());
			}

			TEST_METHOD(vider_ViderQuandListeNonVide_rien) {

				//Arranger
				ListeChaine<int> listeChaine;
				listeChaine.AjouterDebut(2);
				listeChaine.AjouterDebut(3);

				// Auditer
				listeChaine.vider();

				//Agir 
				Assert::IsNull(listeChaine.GetTete());
				Assert::IsNull(listeChaine.GetQueue());
			}

			TEST_METHOD(obtenir_OntenirLeSeulElementDeLaListe_True) {

				//Arranger
				ListeChaine<int> listeChaine;
				listeChaine.AjouterDebut(2);

				// Auditer
				int valeurObtenue = listeChaine.obtenir(0);

				//Agir 
				Assert::IsTrue(1 == listeChaine.nombreElements());
				Assert::IsTrue(2 == valeurObtenue);
			}

			TEST_METHOD(obtenir_OntenirQuandPlusieurElementDansLaListe_True) {

				//Arranger
				ListeChaine<int> listeChaine;
				listeChaine.AjouterDebut(2);
				listeChaine.AjouterDebut(3);
				listeChaine.AjouterDebut(5);

				// Auditer
				int valeurObtenue = listeChaine.obtenir(1);

				//Agir 
				Assert::IsTrue(3 == listeChaine.nombreElements());
				Assert::IsTrue(3 == valeurObtenue);
			}
	};
}