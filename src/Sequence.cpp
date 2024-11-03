#include "Sequence.h"

#include<iostream>

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
void Sequence::inverser(unsigned int index, unsigned int nombreCases) {

}

/************************************************************************
***** Transposer : Deplace une partie de la sequence dans elle-meme *****
************************************************************************/
void Sequence::transposer(unsigned int index, unsigned int nombreCases, unsigned int indexEmplacement) {

}

/***************************************************************************************************************
***** InverserTransposer : Effectue une inversion d'un morceau de la sequence puis deplace ce meme morceau *****
***************************************************************************************************************/
void Sequence::inverserTransposer(unsigned int index, unsigned int nombreCases, unsigned int indexEmplacement) {

}

/*****************************************************************************************************************
***** Dupliquer : Fait une copie d'une partie de la sequence et place cette duplication a cote du bloc copie *****
*****************************************************************************************************************/
void Sequence::dupliquer(unsigned int index, unsigned int nombreCases) {

}

/*******************************************************
***** Supprimer : Retire une partie de la sequence *****
*******************************************************/
void Sequence::supprimer(const unsigned int index, unsigned int nombreCases) {
    /*if (!listeCases_.empty()) {
        if (index < listeCases_.size())
    }
    monVector.erase(monVector.begin() + 5);*/
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
