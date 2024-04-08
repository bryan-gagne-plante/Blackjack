#include "CppUnitTest.h"

#include "MaClasse.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackjackLibTests
{
	TEST_CLASS(MaClasseTests)
	{
	public:
		
		TEST_METHOD(vrai_objetNonUtilise_vrai)
		{
			// Arranger
			MaClasse mc;

			// Agir
			bool calculee = mc.vrai();

			// Auditer
			Assert::IsTrue(calculee);
		}
	};
}
