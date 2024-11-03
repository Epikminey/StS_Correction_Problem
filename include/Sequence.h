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
    Sequence(const Sequence &Param) = default;

    /**************************************************
    ***** ~Sequence : Le destructeur (par defaut) *****
    **************************************************/
    ~Sequence() = default;

    //***Methodes***//

    /*****************************************************************************
    ***** Operator= : Pour recopier un objet Case sur un objet deja existant *****
    *****************************************************************************/
    Sequence &operator=(const Sequence &Param) = default;

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
    [[nodiscard]] const Case &obtenirCase(unsigned int index) const;

    /***************************************************************************
    ***** AfficherSequence : Affiche la composition de la sequence entiere *****
    ***************************************************************************/
    void afficherSequence() const;

    /************************************************************************************************************
    ***** Inverser : Prend et inverse une partie de la sequence, puis change le signe de la partie inversee *****
    ************************************************************************************************************/
    void inverser(unsigned int index, unsigned int nombreCases);

    /************************************************************************
    ***** Transposer : Deplace une partie de la sequence dans elle-meme *****
    ************************************************************************/
    void transposer(unsigned int index, unsigned int nombreCases, unsigned int indexEmplacement);

    /***************************************************************************************************************
    ***** InverserTransposer : Effectue une inversion d'un morceau de la sequence puis deplace ce meme morceau *****
    ***************************************************************************************************************/
    void inverserTransposer(unsigned int index, unsigned int nombreCases, unsigned int indexEmplacement);

    /*****************************************************************************************************************
    ***** Dupliquer : Fait une copie d'une partie de la sequence et place cette duplication a cote du bloc copie *****
    *****************************************************************************************************************/
    void dupliquer(unsigned int index, unsigned int nombreCases);

    /*******************************************************
    ***** Supprimer : Retire une partie de la sequence *****
    *******************************************************/
    void supprimer(unsigned int index, unsigned int nombreCases);

    /**********************************************************
    ***** ModifierCase : Remplace un element par un autre *****
    **********************************************************/
    void modifierCase(unsigned int index, const string &signeLettre);

    /**********************************************************************************
    ***** AjouterCase : Ajoute un nouvel element dans la liste a l'endroit choisi *****
    **********************************************************************************/
    void ajouterCase(unsigned int index, const string &signeLettre);
};

#endif //SEQUENCE_H
