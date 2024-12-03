#include "Algorithme.h"

#include <iostream>
#include <algorithm>
#include <random>

/**************************************************
***** Algorithme : Le constructeur de confort *****
**************************************************/
Algorithme::Algorithme(const Instance &instance): instance_(instance.obtenirSource(), instance.obtenirTerminale()),
                                                  meilleureSolution_(instance, instance.obtenirDistanceLevenshtein()) {
    listeSolutions_ = std::vector<Solution>();
    nombreMouvements_ = instance.obtenirDistanceLevenshtein();
}

void Algorithme::afficherNombreMouvements() const {
    std::cout << "Nombre de mouvements : " << nombreMouvements_ << std::endl;
}

void Algorithme::afficherMeilleureSolution() const {
    std::cout << "Meilleure solution : " << std::endl;
    meilleureSolution_.afficherSolution();
}

std::pair<std::vector<Mouvement>, std::vector<Mouvement> > Algorithme::croisement(
    const std::vector<Mouvement> &mouvementsParent1, const std::vector<Mouvement> &mouvementsParent2) {
    std::vector<Mouvement> mouvementsEnfant1;
    std::vector<Mouvement> mouvementsEnfant2;

    const int min = static_cast<int>(0.3 * static_cast<double>(mouvementsParent1.size()));
    const int max = static_cast<int>(0.7 * static_cast<double>(mouvementsParent1.size()));
    std::uniform_int_distribution<int> dis(min, max);
    std::random_device rd;
    std::mt19937 gen(rd());

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

std::vector<Solution> Algorithme::selectionParTournoi(const std::vector<Solution> &generationCourante,
                                                      const unsigned int nbSolutionParGen) {
    // On crée une liste pour que chaque individus ne fasse qu'une seule fois partie du tournoi
    std::vector<unsigned int> listeCroisement(nbSolutionParGen);
    iota(listeCroisement.begin(), listeCroisement.end(), 0);
    // Mélange de la liste
    std::random_device random_liste;
    std::mt19937 generation_liste(random_liste());
    std::ranges::shuffle(listeCroisement, generation_liste);

    auto generationSuivante = std::vector<Solution>();

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

    std::cout << "Debut de la recherche de solution." << std::endl;
    std::cout << "Sequence de depart S : " << std::endl;
    instance_.obtenirSource().afficherSequence();
    std::cout << "Sequence d'arrivee T : " << std::endl;
    instance_.obtenirTerminale().afficherSequence();

    std::cout << "Distance levenshtein (valeur optimale a atteindre: " << nombreMouvements_ << ")" << std::endl;

    for (unsigned int i = 0; i < nbSolutionParGen; i++) {
        listeSolutions_.emplace_back(instance_, nombreMouvements_);
    }

    // Algorithme de recherche de solution
    while (numGeneration < nbGenerationMax) {
        if (affichageDetaille) {
            std::cout << "Génération n°" << numGeneration << std::endl;
        }

        if (numGeneration == 0) {
            // Initialisation de la premiere generation de solutions avec nbSolutionParGen solutions aléatoires
            for (unsigned int i = 0; i < nbSolutionParGen; i++) {
                listeSolutions_.emplace_back(instance_, nombreMouvements_);
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
            std::vector<unsigned int> listeCroisement(nbSolutionParGen / 2);
            iota(listeCroisement.begin(), listeCroisement.end(), 0);
            // Mélange de la liste
            std::random_device random_liste;
            std::mt19937 generation_liste(random_liste());
            std::ranges::shuffle(listeCroisement, generation_liste);

            // Croisement des solutions gagnantes du tournoi pour reproduire des enfants et retrouver le nombre de solutions initial
            for (unsigned int i = 0; i < listeCroisement.size(); i += 2) {
                auto [mouvementsEnfant1, mouvementsEnfant2] = croisement(
                    listeSolutions_[listeCroisement[i]].obtenirListeMouvements(),
                    listeSolutions_[listeCroisement[i + 1]].obtenirListeMouvements());

                if (affichageDetaille) {
                    std::cout << "Croisement de la solution n°" << listeCroisement[i] << " avec " << listeCroisement[
                                i + 1]
                            << ":" << std::endl;
                    std::cout << "Parent 1 : ";
                    //listeSolutions_[listeCroisement[i]].afficherSolutionSimplifiee();

                    std::cout << "Parent 2 :";
                    //listeSolutions_[listeCroisement[i + 1]].afficherSolutionSimplifiee();
                }

                listeSolutions_.emplace_back(instance_, mouvementsEnfant1);
                listeSolutions_.emplace_back(instance_, mouvementsEnfant2);

                if (affichageDetaille) {
                    std::cout << "Enfant 1 : ";
                    listeSolutions_[listeCroisement[listeCroisement.size() + i]].afficherSolutionSimplifiee();

                    std::cout << "Enfant 2 :";
                    listeSolutions_[listeCroisement[listeCroisement.size() + i + 1]].afficherSolutionSimplifiee();
                }
            }

            // Mutation des solutions venant d'être créées
            /*for (Solution &solution: listeSolutions_) {
                for (unsigned int i = 0; i < nbMutationParGen; i++) {
                    const unsigned int indexSolution = rand() % listeSolutions_.size();
                    listeSolutions_[indexSolution].mutation(tauxMutation);
                }
            }*/


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
                    std::cout << "Solution n°" << i + 1 << " : " << evaluation << std::endl;
                }
            }
        }

        // Sélection des meilleures solutions pour la génération future
        if (affichageDetaille) {
            std::cout << "Sélection par tournoi des meilleures solutions." << std::endl;
        }

        listeSolutions_ = selectionParTournoi(listeSolutions_, nbSolutionParGen);

        if (affichageDetaille) {
            std::cout << std::endl << "Fin de l'itération pour la génération n°" << numGeneration << std::endl;
        }

        numGeneration++;

        if (solutionOptimaleTrouvee) {
            numGeneration = 0;
        }
    }
    return solutionOptimaleTrouvee;
}
