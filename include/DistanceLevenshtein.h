#ifndef DISTANCELEVENSHTEIN_H
#define DISTANCELEVENSHTEIN_H

#include "Sequence.h"

// S'occupe du calcul pour trouver la distance de Levenshtein entre 2 sequences.
// Ce resultat sera utile pour determiner le nombre de mouvements maximum a effectuer pour creer une Solution.
class DistanceLevenshtein {
private:
    unsigned int distanceDeLevenshtein_; // Le resultat du calcul: la distance de Levenshtein

public:
    // On supprime le constructeur par defaut
    DistanceLevenshtein() = delete;

    /******************************************************************************************************************
    ***** DistanceLevenshtein : Le constructeur de confort calculant la distance de Levenshtein entre 2 séquences *****
    ******************************************************************************************************************/
    DistanceLevenshtein(const Sequence &sequence1, const Sequence &sequence2);

    // On supprime le constructeur de recopie
    DistanceLevenshtein(const DistanceLevenshtein &Param) = delete;

    /*************************************************************
    ***** ~DistanceLevenshtein : Le destructeur (par defaut) *****
    *************************************************************/
    ~DistanceLevenshtein() = default;

    // On supprime l'operateur =
    DistanceLevenshtein &operator=(const DistanceLevenshtein &param) = delete;

    /****************************************************************************************************
    ***** ObtenirDistanceLevenshtein : Pour obtenir la distance de Levenshtein entre deux séquences *****
    ****************************************************************************************************/
    [[nodiscard]] unsigned int obtenirDistanceLevenshtein() const;
};

#endif //DISTANCELEVENSHTEIN_H
