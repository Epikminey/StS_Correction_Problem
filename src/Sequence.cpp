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
                cout << "Erreur capturée : " << erreur.what() << endl;
            }
        }
    }
}

/******************************************************************
***** Operator== : Pour savoir si 2 sequences sont identiques *****
******************************************************************/
bool Sequence::operator==(const Sequence &param) const {
    if (listeCases_.size() != param.listeCases_.size()) {
        return false;
    }

    for (unsigned int boucle = 0; boucle < listeCases_.size(); boucle++) {
        if (listeCases_[boucle] != param.listeCases_[boucle]) {
            return false;
        }
    }

    return true;
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
Case Sequence::obtenirCase(const unsigned int index) const {
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
        // Si la partie à inverser ne dépasse pas la taille de la liste
        if (indexDepart + nombreCases < listeCases_.size()) {
            reverse(listeCases_.begin() + indexDepart, listeCases_.begin() + indexDepart + nombreCases);
            for (unsigned int boucle = indexDepart; boucle < indexDepart + nombreCases; boucle++) {
                listeCases_[boucle].modifierSigne();
            }
        }
        // Si la partie à inverser dépasse la taille de la liste
        else {
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
        // Si la partie à transposer ne dépasse pas la taille de la liste
        if ((indexDestination > indexDepart && indexDepart + nombreCases + 1 < listeCases_.size()) ||
            (indexDestination < indexDepart && indexDepart != 0)) {
            // Déplacer vers un index supérieur
            if (indexDestination > indexDepart) {
                const auto debut = listeCases_.begin() + indexDepart;
                const auto nombre = debut + nombreCases;
                auto fin = listeCases_.begin() + indexDestination + nombreCases;
                if (const unsigned int taille = listeCases_.size(); indexDestination + nombreCases > taille) {
                    fin = listeCases_.begin() + taille;
                }

                rotate(debut, nombre, fin);
            }
            // Déplacer vers un index inférieur
            else {

                const auto debut = listeCases_.begin() + indexDepart;
                auto nombre = debut + nombreCases;
                const auto fin = listeCases_.begin() + indexDestination;
                if (const unsigned int taille = listeCases_.size(); indexDepart + nombreCases > taille) {
                    nombre = listeCases_.begin() + taille;
                }

                rotate(fin, debut, nombre);
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
        // Si la partie à dupliquer ne dépasse pas la taille de la liste
        if (indexDepart + nombreCases + 1 < listeCases_.size()) {
            for (unsigned int boucle = 0; boucle < nombreCases; boucle++) {
                listeCases_.emplace(listeCases_.begin() + indexDepart + nombreCases,
                                    listeCases_[indexDepart + nombreCases - 1 - boucle]);
            }
        }
        // Si la partie à dupliquer dépasse la taille de la liste
        else {
            const unsigned int surplus = indexDepart + nombreCases + 1 - listeCases_.size();
            std::cout << indexDepart + nombreCases + 1 << '\n' << listeCases_.size() << '\n' << surplus << std::endl;
            for (unsigned int boucle = 0; boucle < nombreCases - surplus + 1; boucle++) {
                listeCases_.emplace_back(listeCases_[indexDepart + boucle]);
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
    if(!listeCases_.empty()) {
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
            listeCases_.emplace_back(signeLettre[0], signeLettre[1]);
        }
    }
}

/************************************************************************************************
***** CalculerDistanceLevenshtein : Calcule la distance de Levenshtein entre deux séquences *****
************************************************************************************************/
unsigned int calculerDistanceLevenshtein(const Sequence &sequence1, const Sequence &sequence2) {
    const unsigned int tailleSequence1 = sequence1.obtenirTailleSequence();
    const unsigned int tailleSequence2 = sequence2.obtenirTailleSequence();

    // MatriceDistances est un tableau de longueurChaine1+1 rangées et longueurChaine2+1 colonnes
    // MatriceDistances est indexé à partir de 0, les chaînes à partir de 1
    vector MatriceDistances(tailleSequence1 + 1, vector<int>(tailleSequence2 + 1));
    // Initialisation de la première ligne et de la première colonne du tableau D
    for (int i = 0; i <= tailleSequence1; i++) {
        MatriceDistances[i][0] = i;
    }
    for (int j = 0; j <= tailleSequence2; j++) {
        MatriceDistances[0][j] = j;
    }

    // Calcul des autres valeurs de la matrice MatriceDistances
    for (int ligne = 1; ligne <= tailleSequence1; ligne++) {
        for (int colonne = 1; colonne <= tailleSequence2; colonne++) {
            // On compare 2 cases. Si différentes, alors on ajoute 1 au cout de substitution
            int coutSubstitution = 0;
            const char lettre1 = sequence1.obtenirCase(ligne - 1).lireLettre();
            if (const char lettre2 = sequence2.obtenirCase(colonne - 1).lireLettre(); lettre1 != lettre2) {
                coutSubstitution = 1;
            }
            MatriceDistances[ligne][colonne] =  min(MatriceDistances[ligne - 1][colonne] + 1, // effacement du nouveau caractère de séquence1
                                                min(MatriceDistances[ligne][colonne - 1] + 1, // insertion dans séquence2 du nouveau caractère de séquence1
                                                MatriceDistances[ligne - 1][colonne - 1] + coutSubstitution) // substitution
            );
        }
    }
    // On retourne la distance de Levenshtein qui se trouve à la dernière ligne/colonne de la matrice D
    return MatriceDistances[tailleSequence1][tailleSequence2];
}
