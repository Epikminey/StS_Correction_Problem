#ifndef SOLUTION_H
#define SOLUTION_H

#include "sequence.h"

struct Mouvement {
    string nomMouvement;
    int indexDepart;
    int nombreCases;
    int num3;
    string str2;
};



// Contient les chemins d'évolution d'une sequence
class Solution {
private:
    /*** Attributs ***/
    vector<Sequence> listeSequences_; // Le chemin de sequences
    vector<Mouvement> listeMouvements_; // Les mouvements pour faire le chemin de sequences

public:
    //***Constructeurs et destructeurs***//

    /************************************************
    ***** Solution : Le constructeur par defaut *****
    ************************************************/
    Solution();

    /************************************************
    ***** Solution : Le constructeur de confort *****
    ************************************************/
    explicit Solution(const vector<Mouvement>& mouvements);

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
};

#endif //SOLUTION_H