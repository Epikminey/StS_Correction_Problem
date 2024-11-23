#include "Instance.h"

/************************************************
***** Instance : Le constructeur de confort *****
************************************************/
Instance::Instance(const Sequence &source, const Sequence &terminale) {
    source_ = source;
    terminale_ = terminale;
    distance_ = calculerDistanceLevenshtein(source, terminale);
}

/***************************************************************************************************
***** ObtenirDistanceLevenshtein : Renvoie le resultat du calcul de la distance de Levenshtein *****
***************************************************************************************************/
unsigned int Instance::obtenirDistanceLevenshtein() const {
    return distance_;
}

/********************************************************
***** ObtenirSource : Renvoie la sequence d'origine *****
********************************************************/
Sequence Instance::obtenirSource() const {
    return source_;
}

/*************************************************************
***** ObtenirTerminale : Renvoie la sequence a atteindre *****
*************************************************************/
Sequence Instance::obtenirTerminale() const {
    return terminale_;
}
