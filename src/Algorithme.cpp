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

    cout << "Début de la recherche de solution." << endl;
    cout << "Séquence départ : " << endl;
    instanceInitiale.obtenirSource().afficherSequence();
    cout << "Séquence arrivée : " << endl;
    instanceInitiale.obtenirTerminale().afficherSequence();

    cout << "Distance levenshtein (valeur optimale à atteindre: " << nombreMouvements_ << endl;

    cout << "Appuyez sur entrée pour continuer. (1 pour désactiver l'affichage, 2 pour désactiver les points d'arrêt)" << endl;
    string saisie;
    cin >> saisie;

    // Algorithme de recherche de solution
    while(numGeneration < nbGenerationMax) {

        if(saisie != "1") {
            cout << "Génération n°" << numGeneration << endl;
            if(saisie == "2") {
                cout << "Appuyez sur entrée pour continuer. (1 pour désactiver l'affichage, 2 pour désactiver les points d'arrêt)" << endl;
                cin >> saisie;
            }
        }

        if(numGeneration == 0) {
            // Génération de P solutions composées de M mouvements aléatoires
            ranges::generate(generationCourante, [&]() {
                return Solution(instanceInitiale, nbMutationParGen);
            });
        }
        else {
            // Croisement des solutions de la génération courante pour créer une nouvelle génération

            numGeneration++;

            for(int i = 0; i < nbSolutionParGen; i += 2) {

                Solution &premierParent = generationCourante[i];
                Solution &deuxiemeParent = generationCourante[i+1];

                if(saisie != "1") {
                    cout << "Croisement de la solution n°" << i << " avec " << i+1 << ":" << endl;
                    cout << "Parent 1 : ";
                    premierParent.afficherSolution();

                    cout << "Parent 2 :";
                    deuxiemeParent.afficherSolution();
                }

                // Génération d'un nombre aléatoire pour déterminer à quel
                // endroit on souhaite "couper" pour le croisement
                int min = static_cast<int>(0.3 * nbMutationParGen);
                int max = static_cast<int>(0.7 * nbMutationParGen);
                uniform_int_distribution<int> dis(min, max); // Distribution uniforme entre min et max

                unsigned int separation = dis(gen);

                // Création de la liste des mouvements du premier enfant

                // Initialisation de la liste pré-remplie avec les premiers mouvements du premier parent
                vector<Mouvement> mvmtsPremierEnfant(
                    premierParent.obtenirListeMouvements().begin(),
                    premierParent.obtenirListeMouvements().begin() + separation);

                // Ajout des derniers mouvements du deuxième parent à la liste
                mvmtsPremierEnfant.insert(mvmtsPremierEnfant.end(),
                    deuxiemeParent.obtenirListeMouvements().begin() + separation,
                    deuxiemeParent.obtenirListeMouvements().end());


                // Création de la liste des mouvements du deuxième enfant

                // Initialisation de la liste pré-remplie avec les premiers mouvements du deuxième parent
                vector<Mouvement> mvmtsDeuxiemeEnfant(
                    deuxiemeParent.obtenirListeMouvements().begin(),
                    deuxiemeParent.obtenirListeMouvements().begin() + separation);

                // Ajout des derniers mouvements du premier parent à la liste
                mvmtsDeuxiemeEnfant.insert(mvmtsDeuxiemeEnfant.end(),
                    premierParent.obtenirListeMouvements().begin() + separation,
                    premierParent.obtenirListeMouvements().end());

                Solution premierEnfant(instanceInitiale, mvmtsPremierEnfant);
                Solution deuxiemeEnfant(instanceInitiale, mvmtsDeuxiemeEnfant);

                generationCourante.push_back(premierEnfant);
                generationCourante.push_back(deuxiemeEnfant);

                if(saisie != "1") {
                    cout << "Enfant 1 : ";
                    premierEnfant.afficherSolution();

                    cout << "Enfant 2 :";
                    deuxiemeEnfant.afficherSolution();

                    if(saisie == "2") {
                        cout << "Appuyez sur entrée pour continuer. (1 pour désactiver l'affichage, 2 pour désactiver les points d'arrêt)" << endl;
                        cin >> saisie;
                    }
                }
            }

        }

        // Calcul des evaluations des solutions (on les stocke pour la suite de l'algo)


        if(saisie != "1") {
            cout << "Évaluation des solutions." << endl;
            if(saisie == "2") {
                cout << "Appuyez sur entrée pour continuer. (1 pour désactiver l'affichage, 2 pour désactiver les points d'arrêt)" << endl;
                cin >> saisie;
            }
        }
        int numSolution = 0;

        vector<unsigned int> evaluations(nbSolutionParGen);

        for(const Solution& solution : generationCourante) {
            // Pour évaluer une solution on calcule la distance de levenshtein
            // (cad le nb de mouvements restant à faire au minimum)
            // Entre la séquence finale d'une solution et séquence finale de l'instance du problème

            evaluations.push_back(DistanceLevenshtein::calculerDistanceLevenshtein(
                solution.obtenirListeSequences().back(), instanceInitiale.obtenirTerminale()));

            numSolution++;
            if(saisie != "1") {
                cout << "Solution n°" << numSolution << " : " << evaluations.back();
            }

            // Si on a trouvé une solution allant de S à T
            // Cette solution devient la meilleure solution
            if(evaluations.back() == 0) {
                nbMutationParGen --;
                numGeneration = 0;

                meilleureSolution_ = solution;

                if(saisie != "1") {
                    cout << "Meilleure solution trouvée." << endl;
                }
            }
        }

        // Sélection des meilleures solutions pour la génération future

        //Coder la sélection par tournoi (actuellement on prend les Solutions côte à côte)

        if(saisie != "1") {
            cout << "Sélection par tournoi des meilleures solutions." << endl;
            if(saisie == "2") {
                cout << "Appuyez sur entrée pour continuer. (1 pour désactiver l'affichage, 2 pour désactiver les points d'arrêt)" << endl;
                cin >> saisie;
            }
        }
        if(saisie != "1") {
            cout << "Meilleures solutions : " << endl;
        }
        vector<Solution> nouvelleGeneration;
        for(int i = 0; i < nbSolutionParGen; i += 2) {

            Solution &solutionGagnante = (evaluations[i] < evaluations[i + 1]) ?
                                          generationCourante[i] :
                                          generationCourante[i + 1];

            nouvelleGeneration.push_back(solutionGagnante);

            if(saisie != "1") {
                cout << i << " ";
            }
        }

        if(saisie != "1") {
            cout << "Fin de l'itération pour la génération n°" << numGeneration << endl;
            if(saisie == "2") {
                cout << "Appuyez sur entrée pour continuer. (1 pour désactiver l'affichage, 2 pour désactiver les points d'arrêt)" << endl;
                cin >> saisie;
            }
        }
        // La génération courante est remplacée par la nouvelle génération
        // pour la prochaine itération de l'algorithme
        generationCourante = nouvelleGeneration;
    }

    return solutionOptimaleTrouvee;
}
