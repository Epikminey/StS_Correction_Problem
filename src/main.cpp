#include "Algorithme.h"
//#include "Test.h"

#include <iostream>


int main() {

    /*Test::testInverse();
    Test::testTransposee();
    Test::testSuppression();
    Test::testDuplication();
    Test::testModification();
    Test::testAjout();*/

    const unsigned int nbGenerationMax = 10000;
    const float tauxMutation = 0.3;
    const unsigned int nbMutationParGen = 10;
    const unsigned int nbSolutionParGen = 48;
    const bool affichageDetaille = false;

    const std::string ADN1 = "+A-B+C-D+E-F+G-H+I";
    const std::string ADN2 = "+I-H+G-F+E-D+C-B+A";

    const auto sequence1 = Sequence(ADN1);
    const auto sequence2 = Sequence(ADN2);

    const auto instance = Instance(sequence1, sequence2);

    auto algo = Algorithme(instance);

    const bool trouvee = algo.rechercheSolution(nbGenerationMax, tauxMutation, nbMutationParGen, nbSolutionParGen, affichageDetaille);

    if(trouvee) {
        cout << "Solution optimale trouvee !" << endl;
    } else {
        cout << "Solution optimale non trouvee :" << endl;
    }

    cout << "score : " << algo.obtenirMeilleureSolution().obtenirEvaluation() << endl;
    //algo.afficherNombreMouvements();
    algo.afficherMeilleureSolution();


    return 0;
}
