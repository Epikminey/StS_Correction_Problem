#include "Algorithme.h"
//#include "Test.h"

#include <iostream>
#include <map>


// Fonction pour valider et convertir un entier
int validate_and_parse_int(const string& value, const int min, const int max) {
    int number;
    try {
        number = stoi(value);
    } catch (...) {
        throw invalid_argument("La valeur doit etre un entier.");
    }
    if (number < min || number > max) {
        throw out_of_range("La valeur doit etre comprise entre " + to_string(min) + " et " + to_string(max) + ".");
    }
    return number;
}

// Fonction pour valider et convertir un flottant
float validate_and_parse_float(const string& value, const float min, const float max) {
    float number;
    try {
        number = stof(value);
    } catch (...) {
        throw invalid_argument("La valeur doit être un flottant.");
    }
    if (number < min || number > max) {
        throw out_of_range("La valeur doit etre comprise entre " + to_string(min) + " et " + to_string(max) + ".");
    }
    return number;
}

// Fonction pour valider et convertir un booléen
bool validate_and_parse_bool(const string& value) {
    if (value == "true" || value == "1") {
        return true;
    }
    if (value == "false" || value == "0") {
        return false;
    }
    throw invalid_argument("La valeur doit etre 'true', 'false', '1' ou '0'.");
}



int main(int argc, char* argv[]) {

    // Exemple de paramètres
    // StS_Correction_Problem.exe "+A-B+C-D+E-F+G-H+I" "+I-H+G-F+E-D+C-B-A" --genMax 2000 --mutParGen 12 --solParGen 22 --tauxMut 0.3 --details true

    // Valeurs des paramètres par défaut
    int genMax = 1000;
    int mutParGen = 10;
    int solParGen = 24;
    float tauxMut = 0.5;
    bool details = false;
    string ADN1 = "+A-B+C-D+E-F+G-H+I";
    string ADN2 = "+I-H+G-F+E-D+C-B+A";


    // Parcours des arguments

    // Vérifier qu'il y a au moins deux arguments obligatoires
    if (argc < 3) {
        std::cerr << "Erreur : Deux sequences d'ADN sous la forme de chaines de caracteres sont obligatoires." << std::endl;
        std::cerr << "Utilisation : ./programme sequence1 sequence2 [options...]" << std::endl;
        return 1;
    }

    // Lecture des deux séquences d'ADN
    ADN1 = argv[1];
    ADN2 = argv[2];

    for (int i = 3; i < argc; i += 2) {
        string key = argv[i];
        if (i + 1 >= argc) {
            cerr << "Erreur : Valeur manquante pour l'argument " << key << endl;
            return 1; // Retourne une erreur
        }

        try {
            if (key == "--genMax") {
                genMax = validate_and_parse_int(argv[i + 1], 1, 100000);
            } else if (key == "--mutParGen") {
                mutParGen = validate_and_parse_int(argv[i + 1], 0, 1000);
            } else if (key == "--solParGen") {
                solParGen = validate_and_parse_int(argv[i + 1], 2, 256);
            }
            else if (key == "--tauxMut") {
                tauxMut = validate_and_parse_float(argv[i + 1], 0.0, 1.0);
            } else if (key == "--details") {
                details = validate_and_parse_bool(argv[i + 1]);
            } else {
                cerr << "Erreur : Argument inconnu " << key << endl;
                return 1; // Retourne une erreur
            }
        } catch (const exception& e) {
            cerr << "Erreur pour " << key << " : " << e.what() << endl;
            return 1; // Retourne une erreur
        }
    }


    // Affiche les valeurs finales
    cout << "Arguments :" << endl;
    cout << "Nombre de generations maximum : " << genMax << endl;
    cout << "Nombre de mutations par generations : " << mutParGen << endl;
    cout << "Nombre de solutions par generations : " << solParGen << endl;
    cout << "Taux de mutation : " << tauxMut << endl;
    cout << "Affichage detaille : " << (details ? "true" : "false") << endl;
    cout << endl << endl;

    // Création de deux séquences d'ADN à partir des séquences données en paramètre
    const auto sequence1 = Sequence(ADN1);
    const auto sequence2 = Sequence(ADN2);

    const auto instance = Instance(sequence1, sequence2);

    auto algo = Algorithme(instance);

    algo.rechercheSolution(genMax, tauxMut, mutParGen, solParGen, details);

    const unsigned int score = algo.obtenirMeilleureSolution().obtenirEvaluation();
    const int nbMouvements = algo.obtenirMeilleureSolution().obtenirListeMouvements().size();
    cout << "Meilleure solution trouvee en " << nbMouvements << " mouvements." << endl;
    cout << "Score de la solution : " << score << endl;

    algo.afficherMeilleureSolution();

    return 0;
}
