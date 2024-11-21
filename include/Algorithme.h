#ifndef ALGORITHME_H
#define ALGORITHME_H


#include "Instance.h"
#include "Solution.h"
#include "Algorithme.h"
#include "DistanceLevenshtein.h"

#include <random>
#include <iostream>



using namespace std;

class Algorithme {
private:
    /*** Attributs ***/
    Instance instance_; // L'instance du problème que l'on souhaite résoudre
    Solution meilleureSolution_; // Le chemin de sequences
    unsigned int nombreMouvements_; // Les mouvements pour faire le chemin de sequences

public:
    //***Constructeurs et destructeurs***//

    // On supprime le constructeur par defaut
    Algorithme() = delete;

    /************************************************
    ***** Solution : Le constructeur de confort *****
    ************************************************/
    explicit Algorithme(const Instance& instance, unsigned int nombreMutations);

    // On supprime le constructeur de recopie
    Algorithme(const Algorithme &param) = delete;

    /**************************************************
    ***** ~Solution : Le destructeur (par defaut) *****
    **************************************************/
    ~Algorithme() = default;

    //***Methodes***//

    // On supprime l'operateur =
    Algorithme &operator=(const Algorithme &param) = delete;

    void afficherNombreMouvements() const;

    void afficherMeilleureSolution() const;

    /*****************************************************************************************************
    ***** rechercheSolution : Exécute l'algorithme de recherche de la solution optimale au problème. *****
    *****************************************************************************************************/
    bool rechercheSolution(unsigned int nbGenerationMax, float tauxMutation, unsigned int nbMutationParGen, unsigned int nbSolutionParGen);
    // Param : nb génération, taux de mutation, nb mutation par génération, nb solutions par génération (12/16/20)
    // On supprime la moitié, et on fait se reproduire le reste -> sélection par tournoi
    // Aléatoire qui décider où couper pour le croisement
};

#endif //ALGORITHME_H
