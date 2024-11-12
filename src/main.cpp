#include <iostream>

#include "Sequence.h"
#include "DistanceLevenshtein.h"
#include "Instance.h"
#include "Solution.h"
#include "Algorithme.h"

using namespace std;

int main() {
    const string ADN1 = "+A-B+C-D+E-F+G-H+I";
    const string ADN2 = "+I-H+G-F+E-D+C-B+A"; // 1 mouvement nécessaire: inversion de toute la chaine avec ADN1
    const string ADN3 = "+F-D";
    const string ADN4 = "+A-D+V-F+S-V-S";
    const string ADN5 = "+F+G-D+X+S+C-V+F-R";
    const string ADN6 = "+B-E+D+V+E-Z";
    const string ADN7 = "+A-B+C-D+E-F+G-H+I-J+K-L+M-N+O-P+Q-R+S-T+U-V+W-X+Y-Z";

    auto sequence1 = Sequence(ADN1);
    auto sequence2 = Sequence(ADN2);
    auto sequence3 = Sequence(ADN3);
    auto sequence4 = Sequence(ADN4);
    auto sequence5 = Sequence(ADN5);
    auto sequence6 = Sequence(ADN6);
    auto sequence7 = Sequence(ADN7);

    auto instance1 = Instance(sequence1, sequence2);
    auto instance2 = Instance(sequence3, sequence4);
    auto instance3 = Instance(sequence1, sequence5);
    auto instance4 = Instance(sequence4, sequence6);

    sequence1.afficherSequence();
    //sequence1.inverserTransposer(3, 4, 4);
    sequence1.inverser(3, 4);
    sequence1.transposer(3, 4, 3);
    sequence1.afficherSequence();

    /*
    vector sequences = {sequence1, sequence2, sequence3, sequence4, sequence5, sequence6};

    Mouvement mouvement1 = {"substitution", 8, 1, SUBSTITUTION, "str"};
    Mouvement mouvement2 = {"perte", 7, 1, PERTE, "str"};
    Mouvement mouvement3 = {"inversion", 1, 8, INVERSION, "str"};
    Mouvement mouvement4 = {"ajout", 3, 1, AJOUT, "str"};
    Mouvement mouvement5 = {"substitution", 2, 1, SUBSTITUTION, "str"};
    */

    /*Mouvement mouvement1 = {"substitution", 8, 1, 0, "str"};
    Mouvement mouvement2 = {"perte", 7, 1, 0, "str"};
    Mouvement mouvement3 = {"inversion", 1, 8, 0, "str"};
    Mouvement mouvement4 = {"ajout", 3, 1, 0, "str"};
    Mouvement mouvement5 = {"substitution", 2, 1, 0, "str"};
    vector mouvements = {mouvement1, mouvement2, mouvement3, mouvement4, mouvement5};

    const unsigned int nbSequences = sequences.size();
    const unsigned int nbMouvements = mouvements.size();
    */

    /*auto solution1 = Solution(instance1, 10);
    for (const auto &sequence: solution1.obtenirListeSequences()) {
        sequence.afficherSequence();
    }*/

    // La boucle pour afficher tous les mouvements
    /*for (const auto &[nomMouvement, indexDepart, nombreCases, indexDestination, nomCase]: solution1.
         obtenirListeMouvements()) {
        cout << nomMouvement << " " << indexDepart << " " << nombreCases << " " << indexDestination << " " << nomCase <<
                endl;
    }*/



    //solution1.obtenirDerniereSequence().afficherSequence();

    /*auto algorithme1 = Algorithme(instance1);
    auto algorithme2 = Algorithme(instance2);
    auto algorithme3 = Algorithme(instance3);
    auto algorithme4 = Algorithme(instance4);

    printf(algorithme1.resultat);*/

    cout << "Hello, World!" << endl;
    return 0;
}
