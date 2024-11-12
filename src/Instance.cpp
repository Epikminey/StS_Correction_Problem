#include "Instance.h"
#include "DistanceLevenshtein.h"

/************************************************
***** Instance : Le constructeur de confort *****
************************************************/
Instance::Instance(const Sequence &source, const Sequence &terminale) {
    source_ = source;
    terminale_ = terminale;
    distance_ = DistanceLevenshtein::calculerDistanceLevenshtein(source, terminale);
}

/***************************************************************************************************
***** ObtenirDistanceLevenshtein : Renvoie le resultat du calcul de la distance de Levenshtein *****
***************************************************************************************************/
unsigned int Instance::obtenirDistanceLevenshtein() const {
    return distance_;
}

const Sequence & Instance::obtenirSource() const {
    return source_;
}

const Sequence & Instance::obtenirTerminale() const {
    return terminale_;
}
