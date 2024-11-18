#include "Algorithme.h"

#include <DistanceLevenshtein.h>


Algorithme::Algorithme(const Instance &instance, unsigned int nombreMutations): meilleureSolution_(instance, nombreMutations) {
    nombreMouvements_ = instance.obtenirDistanceLevenshtein();
}

void Algorithme::afficherNombreMouvements() const {
    cout << "Nombre de mouvements : " << nombreMouvements_ << endl;
}

void Algorithme::afficherMeilleureSolution() const {
    cout << "Meilleure solution : " << endl;
    meilleureSolution_.afficherSolution();
}

//Algorithme::Algorithme(const Instance &instance) {
//}
bool Algorithme::rechercheSolution() {
    bool solution_trouvee = false;

    unsigned int nb_generation = 0;

    cout << "Distance levenshtein : " << nombreMouvements_;

    return solution_trouvee;
}
