#include "CppUnitTest.h"

#include "Croupier.h"
#include "Carte.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackjackLibTests {

	TEST_CLASS(CroupierTests) {
		public:
			TEST_METHOD(calculerScore_CasAucuneCarte_True) {

				//Arranger
				Croupier croupier;

				//Agir
				int scoreObtenue = croupier.calculerScore();

				//Auditer
				Assert::IsTrue(0 == scoreObtenue);
			}

			TEST_METHOD(calculerScore_CasIlYaDesCartes_Valeur) {

				//Arranger
				Croupier croupier;
				Carte carte1(2, Pique, "image1.png");
				Carte carte2(2, Coeur, "image1.png");
				Carte carte3(5, Carreau, "image1.png");
				croupier.recevoirCarte(carte1);
				croupier.recevoirCarte(carte2);
				croupier.recevoirCarte(carte3);

				//Agir
				int scoreObtenue = croupier.calculerScore();

				//Auditer
				Assert::IsTrue(9 == scoreObtenue);
			}

			TEST_METHOD(calculerScore_QuandCarteEstAs_Valeur) {

				//Arranger
				Croupier croupier;
				Carte carteAs(1, Trefle, "as.png");
				croupier.recevoirCarte(carteAs);

				//Agir
				int scoreObtenue = croupier.calculerScore();

				//Auditer
				Assert::IsTrue(11 == scoreObtenue);
			}

			TEST_METHOD(verifierBlackjack_BlackJackValide_True) {

				//Arranger
				Croupier croupier;
				Carte carteAs(1, Trefle, "as.png");
				Carte carte10(10, Coeur, "cart10.png");
				croupier.recevoirCarte(carteAs);
				croupier.recevoirCarte(carte10);

				//Agir
				bool estBlackJack = croupier.verifierBlackjack();

				//Auditer
				Assert::IsTrue(estBlackJack);
			}

			TEST_METHOD(verifierBlackjack_BlackJackInValide_False) {

				//Arranger
				Croupier croupier;
				Carte carte10(10, Trefle, "carte10.png");
				Carte carteRoi(10, Coeur, "carteRoi.png");
				croupier.recevoirCarte(carte10);
				croupier.recevoirCarte(carteRoi);

				//Agir
				bool estBlackJack = croupier.verifierBlackjack();

				//Auditer
				Assert::IsFalse(estBlackJack);
			}

			TEST_METHOD(verifierBuste_SiScoreInferieurA21_False) {

				//Arranger
				Croupier croupier;
				Carte carte1(2, Trefle, "carte1.png");
				croupier.recevoirCarte(carte1);

				//Agir
				bool buste = croupier.verifierBuste();

				//Auditer
				Assert::IsFalse(buste);
			}

			TEST_METHOD(verifierBuste_SiScoreEgalA21_False) {

				//Arranger
				Croupier croupier;
				Carte carteAs(1, Trefle, "as.png");
				Carte carte10(10, Coeur, "cart10.png");
				croupier.recevoirCarte(carteAs);
				croupier.recevoirCarte(carte10);

				//Agir
				bool buste = croupier.verifierBuste();

				//Auditer
				Assert::IsFalse(buste);
			}
			TEST_METHOD(verifierBuste_SiScoreDepasse21_IsFalse) {

				//Arranger
				Croupier croupier;
				Carte carteAs(1, Trefle, "as.png");
				Carte carte10(10, Coeur, "cart10.png");
				Carte carte3(3, Coeur, "cart10.png");
				croupier.recevoirCarte(carteAs);
				croupier.recevoirCarte(carte10);
				croupier.recevoirCarte(carte3);

				//Agir
				bool buste = croupier.verifierBuste();

				//Auditer
				Assert::IsFalse(buste);
			}
	};
}