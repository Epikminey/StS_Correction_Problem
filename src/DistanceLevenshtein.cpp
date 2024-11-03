#include "DistanceLevenshtein.h"

#include <vector>

using namespace std;

int DistanceLevenshtein::calculerDistanceLevenshtein(const Sequence& sequence1, const Sequence& sequence2) {
    const unsigned int tailleSequence1 = sequence1.obtenirTailleSequence();
    const unsigned int tailleSequence2 = sequence2.obtenirTailleSequence();
    // D est un tableau de longueurChaine1+1 rangées et longueurChaine2+1 colonnes
    // D est indexé à partir de 0, les chaînes à partir de 1
    vector D(tailleSequence1 + 1, std::vector<int>(tailleSequence2 + 1));

    // Initialisation de la première ligne et de la première colonne du tableau D
    for (int i = 0; i <= tailleSequence1; i++) {
        D[i][0] = i;
    }
    for (int j = 0; j <= tailleSequence2; j++) {
        D[0][j] = j;
    }

    // Calcul des autres valeurs de la matrice D
    for (int ligne = 1; ligne <= tailleSequence1; ligne++) {
        for (int colonne = 1; colonne <= tailleSequence2; colonne++) {
            int coutSubstitution = 0;
            const char lettre1 = sequence1.obtenirCase(ligne - 1).lireLettre();
            const char lettre2 = sequence2.obtenirCase(colonne - 1).lireLettre();
            if ( lettre1 != lettre2) {
                coutSubstitution = 1;
            }
            D[ligne][colonne] = min(D[ligne - 1][colonne] + 1,             // effacement du nouveau caractère de séquence1
                     min(D[ligne][colonne - 1] + 1,                        // insertion dans séquence2 du nouveau caractère de séquence1
                           D[ligne - 1][colonne - 1] + coutSubstitution) // substitution
                           );
        }
    }

    // On retourne la distance de Levenshtein qui se trouve à la dernière ligne/colonne de la matrice D
    return D[tailleSequence1][tailleSequence2];
}
