#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "Case.h"

#include <string>
#include <vector>

// Contient tous les mouvements pour modifier une sequence.
class Sequence {
private:
    /*** Attributs ***/
    vector<Case> listeCases_; //La sequence composee d'objets Case

public:
    //***Constructeurs et destructeurs***//

    /************************************************
    ***** Sequence : Le constructeur par defaut *****
    ************************************************/
    Sequence();

    /************************************************
    ***** Sequence : Le constructeur de confort *****
    ************************************************/
    explicit Sequence(string sequence);

    /*************************************************************
    ***** Sequence : Le constructeur de recopie (par defaut) *****
    *************************************************************/
    Sequence(const Sequence &param) = default;

    /**************************************************
    ***** ~Sequence : Le destructeur (par defaut) *****
    **************************************************/
    ~Sequence() = default;

    //***Methodes***//

    /*****************************************************************************
    ***** Operator= : Pour recopier un objet Case sur un objet deja existant *****
    *****************************************************************************/
    Sequence &operator=(const Sequence &param) = default;

    /******************************************************************
    ***** Operator== : Pour savoir si 2 sequences sont identiques *****
    ******************************************************************/
    bool operator==(const Sequence &param) const;

    /************************************************************************************
    ***** ObtenirTailleSequence : Pour connaitre le nombre d'elements dans la liste *****
    ************************************************************************************/
    [[nodiscard]] unsigned int obtenirTailleSequence() const;

    /****************************************************************************
    ***** AfficherCase : Affiche la valeur de la case choisie dans la liste *****
    ****************************************************************************/
    void afficherCase(unsigned int index) const;

    /********************************************************************************
    ***** ObtenirCase : Pour obtenir la valeur de la case choisie dans la liste *****
    ********************************************************************************/
    [[nodiscard]] Case obtenirCase(unsigned int index) const;

    /***************************************************************************
    ***** AfficherSequence : Affiche la composition de la sequence entiere *****
    ***************************************************************************/
    void afficherSequence() const;

    /************************************************************************************************************
    ***** Inverser : Prend et inverse une partie de la sequence, puis change le signe de la partie inversee *****
    ************************************************************************************************************/
    void inverser(unsigned int indexDepart, unsigned int nombreCases);

    /************************************************************************
    ***** Transposer : Deplace une partie de la sequence dans elle-meme *****
    ************************************************************************/
    void transposer(unsigned int indexDepart, unsigned int nombreCases, unsigned int indexDestination);

    /***************************************************************************************************************
    ***** InverserTransposer : Effectue une inversion d'un morceau de la sequence puis deplace ce meme morceau *****
    ***************************************************************************************************************/
    void inverserTransposer(unsigned int indexDepart, unsigned int nombreCases, unsigned int indexDestination);

    /*****************************************************************************************************************
    ***** Dupliquer : Fait une copie d'une partie de la sequence et place cette duplication a cote du bloc copie *****
    *****************************************************************************************************************/
    void dupliquer(unsigned int indexDepart, unsigned int nombreCases);

    /*******************************************************
    ***** Supprimer : Retire une partie de la sequence *****
    *******************************************************/
    void supprimer(unsigned int indexDepart, unsigned int nombreCases);

    /**********************************************************
    ***** ModifierCase : Remplace un element par un autre *****
    **********************************************************/
    void modifierCase(unsigned int index, const string &signeLettre);

    /**********************************************************************************
    ***** AjouterCase : Ajoute un nouvel element dans la liste a l'endroit choisi *****
    **********************************************************************************/
    void ajouterCase(unsigned int index, const string &signeLettre);
};

/************************************************************************************************
***** CalculerDistanceLevenshtein : Calcule la distance de Levenshtein entre deux séquences *****
************************************************************************************************/
unsigned int calculerDistanceLevenshtein(const Sequence &sequence1, const Sequence &sequence2);

#endif //SEQUENCE_H
