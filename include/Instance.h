#ifndef INSTANCE_H
#define INSTANCE_H

#include "Sequence.h"

// Contient les informations importantes pour lancer l'algorithme principal.
class Instance {
private:
    /*** Attributs ***/
    Sequence source_;
    Sequence terminale_;
    unsigned int distance_;

public:
    //***Constructeurs et destructeurs***//

    // On supprime le constructeur par defaut
    Instance() = delete;

    /************************************************
    ***** Instance : Le constructeur de confort *****
    ************************************************/
    Instance(const Sequence& source, const Sequence& terminale);

    /*************************************************************
    ***** Instance : Le constructeur de recopie (par defaut) *****
    *************************************************************/
    Instance(const Instance &Param) = default;

    //***Methodes***//

    /*********************************************************************************
    ***** Operator= : Pour recopier un objet Instance sur un objet deja existant *****
    *********************************************************************************/
    Instance &operator=(const Instance &Param) = default;

    /***************************************************************************************************
    ***** ObtenirDistanceLevenshtein : Renvoie le resultat du calcul de la distance de Levenshtein *****
    ***************************************************************************************************/
    [[nodiscard]] unsigned int obtenirDistanceLevenshtein() const;

    /********************************************************
    ***** ObtenirSource : Renvoie la sequence d'origine *****
    ********************************************************/
    [[nodiscard]] Sequence obtenirSource() const;

    /*************************************************************
    ***** ObtenirTerminale : Renvoie la sequence a atteindre *****
    *************************************************************/
    [[nodiscard]] Sequence obtenirTerminale() const;
};

#endif //INSTANCE_H
