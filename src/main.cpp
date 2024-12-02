#include "Test.h"

#include <iostream>
//#include <windows.h>

using namespace  std;

int main() {

    // Pour s'assurer que l'affichage de la console soit en UTF8
    //SetConsoleOutputCP(CP_UTF8);

    //Test de l'affichage d'une solution
    Test::testSolutionOptimale();

    /*
    const unsigned int nbGenerationMax = 2;
    const float tauxMutation = 0.5;
    const unsigned int nbMutationParGen = 10;
    const unsigned int nbSolutionParGen = 16;
    const bool affichageDetaille = true;

    const std::string ADN1 = "+A-B+C-D+E-F+G-H+I";
    const std::string ADN6 = "+I-H+G-F+E-D+C-B+A";

    std::cout << "OK1";
    const auto sequence1 = Sequence(ADN1);
    const auto sequence2 = Sequence(ADN6);

    std::cout << "OK2";

    const auto instance = Instance(sequence1, sequence2);

    std::cout << "OK3";

    auto algo = Algorithme(instance);

    std::cout << "OK4";

    algo.rechercheSolution(nbGenerationMax, tauxMutation, nbMutationParGen, nbSolutionParGen, affichageDetaille);
    */

    return 0;
}
