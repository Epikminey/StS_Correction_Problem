#include "Test.h"

#include <iostream>
//#include <windows.h>

using namespace  std;

int main() {

    // Pour s'assurer que l'affichage de la console soit en UTF8
    //SetConsoleOutputCP(CP_UTF8);

    // Test de la résolution d'une solution
    //Test::testSolutionOptimale();

    // Test de l'affichage d'une solution
    Test::testAffichage(true);

    return 0;
}
