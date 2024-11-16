#ifndef SOLUTION_H
#define SOLUTION_H

#include "Instance.h"
#include "sequence.h"

struct Mouvement {
    unsigned int idMouvement;
    unsigned int indexDepart;
    unsigned int nombreCases;
    unsigned int indexDestination;
    string nomCase;
};

enum Mouvements {
    INVERSION = 1,
    TRANSPOSITION = 2,
    INVERSION_TRANSPOSEE = 3,
    DUPLICATION = 4,
    SUPPRESSION = 5,
    SUBSTITUTION = 6,
    AJOUT = 7
};


// Contient les chemins d'évolution d'une sequence
class Solution {
private:
    /*** Attributs ***/
    vector<Sequence> listeSequences_; // Le chemin de sequences
    vector<Mouvement> listeMouvements_; // Les mouvements pour faire le chemin de sequences

public:
    //***Constructeurs et destructeurs***//

    // On supprime le constructeur par defaut
    Solution() = delete;

    /***************************************************************************
    ***** Solution : Le constructeur de confort avec mouvements aleatoires *****
    ***************************************************************************/
    Solution(const Instance &instance, unsigned int nombreMutations);

    /***********************************************************************************************
    ***** Solution : Le constructeur de confort via une liste de mouvements (apres croisement) *****
    ***********************************************************************************************/
    explicit Solution(const Instance &instance, const vector<Mouvement> &mouvements);

    /*************************************************************
    ***** Solution : Le constructeur de recopie (par defaut) *****
    *************************************************************/
    Solution(const Solution &param) = default;

    /**************************************************
    ***** ~Solution : Le destructeur (par defaut) *****
    **************************************************/
    ~Solution() = default;

    //***Methodes***//

    /*****************************************************************************
    ***** Operator= : Pour recopier un objet Case sur un objet deja existant *****
    *****************************************************************************/
    Solution &operator=(const Solution &param) = default;

    /********************************************************************
    ***** Mutation : Pour modifier un des mouvements de la Solution *****
    ********************************************************************/
    void Mutation(unsigned int index, const Mouvement &mouvement);

    /**********************************************************************************************
    ***** ObtenirDerniereSequence : Pour copier et manipuler la derniere sequence de la liste *****
    **********************************************************************************************/
    [[nodiscard]] Sequence obtenirDerniereSequence() const;

    /****************************************************************************
    ***** ObtenirListeSequences : Pour avoir la suite de sequences modifies *****
    ****************************************************************************/
    [[nodiscard]] vector<Sequence> obtenirListeSequences() const;

    /**********************************************************************************************
    ***** ObtenirListeMouvements : Pour avoir tous les mouvements effectues sur la sequence S *****
    **********************************************************************************************/
    [[nodiscard]] vector<Mouvement> obtenirListeMouvements() const;

    /***************************************************************************************************
    ***** AfficherSolution : Affiche la solution avec l'ensemble des mouvements de cette solution. *****
    ***************************************************************************************************/
    void afficherSolution() const;

    /**********************************************************************************************************
    ***** afficherMouvement : Fonction utile à afficherSolution, permet d'améliorer la lisibilité du code *****
    **********************************************************************************************************/
    static void afficherMouvement(const Mouvement &mouvement, char delimiteur, char symbole,
                                  unsigned int longueurSequence);
};

#endif //SOLUTION_H
