#ifndef SOLUTION_H
#define SOLUTION_H

#include "sequence.h"

#include <iostream>

using namespace std;

struct Mouvement {
    string nomMouvement;
    int indexDepart;
    int nombreCases;
    int idMouvement;
    string str2;
};

//!!!!! Ca peut optimiser l'algo d'utiliser une enum plutôt que des chaines pour les noms des mouvements
/*
enum Mouvements {
    INVERSION = 1,
    TRANSPOSITION = 2,
    INVERSION_TRANSPOSEE = 3,
    DUPLICATION = 4,
    PERTE = 5,
    SUBSTITUTION = 6,
    AJOUT = 7
};*/




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


    /********************************************************************************
    ***** AfficherSolution : Affiche la solution avec l'ensemble des mouvements *****
    *****                    de cette solution.                                 *****
    ********************************************************************************/
    void afficherSolution() const;


private:
    /********************************************************************************
    ***** AfficherSolution : Fonction utile à afficherSolution                  *****
    *****                    permet d'améliorer la lisibilité du code           *****
    ********************************************************************************/
    void afficherSolution_afficherMouvement(const Mouvement & mouvement,
        char delimiteur, char symbole, unsigned int longueurSequence) const;
};

#endif //SOLUTION_H