#include "CppUnitTest.h"

#include "Joueur.h"
#include "Carte.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackjackLibTests {

	TEST_CLASS(JoueurTests) {
		public:
			TEST_METHOD(calculerScore_CasAucuneCarte_True) {

				//Arranger
				Joueur joueur;

				//Agir
				int scoreObtenue = joueur.calculerScore();

				//Auditer
				Assert::IsTrue(0 == scoreObtenue);
			}

			TEST_METHOD(calculerScore_CasIlYaDesCartes_Valeur) {

				//Arranger
				Joueur joueur;
				Carte carte1(2, Pique, "image1.png");
				Carte carte2(2, Coeur, "image1.png");
				Carte carte3(5, Carreau, "image1.png");
				joueur.recevoirCarte(carte1);
				joueur.recevoirCarte(carte2);
				joueur.recevoirCarte(carte3);

				//Agir
				int scoreObtenue = joueur.calculerScore();

				//Auditer
				Assert::IsTrue(9 == scoreObtenue);
			}

			TEST_METHOD(calculerScore_QuandCarteEstAs_Valeur) {

				//Arranger
				Joueur joueur;
				Carte carteAs(1, Trefle, "as.png");
				joueur.recevoirCarte(carteAs);

				//Agir
				int scoreObtenue = joueur.calculerScore();

				//Auditer
				Assert::IsTrue(11 == scoreObtenue);
			}

			TEST_METHOD(verifierBlackjack_BlackJackValide_True) {

				//Arranger
				Joueur joueur;
				Carte carteAs(1, Trefle, "as.png");
				Carte carte10(10, Coeur, "cart10.png");
				joueur.recevoirCarte(carteAs);
				joueur.recevoirCarte(carte10);

				//Agir
				bool estBlackJack = joueur.verifierBlackjack();

				//Auditer
				Assert::IsTrue(estBlackJack);
			}

			TEST_METHOD(verifierBlackjack_BlackJackInValide_False) {

				//Arranger
				Joueur joueur;
				Carte carte10(10, Trefle, "carte10.png");
				Carte carteRoi(10, Coeur, "carteRoi.png");
				joueur.recevoirCarte(carte10);
				joueur.recevoirCarte(carteRoi);

				//Agir
				bool estBlackJack = joueur.verifierBlackjack();

				//Auditer
				Assert::IsFalse(estBlackJack);
			}
			TEST_METHOD(verifierBuste_SiScoreInferieurA21_False) {

				//Arranger
				Joueur joueur;
				Carte carte1(2, Trefle, "carte1.png");
				joueur.recevoirCarte(carte1);

				//Agir
				bool buste = joueur.verifierBuste();

				//Auditer
				Assert::IsFalse(buste);
			}

			TEST_METHOD(verifierBuste_SiScoreEgalA21_False) {

				//Arranger
				Joueur joueur;
				Carte carteAs(1, Trefle, "as.png");
				Carte carte10(10, Coeur, "cart10.png");
				joueur.recevoirCarte(carteAs);
				joueur.recevoirCarte(carte10);

				//Agir
				bool buste = joueur.verifierBuste();

				//Auditer
				Assert::IsFalse(buste);
			}
			TEST_METHOD(verifierBuste_SiScoreDepasse21_True) {

				//Arranger
				Joueur joueur;
				Carte carteAs(1, Trefle, "as.png");
				Carte carte10(10, Coeur, "cart10.png");
				Carte carte3(3, Coeur, "cart10.png");
				joueur.recevoirCarte(carteAs);
				joueur.recevoirCarte(carte10);
				joueur.recevoirCarte(carte3);

				//Agir
				bool buste = joueur.verifierBuste();

				//Auditer
				Assert::IsFalse(buste);
			}
	};
}