#include <iostream>
#include <windows.h>
#include "Test.h"

using namespace std;



int main() {

    // Pour s'assurer que l'affichage de la console soit en UTF8
    SetConsoleOutputCP(CP_UTF8);

    //Test de l'affichage d'une solution
    Test::testAffichage();

    return 0;
}
