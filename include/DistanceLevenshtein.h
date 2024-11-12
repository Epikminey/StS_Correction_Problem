#ifndef DISTANCELEVENSHTEIN_H
#define DISTANCELEVENSHTEIN_H

#include "Sequence.h"

// S'occupe du calcul pour trouver la distance de Levenshtein entre 2 sequences.
// Ce resultat sera utile pour determiner le nombre de mouvements maximum a effectuer pour creer une Solution.

class DistanceLevenshtein {

public:
    /************************************************************************************************
    ***** CalculerDistanceLevenshtein : Calcule la distance de Levenshtein entre deux séquences *****
    ************************************************************************************************/
    static unsigned int calculerDistanceLevenshtein(const Sequence &sequence1, const Sequence &sequence2);
};

#endif //DISTANCELEVENSHTEIN_H
