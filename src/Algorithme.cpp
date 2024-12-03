#include "Algorithme.h"

#include <iostream>
#include <algorithm>
#include <random>

/**************************************************
***** Algorithme : Le constructeur de confort *****
**************************************************/
Algorithme::Algorithme(const Instance &instance): instance_(instance.obtenirSource(), instance.obtenirTerminale()),
                                                  meilleureSolution_(instance, instance.obtenirDistanceLevenshtein()) {
    listeSolutions_ = vector<Solution>();
    nombreMouvements_ = instance.obtenirDistanceLevenshtein();
}

void Algorithme::afficherNombreMouvements() const {
    cout << "Nombre de mouvements : " << nombreMouvements_ << endl;
}

void Algorithme::afficherMeilleureSolution() const {
    cout << "Meilleure solution : " << endl;
    meilleureSolution_.afficherSolution();
}

pair<vector<Mouvement>, vector<Mouvement> > Algorithme::croisement(
    const vector<Mouvement> &mouvementsParent1, const vector<Mouvement> &mouvementsParent2) {
    vector<Mouvement> mouvementsEnfant1;
    vector<Mouvement> mouvementsEnfant2;

    const int min = static_cast<int>(0.3 * static_cast<double>(mouvementsParent1.size()));
    const int max = static_cast<int>(0.7 * static_cast<double>(mouvementsParent1.size()));
    uniform_int_distribution<int> dis(min, max);
    random_device rd;
    mt19937 gen(rd());

    const unsigned int separation = dis(gen);

    for (unsigned int pos = 0; pos < separation; pos++) {
        mouvementsEnfant1.emplace_back(mouvementsParent1[pos]);
        mouvementsEnfant2.emplace_back(mouvementsParent2[pos]);
    }
    for (unsigned int pos = separation; pos < mouvementsParent1.size(); pos++) {
        mouvementsEnfant1.emplace_back(mouvementsParent2[pos]);
        mouvementsEnfant2.emplace_back(mouvementsParent1[pos]);
    }
    return make_pair(mouvementsEnfant1, mouvementsEnfant2);
}

vector<Solution> Algorithme::selectionParTournoi(const vector<Solution> &generationCourante,
                                                      const unsigned int nbSolutionParGen) {
    // On crée une liste pour que chaque individus ne fasse qu'une seule fois partie du tournoi
    vector<unsigned int> listeCroisement(nbSolutionParGen);
    iota(listeCroisement.begin(), listeCroisement.end(), 0);
    // Mélange de la liste
    random_device random_liste;
    mt19937 generation_liste(random_liste());
    ranges::shuffle(listeCroisement, generation_liste);

    auto generationSuivante = vector<Solution>();

    for (unsigned int i = 0; i < listeCroisement.size(); i += 2) {
        const unsigned int indexSolution1 = listeCroisement[i];
        const unsigned int indexSolution2 = listeCroisement[i + 1];

        const unsigned int evaluation1 = generationCourante[indexSolution1].obtenirEvaluation();

        if (const unsigned int evaluation2 = generationCourante[indexSolution2].obtenirEvaluation();
            evaluation1 < evaluation2) {
            generationSuivante.emplace_back(generationCourante[indexSolution1]);
        } else {
            generationSuivante.emplace_back(generationCourante[indexSolution2]);
        }
    }

    return generationSuivante;
}


/*****************************************************************************************************
***** rechercheSolution : Exécute l'algorithme de recherche de la solution optimale au problème. *****
*****************************************************************************************************/
bool Algorithme::rechercheSolution(const unsigned int nbGenerationMax, const float tauxMutation,
                                   const unsigned int nbMutationParGen, const unsigned int nbSolutionParGen,
                                   const bool affichageDetaille) {
    // Définitions des variables utiles à la recherche de solution
    bool solutionOptimaleTrouvee = false;
    unsigned int numGeneration = 0;

    cout << "Début de la recherche de solution." << endl;
    cout << "Séquence de départ S : " << endl;
    instance_.obtenirSource().afficherSequence();
    cout << "Séquence d'arrivée T : " << endl;
    instance_.obtenirTerminale().afficherSequence();

    cout << "Distance levenshtein (valeur optimale à atteindre: " << nombreMouvements_ << ")" << endl;

    // Algorithme de recherche de solution
    while (numGeneration < nbGenerationMax) {
        if (affichageDetaille) {
            cout << "Génération n°" << numGeneration << endl;
        }

        if (numGeneration == 0) {
            // Initialisation de la premiere generation de solutions avec nbSolutionParGen solutions aléatoires
            for (unsigned int i = 0; i < nbSolutionParGen; i++) {
                listeSolutions_.emplace_back(Solution(instance_, nombreMouvements_));
            }


            // On evalue chaque nouvel individu
            for (Solution &solution: listeSolutions_) {
                solution.calculerEvaluation(instance_.obtenirTerminale());
                if (const unsigned int evaluation = solution.obtenirEvaluation();
                    evaluation == 0) {
                    meilleureSolution_ = solution;
                    nombreMouvements_--;
                    solutionOptimaleTrouvee = true;
                    break;
                }
            }

        } else {
            // On rajoute la partie de la population manquante (après sélection par tournoi)

            // On crée une liste pour croiser les individus gagnants du tournoi aléatoirement entre eux
            vector<unsigned int> listeCroisement(nbSolutionParGen / 2);
            iota(listeCroisement.begin(), listeCroisement.end(), 0);
            // Mélange de la liste
            random_device random;
            mt19937 generation_liste(random());
            ranges::shuffle(listeCroisement, generation_liste);

            // Croisement des solutions gagnantes du tournoi pour reproduire des enfants et retrouver le nombre de solutions initial
            int compteur = 0;
            for (unsigned int i = 0; i < listeCroisement.size(); i += 2) {
                auto [mouvementsEnfant1, mouvementsEnfant2] = croisement(
                    listeSolutions_[listeCroisement[i]].obtenirListeMouvements(),
                    listeSolutions_[listeCroisement[i + 1]].obtenirListeMouvements());


                listeSolutions_.emplace_back(instance_, mouvementsEnfant1);
                listeSolutions_.emplace_back(instance_, mouvementsEnfant2);

                compteur++;
            }

            // Mutation des solutions venant d'être créées
            for (Solution &solution: listeSolutions_) {
                for (unsigned int i = 0; i < nbMutationParGen; i++) {
                    mt19937 gen(random());
                    const int max_index = static_cast<int>(listeSolutions_.size()) - 1;
                    uniform_int_distribution<> dis(0, max_index);
                    const unsigned int indexSolution = dis(gen);

                    // On applique toujours une seule mutation par solution
                    listeSolutions_[indexSolution].Mutation(tauxMutation, 1);
                }
            }


            // On evalue les nouveaux individus uniquement
            const auto numSolution = listeSolutions_.size() / 2;
            for (unsigned int i = numSolution; i < listeSolutions_.size(); i++) {
                Solution &solution = listeSolutions_[i];
                solution.calculerEvaluation(instance_.obtenirTerminale());
                const unsigned int evaluation = solution.obtenirEvaluation();
                if (evaluation == 0) {
                    meilleureSolution_ = solution;
                    nombreMouvements_--;
                    solutionOptimaleTrouvee = true;
                    break;
                }

                if (affichageDetaille) {
                    cout << "Solution n°" << i + 1 << " : " << evaluation << endl;
                }
            }
        }

        // Sélection des meilleures solutions pour la génération future
        if (affichageDetaille) {
            cout << "Sélection par tournoi des meilleures solutions." << endl;
        }

        listeSolutions_ = selectionParTournoi(listeSolutions_, nbSolutionParGen);

        //if (affichageDetaille) {
            cout << "Fin de l'itération pour la génération n°" << numGeneration << "; " << listeSolutions_.size() << endl;
        //}

        numGeneration++;

        if (solutionOptimaleTrouvee) {
            cout << "Meilleure solution trouvée !" << endl;
            numGeneration = 0;
        }
    }
    return solutionOptimaleTrouvee;
}
