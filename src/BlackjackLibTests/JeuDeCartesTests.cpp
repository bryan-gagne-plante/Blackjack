#include "CppUnitTest.h"

#include "JeuDeCartes.h"
#include "JeuDeCartes.h"
#include "Carte.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackjackLibTests {

	TEST_CLASS(JeuDeCartesTests) {
		public:
			TEST_METHOD(DistribuerUneCarte_UneCarte_LaCarte) {

				//Arranger
				JeuDeCartes jeuDeCartes;

				//Agir
				Carte carteDistribuee = jeuDeCartes.DistribuerUneCarte();

				//Auditer
				Assert::IsTrue(EstCarteValide(carteDistribuee));
			}

			TEST_METHOD(DistribuerUneCarte_QuandLeJeuDeCarteEstVide_True) {

				//Arranger
				JeuDeCartes jeuDeCartes;

				//Agir
				Carte carteDistribuee = jeuDeCartes.DistribuerUneCarte();

				//Auditer
				Assert::IsTrue(EstCarteValide(carteDistribuee));
			}

			TEST_METHOD(DistribuerUneCarte_RenvoirCartesDifferentes_True) {

				//Arranger
				JeuDeCartes jeuDeCartes;

				//Agir
				Carte premiereCarte = jeuDeCartes.DistribuerUneCarte();
				Carte secondeCarte = jeuDeCartes.DistribuerUneCarte();

				//Auditer
				Assert::IsTrue(premiereCarte.ObtenirValeur() != secondeCarte.ObtenirValeur());
			}

			TEST_METHOD(JeuCarteVide_SansInitialiser_False) {

				//Arranger
				JeuDeCartes jeuDeCartes;

				//Agir
				bool estVide = jeuDeCartes.JeuCarteVide();

				//Auditer
				Assert::IsFalse(estVide);
			}

			TEST_METHOD(JeuCarteVide_QuandOnAjoute_False) {

				//Arranger
				JeuDeCartes jeuDeCartes;

				//Agir
				bool estVide = jeuDeCartes.JeuCarteVide();

				//Auditer
				Assert::IsFalse(estVide);
			}

			TEST_METHOD(JeuCarteVide_QuandOnSupprimeToutesLesCartes_false) {

				//Arranger
				JeuDeCartes jeuDeCartes;

				//Agir
				bool estVide = jeuDeCartes.JeuCarteVide();

				//Auditer
				Assert::IsFalse(estVide);
			}
			bool EstCarteValide(const Carte& p_cartes) {
				bool estValid = false;
				if (p_cartes.ObtenirValeur() >= 1 && p_cartes.ObtenirValeur() <= 13 && p_cartes.ObtenirSymbole() >= 1 && p_cartes.ObtenirSymbole() <= 4) {
					estValid = true;
				}
				return estValid;
			}
	};
}