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

    // On supprime le constructeur de recopie
    Instance(const Instance &Param) = delete;

    //***Methodes***//

    // On supprime l'operateur ='
    Instance &operator=(const Instance &Param) = delete;

    /***************************************************************************************************
    ***** ObtenirDistanceLevenshtein : Renvoie le resultat du calcul de la distance de Levenshtein *****
    ***************************************************************************************************/
    [[nodiscard]] unsigned int obtenirDistanceLevenshtein() const;

    [[nodiscard]] const Sequence &obtenirSource() const;

    [[nodiscard]] const Sequence &obtenirTerminale() const;
};

#endif //INSTANCE_H
