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

Solution & Algorithme::obtenirMeilleureSolution() {
    return meilleureSolution_;
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

    cout << "Debut de la recherche de solution." << endl;
    cout << "Sequence de depart S : " << endl;
    instance_.obtenirSource().afficherSequence();
    cout << "Sequence d'arrivee T : " << endl;
    instance_.obtenirTerminale().afficherSequence();

    cout << "Distance levenshtein (valeur optimale a atteindre: " << nombreMouvements_ << ")" << endl << endl << endl;

    // Algorithme de recherche de solution
    while (numGeneration < nbGenerationMax && nombreMouvements_ > 0) {

        if(affichageDetaille && numGeneration%100 == 0)
            cout << "Generation numero " << numGeneration << " avec " << nombreMouvements_ << " mouvements." << endl;

        if (numGeneration == 0) {

            if(affichageDetaille && numGeneration%100 == 0)
                cout << "Generation de " << nbSolutionParGen << " solutions aleatoires." << endl;
            // Initialisation de la premiere generation de solutions avec nbSolutionParGen solutions aléatoires
            for (unsigned int i = 0; i < nbSolutionParGen; i++) {
                listeSolutions_.emplace_back(instance_, nombreMouvements_);
            }

            if(affichageDetaille && numGeneration%100 == 0)
                cout << "Evaluation des solutions." << endl;

            // On evalue chaque nouvel individu
            for (Solution &solution: listeSolutions_) {
                solution.calculerEvaluation(instance_.obtenirTerminale());
                if (const unsigned int evaluation = solution.obtenirEvaluation();
                    evaluation == 0) {
                    if(affichageDetaille)
                        cout << "Meilleure solution trouvee pour " << nombreMouvements_ << " mouvements!" << endl;
                    meilleureSolution_ = solution;
                    nombreMouvements_--;
                    solutionOptimaleTrouvee = true;
                    listeSolutions_.clear();
                    break;
                }
            }

        } else {
            // On rajoute la partie de la population manquante (après sélection par tournoi)

            if(affichageDetaille && numGeneration%100 == 0)
                cout << "Croisement des solutions." << endl;

            // On crée une liste pour croiser les individus gagnants du tournoi aléatoirement entre eux
            vector<unsigned int> listeCroisement(nbSolutionParGen / 2);
            iota(listeCroisement.begin(), listeCroisement.end(), 0);
            // Mélange de la liste
            random_device random;
            mt19937 generation_liste(random());
            ranges::shuffle(listeCroisement, generation_liste);

            // Croisement des solutions gagnantes du tournoi pour reproduire des enfants et retrouver le nombre de solutions initial
            for (unsigned int i = 0; i < listeCroisement.size(); i += 2) {
                auto [mouvementsEnfant1, mouvementsEnfant2] = croisement(
                    listeSolutions_[listeCroisement[i]].obtenirListeMouvements(),
                    listeSolutions_[listeCroisement[i + 1]].obtenirListeMouvements());

                listeSolutions_.emplace_back(instance_, mouvementsEnfant1);
                listeSolutions_.emplace_back(instance_, mouvementsEnfant2);
            }

            if(affichageDetaille && numGeneration%100 == 0)
                cout << "Mutations des solutions." << endl;

            // Mutation des solutions venant d'être créées
            for (unsigned int i = 0; i < nbMutationParGen; i++) {
                mt19937 gen(random());
                const int max_index = static_cast<int>(listeSolutions_.size()) - 1;
                uniform_int_distribution<> dis(0, max_index);
                const unsigned int indexSolution = dis(gen);

                // On applique toujours une seule mutation par solution
                listeSolutions_[indexSolution].Mutation(tauxMutation, 1);
            }

            if(affichageDetaille && numGeneration%100 == 0)
                cout << "Evaluation des solutions." << endl;

            // On evalue les nouveaux individus uniquement
            const auto numSolution = listeSolutions_.size() / 2;
            for (unsigned int i = numSolution; i < listeSolutions_.size(); i++) {
                Solution &solution = listeSolutions_[i];
                solution.calculerEvaluation(instance_.obtenirTerminale());
                if (const unsigned int evaluation = solution.obtenirEvaluation(); evaluation == 0) {
                    if(affichageDetaille)
                        cout << "Meilleure solution trouvee pour " << nombreMouvements_ << " mouvements!" << endl;
                    meilleureSolution_ = solution;
                    nombreMouvements_--;
                    solutionOptimaleTrouvee = true;
                    break;
                }
            }
        }

        // Sélection des meilleures solutions pour la génération future
        if(affichageDetaille && numGeneration%100 == 0)
            cout << "Selection par tournoi des meilleures solutions." << endl;

        listeSolutions_ = selectionParTournoi(listeSolutions_, nbSolutionParGen);

        numGeneration++;

        if (solutionOptimaleTrouvee) {
            if(affichageDetaille)
                cout << "Meilleure solution trouvee pour " << nombreMouvements_ << " mouvements!" << endl;

            numGeneration = 0;
            solutionOptimaleTrouvee = false;
            listeSolutions_.clear();
        }

        if(affichageDetaille && numGeneration%100 == 0)
            cout << endl;
    }

    return !meilleureSolution_.obtenirListeMouvements().empty();
}
