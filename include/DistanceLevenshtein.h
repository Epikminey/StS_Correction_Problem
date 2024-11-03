#ifndef DISTANCELEVENSHTEIN_H
#define DISTANCELEVENSHTEIN_H

#include <Sequence.h>

#include <tuple>

using namespace std;

class DistanceLevenshtein {

public:
    /************************************************************************************************
    ***** CalculerDistanceLevenshtein : Calcule la distance de Levenshtein entre deux séquences *****
    ************************************************************************************************/
    static int calculerDistanceLevenshtein(const Sequence &sequence1, const Sequence &sequence2);

};

#endif //DISTANCELEVENSHTEIN_H