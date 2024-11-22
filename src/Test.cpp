#include "Test.h"

#include <Algorithme.h>


bool Test::testAntoine() {

    // Exemple de transformations sur `sequence1`
    const string ADN1 = "+A-B+C-D+E-F+G-H+I";
    const string ADN2 = "+A-B+C-D+E-F+G-C+I";
    const string ADN3 = "+A-B+C-D+E-F-C+I";
    const string ADN4 = "+I-C-F+E-D+C-B+A";
    const string ADN5 = "+I-C+G-F+E-D+C-B+A";
    const string ADN6 = "+I-H+G-F+E-D+C-B+A";
    const string ADN7 = "+I-D+C-B-H+G-F+E+A";

    const auto sequence1 = Sequence(ADN1);
    auto sequence2 = Sequence(ADN2);
    auto sequence3 = Sequence(ADN3);
    auto sequence4 = Sequence(ADN4);
    auto sequence5 = Sequence(ADN5);
    auto sequence6 = Sequence(ADN6);
    auto sequence7 = Sequence(ADN7);

    auto instance = Instance(sequence1, sequence2);

    auto solution1 = Solution(instance, 7);

    return true;
}


string genererChaineAleatoire(const vector<char>& caracteresPossibles, int longeurMax) {
    string chaine;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distLongueur(1, longeurMax);
    uniform_int_distribution<> distCaractere(0, caracteresPossibles.size() - 1);
    uniform_int_distribution<> distSymbole(0, 1);

    int longueurChaine = distLongueur(gen);  // Calcul de la longueur aléatoire de la chaîne, entre 1 et tailleMax

    for (int i = 0; i < longueurChaine; ++i) {
        char symbole = (distSymbole(gen) == 0) ? '-' : '+';
        char caractere = caracteresPossibles[distCaractere(gen)];
        chaine += symbole;
        chaine += caractere;
    }

    return chaine;
}

bool Test::testEnzo() {
    //Paramètres de test
    const int nombreSequences = 2;
    const int longueurMax = 10;
    const vector<char>  caracteresPossibles = {'A', 'C', 'T', 'G'};

    vector<string> listeSequencesBrutes;

    // Génère "nombreSequences" chaines aléatoires
    for (int i = 0; i < nombreSequences; ++i) {
        listeSequencesBrutes.push_back(genererChaineAleatoire(caracteresPossibles, longueurMax));
    }

    vector<Sequence> listeSequences;

    // Génère des séquences à partir des chaines
    for(const auto& sequenceBrute : listeSequencesBrutes) {
        listeSequences.emplace_back(sequenceBrute);
    }


    vector<Instance> listeInstances;

    // Peut être modifié si on ne veut pas des instances entre toutes les séquences
    for(const auto& sequenceA : listeSequences) {
        for(const auto& sequenceB : listeSequences) {
            listeInstances.emplace_back(sequenceA, sequenceB);
        }
    }

    return true;
}


bool Test::testAffichage() {

    const string ADN1 = "+A-B+C-D+E-F+G-H+I";
    const string ADN2 = "+A-B+C-D+E-F+G-C+I";
    const string ADN3 = "+A-B+C-D+E-F-C+I";
    const string ADN4 = "+I-C-F+E-D+C-B+A";
    const string ADN5 = "+I-C+G-F+E-D+C-B+A";
    const string ADN6 = "+I-H+G-F+E-D+C-B+A";
    const string ADN7 = "+I-D+C-B-H+G-F+E+A";

    vector<string> listeSequencesBrutes = {ADN1, ADN2, ADN3, ADN4, ADN5, ADN6, ADN7};

    auto sequence1 = Sequence(ADN1);
    auto sequence2 = Sequence(ADN2);
    auto sequence3 = Sequence(ADN3);
    auto sequence4 = Sequence(ADN4);
    auto sequence5 = Sequence(ADN5);
    auto sequence6 = Sequence(ADN6);
    auto sequence7 = Sequence(ADN7);

    vector<Sequence> listeSequences = {sequence1, sequence2, sequence3, sequence4, sequence5, sequence6};

    Mouvement mouvement1 = {SUBSTITUTION, 8, 1, 8, "str"};
    Mouvement mouvement2 = {SUPPRESSION, 7, 1, 7, "str"};
    Mouvement mouvement3 = {INVERSION, 1, 8, 1, "str"};
    Mouvement mouvement4 = {AJOUT, 3, 1, 3, "str"};
    Mouvement mouvement5 = {SUBSTITUTION, 2, 1, 8, "str"};
    Mouvement mouvement6 = {TRANSPOSITION, 2, 4, 5, "str"};

    vector<Mouvement> listeMouvements = {mouvement1, mouvement2, mouvement3, mouvement4, mouvement5};

    auto instance = Instance(sequence1, sequence2);
    vector<Instance> listeInstances = {instance};

    // Exemple d'initialisation d'une solution et d'affichage
    auto solution = Solution(listeInstances[0], 6);
    //solution1.obtenirListeMouvements() = listeMouvements_; // Potentielle erreur de pointeurs

    solution.afficherSolution();

    return true;
}

bool Test::testSolutionOptimale() {

    const string ADN1 = "+A-B+C-D+E-F+G-H+I";
    const string ADN2 = "+A-B+C-D+E-F+G-C+I";
    const string ADN6 = "+I-H+G-F+E-D+C-B+A";
    //const string ADN7 = "+I-D+C-B-H+G-F+E+A";

    vector<string> listeSequencesBrutes = {ADN1,  ADN2};

    const auto sequence1 = Sequence(ADN1);
    const auto sequence2 = Sequence(ADN6);


    const auto instance = Instance(sequence1, sequence2);


    Algorithme algo(instance);

    cout << "Test : ";
    instance.obtenirTerminale().afficherSequence();

    const unsigned int nbGenerationMax = 1000;
    const float tauxMutation = 0.5;
    const unsigned int nbMutationParGen = 10;
    const unsigned int nbSolutionParGen = 16;


    algo.rechercheSolution(nbGenerationMax, tauxMutation, nbMutationParGen, nbSolutionParGen, false);

    return true;
}
