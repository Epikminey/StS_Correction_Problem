#ifndef ALGORITHME_H
#define ALGORITHME_H

#include "Solution.h"

class Algorithme {
private:
    /*** Attributs ***/
    Instance instance_; // L'instance du problème que l'on souhaite résoudre
    Solution meilleureSolution_; // Le chemin de sequences optimal
    std::vector<Solution> listeSolutions_; // La population de solutions
    unsigned int nombreMouvements_; // Les mouvements pour faire le chemin de sequences optimal

public:
    //***Constructeurs et destructeurs***//

    // On supprime le constructeur par defaut
    Algorithme() = delete;

    /**************************************************
    ***** Algorithme : Le constructeur de confort *****
    **************************************************/
    explicit Algorithme(const Instance &instance);

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

    static std::pair<std::vector<Mouvement>, std::vector<Mouvement> > croisement(
        const std::vector<Mouvement> &mouvementsParent1, const std::vector<Mouvement> &mouvementsParent2);

    static std::vector<Solution> selectionParTournoi(const std::vector<Solution> &generationCourante,
                                                     unsigned int nbSolutionParGen);

    /*****************************************************************************************************
    ***** rechercheSolution : Exécute l'algorithme de recherche de la solution optimale au problème. *****
    *****************************************************************************************************/
    bool rechercheSolution(unsigned int nbGenerationMax, float tauxMutation, unsigned int nbMutationParGen,
                           unsigned int nbSolutionParGen, bool affichageDetaille);
};

#endif //ALGORITHME_H
