#include "Sequence.h"

#include <algorithm>
#include <iostream>

/************************************************
***** Sequence : Le constructeur par defaut *****
************************************************/
Sequence::Sequence() {
    listeCases_ = vector<Case>();
}

/************************************************
***** Sequence : Le constructeur de confort *****
************************************************/
Sequence::Sequence(string sequence) {
    for (unsigned int boucle = 0; boucle < sequence.size(); boucle++) {
        if (boucle % 2 == 0) {
            try {
                listeCases_.emplace_back(sequence[boucle], sequence[boucle + 1]);
            } catch (const runtime_error &erreur) {
                cout << "Erreur capturée : " << erreur.what() << std::endl;
            }
        }
    }
}

/************************************************************************************
***** ObtenirTailleSequence : Pour connaitre le nombre d'elements dans la liste *****
************************************************************************************/
unsigned int Sequence::obtenirTailleSequence() const {
    return listeCases_.size();
}

/****************************************************************************
***** AfficherCase : Affiche la valeur de la case choisie dans la liste *****
****************************************************************************/
void Sequence::afficherCase(const unsigned int index) const {
    listeCases_[index].afficherCase();
}

/********************************************************************************
***** ObtenirCase : Pour obtenir la valeur de la case choisie dans la liste *****
********************************************************************************/
const Case &Sequence::obtenirCase(const unsigned int index) const {
    if (index >= listeCases_.size()) {
        throw out_of_range("Index hors limites");
    }
    return listeCases_[index];
}

/***************************************************************************
***** AfficherSequence : Affiche la composition de la sequence entiere *****
***************************************************************************/
void Sequence::afficherSequence() const {
    for (unsigned int boucle = 0; boucle < listeCases_.size(); boucle++) {
        afficherCase(boucle);
    }
    cout << endl;
}

/************************************************************************************************************
***** Inverser : Prend et inverse une partie de la sequence, puis change le signe de la partie inversee *****
************************************************************************************************************/
void Sequence::inverser(const unsigned int indexDepart, const unsigned int nombreCases) {
    if (!listeCases_.empty() && indexDepart < listeCases_.size() && nombreCases != 0) {
        if (indexDepart + nombreCases < listeCases_.size()) {
            reverse(listeCases_.begin() + indexDepart, listeCases_.begin() + indexDepart + nombreCases);
            for (unsigned int boucle = indexDepart; boucle < indexDepart + nombreCases; boucle++) {
                listeCases_[boucle].modifierSigne();
            }
        } else {
            reverse(listeCases_.begin() + indexDepart, listeCases_.end());
            for (auto boucle = indexDepart; boucle < listeCases_.size(); ++boucle) {
                listeCases_[boucle].modifierSigne();
            }
        }
    }
}

/************************************************************************
***** Transposer : Deplace une partie de la sequence dans elle-meme *****
************************************************************************/
void Sequence::transposer(const unsigned int indexDepart, const unsigned int nombreCases,
                          const unsigned int indexDestination) {
    if (!listeCases_.empty() && indexDepart < listeCases_.size() && indexDepart != indexDestination && nombreCases !=
        0) {
        if ((indexDestination > indexDepart && indexDepart + nombreCases + 1 < listeCases_.size()) ||
            (indexDestination < indexDepart && indexDepart != 0)) {
            if (indexDestination > indexDepart) {
                // Déplacer vers un index supérieur
                std::rotate(listeCases_.begin() + indexDepart, listeCases_.begin() + indexDepart + nombreCases,
                            listeCases_.begin() + indexDestination + nombreCases);
            } else {
                // Déplacer vers un index inférieur
                std::rotate(listeCases_.begin() + indexDestination, listeCases_.begin() + indexDepart,
                            listeCases_.begin() + indexDepart + nombreCases);
            }
        }
    }
}

/***************************************************************************************************************
***** InverserTransposer : Effectue une inversion d'un morceau de la sequence puis deplace ce meme morceau *****
***************************************************************************************************************/
void Sequence::inverserTransposer(const unsigned int indexDepart, const unsigned int nombreCases,
                                  const unsigned int indexDestination) {
    inverser(indexDepart, nombreCases);
    transposer(indexDepart, nombreCases, indexDestination);
}

/*****************************************************************************************************************
***** Dupliquer : Fait une copie d'une partie de la sequence et place cette duplication a cote du bloc copie *****
*****************************************************************************************************************/
void Sequence::dupliquer(const unsigned int indexDepart, const unsigned int nombreCases) {
    if (!listeCases_.empty() && indexDepart < listeCases_.size() && nombreCases != 0) {
        if (indexDepart + nombreCases + 1 < listeCases_.size()) {
            for (unsigned int boucle = 0; boucle < nombreCases; boucle++) {
                listeCases_.emplace(listeCases_.begin() + indexDepart + nombreCases,
                                    listeCases_[indexDepart + nombreCases - 1 - boucle]);
            }
        } else {
            const unsigned int surplus = indexDepart + nombreCases - 1 - listeCases_.size();
            for (unsigned int boucle = 0; boucle < nombreCases - surplus; boucle++) {
                listeCases_.emplace_back(listeCases_[indexDepart + boucle - 1]);
            }
        }
    }
}

/*******************************************************
***** Supprimer : Retire une partie de la sequence *****
*******************************************************/
void Sequence::supprimer(const unsigned int indexDepart, const unsigned int nombreCases) {
    if (!listeCases_.empty() && indexDepart < listeCases_.size() && nombreCases != 0) {
        if (indexDepart + nombreCases < listeCases_.size()) {
            listeCases_.erase(listeCases_.begin() + indexDepart, listeCases_.begin() + indexDepart + nombreCases);
        } else {
            listeCases_.erase(listeCases_.begin() + indexDepart, listeCases_.end());
        }
    }
}

/**********************************************************
***** ModifierCase : Remplace un element par un autre *****
**********************************************************/
void Sequence::modifierCase(const unsigned int index, const string &signeLettre) {
    if (index < listeCases_.size()) {
        if (signeLettre.size() == 2) {
            listeCases_[index].modifierCase(signeLettre[0], signeLettre[1]);
        }
    } else {
        if (signeLettre.size() == 2) {
            listeCases_[listeCases_.size() - 1] = Case(signeLettre[0], signeLettre[1]);
        }
    }
}

/**********************************************************************************
***** AjouterCase : Ajoute un nouvel element dans la liste a l'endroit choisi *****
**********************************************************************************/
void Sequence::ajouterCase(const unsigned int index, const string &signeLettre) {
    if (index < listeCases_.size()) {
        if (signeLettre.size() == 2) {
            listeCases_.emplace(listeCases_.begin() + index, signeLettre[0], signeLettre[1]);
        }
    } else {
        if (signeLettre.size() == 2) {
            listeCases_.emplace(listeCases_.end(), signeLettre[0], signeLettre[1]);
        }
    }
}
