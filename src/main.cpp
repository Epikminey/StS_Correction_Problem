#include <iostream>
#include "Sequence.h"
#include "DistanceLevenshtein.h"
#include "Instance.h"
#include "Solution.h"
#include "Algorithme.h"
using namespace std;

int main()
{
    const string ADN1 = "+A-B+C-D+E-F+G-H+I";
    const string ADN2 = "+I-H+G-F+E-D+C-B+A"; // 1 mouvement nécessaire: inversion de toute la chaine avec ADN1
    const string ADN3 = "+F-D";
    const string ADN4 = "+A-D+V-F+S-V-S";
    const string ADN5 = "+F+G-D+X+S+C-V+F-R";
    const string ADN6 = "+B-E+D+V+E-Z";

    auto sequence1 = Sequence(ADN1);
    auto sequence2 = Sequence(ADN2);
    auto sequence3 = Sequence(ADN3);
    auto sequence4 = Sequence(ADN4);
    auto sequence5 = Sequence(ADN5);
    auto sequence6 = Sequence(ADN6);


    sequence1.ajouterCase(12, "-A");
    sequence1.modifierCase(12, "-Af");

    sequence1.afficherSequence();

    auto instance1 = Instance(sequence1, sequence2);
    auto instance2 = Instance(sequence3, sequence4);
    auto instance3 = Instance(sequence1, sequence5);
    auto instance4 = Instance(sequence4, sequence6);

    /*auto algorithme1 = Algorithme(instance1);
    auto algorithme2 = Algorithme(instance2);
    auto algorithme3 = Algorithme(instance3);
    auto algorithme4 = Algorithme(instance4);

    printf(algorithme1.resultat);*/

    cout << "Hello, World!" << endl;
    return 0;
}