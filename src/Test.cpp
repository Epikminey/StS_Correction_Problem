#include "Test.h"

#include <iostream>
#include <bits/random.h>

/**********************************************************************************************/
#define ASSERT_INVERSE(a, b) \
if (!((a) == (b))) { \
std::cout << "Test failed: " #a " != " #b << " at line " << __LINE__ << std::endl; \
} else { \
std::cout << "Test passed." << std::endl; \
}

void Test::testInverse() {
    const std::string ADN = "+A-B+C-D+E-F+G-H+I";
    auto sequence = Sequence(ADN);
    const std::string ADNvide;
    auto sequenceVide = Sequence(ADNvide);

    std::string ADNtest = "-A-B+C-D+E-F+G-H+I";
    auto sequenceTest = Sequence(ADNtest);
    sequence.inverser(0,1);
    ASSERT_INVERSE(sequence , sequenceTest);

    ADNtest = "-A-B+C-G+F-E+D-H+I";
    sequenceTest = Sequence(ADNtest);
    sequence.inverser(3,4);
    ASSERT_INVERSE(sequence , sequenceTest);

    ADNtest = "-A-B+C-G+F-I+H-D+E";
    sequenceTest = Sequence(ADNtest);
    sequence.inverser(5,6);
    ASSERT_INVERSE(sequence , sequenceTest);

    ADNtest = "-A-B+C-G+F-I+H-D+E";
    sequenceTest = Sequence(ADNtest);
    sequence.inverser(9,2);
    ASSERT_INVERSE(sequence , sequenceTest);

    ADNtest = "-A-B+C-G+F-I+H-D+E";
    sequenceTest = Sequence(ADNtest);
    sequence.inverser(9,0);
    ASSERT_INVERSE(sequence , sequenceTest);

    ADNtest = "-A-B+C-G+F-I+H-D+E";
    sequenceTest = Sequence(ADNtest);
    sequence.inverser(-1,-1);
    ASSERT_INVERSE(sequence , sequenceTest);

    ADNtest = "";
    sequenceTest = Sequence(ADNtest);
    sequenceVide.inverser(0,1);
    ASSERT_INVERSE(sequenceVide , sequenceTest);
}
/**********************************************************************************************/
#define ASSERT_TRANSPOSEE(a, b) \
if (!(a == b)) { \
std::cout << "Test failed: " #a " != " #b << " at line " << __LINE__ << std::endl; \
} else { \
std::cout << "Test passed." << std::endl; \
}

void Test::testTransposee() {
    const std::string ADN = "-A-B+C-G+F-I+H-D+E";
    auto sequence = Sequence(ADN);
    const std::string ADNvide;
    auto sequenceVide = Sequence(ADNvide);

    std::string ADNtest = "-G-A-B+C+F-I+H-D+E";
    auto sequenceTest = Sequence(ADNtest);
    sequence.transposer(0,3,1);
    ASSERT_TRANSPOSEE(sequence , sequenceTest);

    ADNtest = "-G-A+F-B+C-I+H-D+E";
    sequenceTest = Sequence(ADNtest);
    sequence.transposer(4,1,2);
    ASSERT_TRANSPOSEE(sequence , sequenceTest);

    ADNtest = "-G-A+F-B-D+E+C-I+H";
    sequenceTest = Sequence(ADNtest);
    sequence.transposer(4,3,6);
    ASSERT_TRANSPOSEE(sequence , sequenceTest);

    ADNtest = "-G-A+F-B-I+H-D+E+C";
    sequenceTest = Sequence(ADNtest);
    sequence.transposer(4,3,10);
    ASSERT_TRANSPOSEE(sequence , sequenceTest);

    ADNtest = "-G-A+F-B-I+H-D+E+C";
    sequenceTest = Sequence(ADNtest);
    sequence.transposer(6,3,7);
    ASSERT_TRANSPOSEE(sequence , sequenceTest);

    ADNtest = "-G-A+F-B-I+H-D+E+C";
    sequenceTest = Sequence(ADNtest);
    sequence.transposer(6,0,1);
    ASSERT_TRANSPOSEE(sequence , sequenceTest);

    ADNtest = "-G-A-D+E+C+F-B-I+H";
    sequenceTest = Sequence(ADNtest);
    sequence.transposer(6,10,2);
    ASSERT_TRANSPOSEE(sequence , sequenceTest);

    ADNtest = "-G-A-D+E+C+F-B-I+H";
    sequenceTest = Sequence(ADNtest);
    sequence.transposer(9,2,0);
    ASSERT_TRANSPOSEE(sequence , sequenceTest);

    ADNtest = "";
    sequenceTest = Sequence(ADNtest);
    sequenceVide.transposer(0,1, 5);
    ASSERT_TRANSPOSEE(sequenceVide , sequenceTest);
}
/**********************************************************************************************/
#define ASSERT_SUPPRESSION(a, b) \
if (!(a == b)) { \
std::cout << "Test failed: " #a " != " #b << " at line " << __LINE__ << std::endl; \
} else { \
std::cout << "Test passed." << std::endl; \
}

void Test::testSuppression() {
}
/**********************************************************************************************/
#define ASSERT_DUPLICATION(a, b) \
if (!(a == b)) { \
std::cout << "Test failed: " #a " != " #b << " at line " << __LINE__ << std::endl; \
} else { \
std::cout << "Test passed." << std::endl; \
}

void Test::testDuplication() {
}
/**********************************************************************************************/
#define ASSERT_MODIFICATION(a, b) \
if (!(a == b)) { \
std::cout << "Test failed: " #a " != " #b << " at line " << __LINE__ << std::endl; \
} else { \
std::cout << "Test passed." << std::endl; \
}

void Test::testModification() {
}
/**********************************************************************************************/
#define ASSERT_AJOUT(a, b) \
if (!(a == b)) { \
std::cout << "Test failed: " #a " != " #b << " at line " << __LINE__ << std::endl; \
} else { \
std::cout << "Test passed." << std::endl; \
}

void Test::testAjout() {
}
/**********************************************************************************************/


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


bool Test::testAffichage(const bool aleatoire) {

    const string ADN1 = "+A-B+C-D+E-F+G-H+I";
    const string ADN2 = "+A-B+C-D+E-F+G-C+I";

    auto sequence1 = Sequence(ADN1);
    auto sequence2 = Sequence(ADN2);

    Instance instance = Instance(sequence1, sequence2);

    Solution solution = Solution(instance, 20);

    if(!aleatoire)
    {
        const string ADN3 = "+A-B+C-D+E-F-C+I";
        const string ADN4 = "+I-C-F+E-D+C-B+A";
        const string ADN5 = "+I-C+G-F+E-D+C-B+A";
        const string ADN6 = "+I-H+G-F+E-D+C-B+A";
        const string ADN7 = "+I-D+C-B-H+G-F+E+A";

        vector<string> listeSequencesBrutes = {ADN1, ADN2, ADN3, ADN4, ADN5, ADN6, ADN7};


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

        vector<Instance> listeInstances = {instance};

        solution = Solution(listeInstances[0], listeMouvements);
    }


    solution.afficherSolution();

    return true;
}

bool Test::testSolutionOptimale() {


    const string ADN1 = "+A-B+C-D+E-F+G-H+I";
    const string ADN2 = "+A-B+C-D+E-F+G-C+I";
    //const string ADN7 = "+I-D+C-B-H+G-F+E+A";

    vector<string> listeSequencesBrutes = {ADN1,  ADN2};

    auto sequence1 = Sequence(ADN1);
    auto sequence2 = Sequence(ADN2);

    Instance instance = Instance(sequence1, sequence2);


    Algorithme algo(instance);

    cout << "Test : ";
    instance.obtenirTerminale().afficherSequence();

    unsigned int nbGenerationMax = 10;
    float tauxMutation = 0.2;
    unsigned int nbMutationParGen = 10;
    unsigned int nbSolutionParGen = 16;

    algo.rechercheSolution(nbGenerationMax, tauxMutation, nbMutationParGen, nbSolutionParGen, true);

    return true;
}
