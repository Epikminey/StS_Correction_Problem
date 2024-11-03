#include "Instance.h"
#include "DistanceLevenshtein.h"

/************************************************
***** Instance : Le constructeur de confort *****
************************************************/
Instance::Instance(const Sequence& source, const Sequence& terminale) {
    source_ = source;
    terminale_ = terminale;

    //auto distance = DistanceLevenshtein(source, terminale);
    //distance_ = distance.calculerDistance();
}

/***************************************************************************************************
***** ObtenirDistanceLevenshtein : Renvoie le resultat du calcul de la distance de Levenshtein *****
***************************************************************************************************/
unsigned int Instance::obtenirDistanceLevenshtein() const {
    return distance_;
}
