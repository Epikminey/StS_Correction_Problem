#include "Algorithme.h"

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

/*****************************************************************************************************
***** rechercheSolution : Exécute l'algorithme de recherche de la solution optimale au problème. *****
*****************************************************************************************************/
bool Algorithme::rechercheSolution(
    unsigned int nbGenerationMax,
    float tauxMutation, //!!!!!Demander des détails dessus
    unsigned int nbMutationParGen,
    unsigned int nbSolutionParGen) {

    // Param : nb génération, taux de mutation, nb mutation par génération, nb solutions par génération (12/16/20)
    // On supprime la moitié, et on fait se reproduire le reste -> sélection par tournoi
    // Aléatoire qui décider où couper pour le croisement

    // Définition des constantes utiles à la recherche de solution

    // Graine pour la sélection de Solution aléatoire lors de la sélection par tournoi
    random_device rd;
    mt19937 gen(rd());

    // L'instance initiale qui contient S : la séquence de départ, et T : la séquence d'arrivée
    const Instance instanceInitiale(meilleureSolution_.obtenirListeSequences().front(),
                            meilleureSolution_.obtenirListeSequences().back());

    // Définitions des variables utiles à la recherche de solution
    bool solutionOptimaleTrouvee = false;
    unsigned int numGeneration = 0;
    vector <Solution> generationCourante(nbSolutionParGen);
    //nbMutationParGen : mis à jour au cours de la recherche

    cout << "Distance levenshtein : " << nombreMouvements_;

    while(numGeneration < nbGenerationMax) {

        if(numGeneration == 0) {
            // Génération de P solutions composées de M mouvements aléatoires
            ranges::generate(generationCourante, [&]() {
                return Solution(instanceInitiale, nbMutationParGen);
            });
        }
        else {
            // Croisement des solutions de la génération courante

            for(int i = 0; i < nbSolutionParGen; i += 2) {
                Solution &premierParent = generationCourante[i];
                Solution &deuxiemeParent = generationCourante[i+1];

                // Génération d'un nombre aléatoire pour déterminer à quel
                // endroit on souhaite "couper" pour le croisement
                uniform_real_distribution<float> dis(0.3, 0.7);
                float separation = dis(gen);

            }

        }

        // Calcul des evaluations des solutions (on les stocke pour la suite de l'algo)

        vector<unsigned int> evaluations(nbSolutionParGen);
        for(const Solution& solution : generationCourante) {
            // Pour évaluer une solution on calcule la distance de levenshtein
            // (cad le nb de mouvements restant à faire au minimum)
            // Entre la séquence finale d'une solution et séquence finale de l'instance du problème

            evaluations.push_back(DistanceLevenshtein::calculerDistanceLevenshtein(
                solution.obtenirListeSequences().back(), instanceInitiale.obtenirTerminale()));

            // Si on a trouvé une solution allant de S à T
            // Cette solution devient la meilleure solution
            if(evaluations.back() == 0) {
                nbMutationParGen --;
                numGeneration = 0;

                meilleureSolution_ = solution;
            }
        }

        // Sélection des meilleures solutions pour la génération future

        //Coder la sélection par tournoi (actuellement on prend les Solutions côte à côte)

        vector<Solution> nouvelleGeneration;
        for(int i = 0; i < nbSolutionParGen; i += 2) {

            Solution &solutionGagnante = (evaluations[i] < evaluations[i + 1]) ?
                                          generationCourante[i] :
                                          generationCourante[i + 1];

            nouvelleGeneration.push_back(solutionGagnante);
        }

        // La génération courante est remplacée par la nouvelle génération
        // pour la prochaine itération de l'algorithme
        generationCourante = nouvelleGeneration;
    }

    return solutionOptimaleTrouvee;
}
