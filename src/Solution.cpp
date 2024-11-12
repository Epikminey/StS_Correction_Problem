#include "Solution.h"

#include <random>
#include <bits/random.h>
#include <iostream>

/***************************************************************************
***** Solution : Le constructeur de confort avec mouvements aleatoires *****
***************************************************************************/
Solution::Solution(const Instance &instance, const unsigned int nombreMutations) {
    // On ajoute la premiere sequence, la sequence Source.
    listeSequences_.push_back(instance.obtenirSource());

    // On initialise le generateur de nombre aleatoire
    random_device graine;
    mt19937 generation(graine());

    for (unsigned int boucle = 0; boucle < nombreMutations; ++boucle) {
        uniform_int_distribution<> distrOperation1(0, 6);
        const unsigned int chiffreAleatoire = distrOperation1(generation);

        // Pour obtenir la taille de la sequence precedente
        const unsigned int tailleSequence = listeSequences_.back().obtenirTailleSequence();

        Mouvement mouvement;

        // Switch case pour les differentes valeurs de randomNumber
        switch (chiffreAleatoire) {
            case 0: {
                uniform_int_distribution<> distrInverse1(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexDepartInverse = distrInverse1(generation);
                uniform_int_distribution<> distrInverse2(1, static_cast<int>(tailleSequence - indexDepartInverse));
                const unsigned int nombreCasesInverse = distrInverse2(generation);

                // On inverse une partie de la sequence
                auto sequence = listeSequences_.back();
                sequence.inverser(indexDepartInverse, nombreCasesInverse);
                listeSequences_.push_back(sequence);

                mouvement = Mouvement("inversion", indexDepartInverse, nombreCasesInverse, 0, "");
                listeMouvements_.push_back(mouvement);

                break;
            }
            case 1: {
                uniform_int_distribution<> distrTranspose1(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexDepartTranspose = distrTranspose1(generation);
                uniform_int_distribution<> distrTranspose2(1, static_cast<int>(tailleSequence - indexDepartTranspose));
                const unsigned int nombreCasesTranspose = distrTranspose2(generation);
                uniform_int_distribution<> distrTranspose3(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexDestinationTranspose = distrTranspose3(generation);

                // On transpose une partie de la sequence
                auto sequence = listeSequences_.back();
                sequence.transposer(indexDepartTranspose, nombreCasesTranspose, indexDestinationTranspose);
                listeSequences_.push_back(sequence);

                mouvement = Mouvement("transposition", indexDepartTranspose, nombreCasesTranspose,
                                      indexDestinationTranspose, "");
                listeMouvements_.push_back(mouvement);

                break;
            }
            case 2: {
                uniform_int_distribution<> distrInverseTranspose1(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexDepartInverseTranspose = distrInverseTranspose1(generation);
                uniform_int_distribution<> distrInverseTranspose2(
                    1, static_cast<int>(tailleSequence - indexDepartInverseTranspose));
                const unsigned int nombreCasesInverseTranspose = distrInverseTranspose2(generation);
                uniform_int_distribution<> distrInverseTranspose3(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexDestinationInverseTranspose = distrInverseTranspose3(generation);

                // On inverse et transpose une partie de la sequence
                auto sequence = listeSequences_.back();
                sequence.inverserTransposer(indexDepartInverseTranspose, nombreCasesInverseTranspose,
                                            indexDestinationInverseTranspose);
                listeSequences_.push_back(sequence);

                mouvement = Mouvement("inversion_transposee", indexDepartInverseTranspose, nombreCasesInverseTranspose,
                                      indexDestinationInverseTranspose, "");
                listeMouvements_.push_back(mouvement);

                break;
            }
            case 3: {
                uniform_int_distribution<> distrDuplique1(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexDepartDuplique = distrDuplique1(generation);
                uniform_int_distribution<> distrDuplique2(1, static_cast<int>(tailleSequence - indexDepartDuplique));
                const unsigned int nombreCasesDuplique = distrDuplique2(generation);

                // On duplique une partie de la sequence
                auto sequence = listeSequences_.back();
                sequence.dupliquer(indexDepartDuplique, nombreCasesDuplique);
                listeSequences_.push_back(sequence);

                mouvement = Mouvement("duplication", indexDepartDuplique, nombreCasesDuplique,
                                      0, "");
                listeMouvements_.push_back(mouvement);

                break;
            }

            case 4: {
                uniform_int_distribution<> distrSupprime1(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexDepartSupprime = distrSupprime1(generation);
                uniform_int_distribution<> distrSupprime2(1, static_cast<int>(tailleSequence - indexDepartSupprime));
                const unsigned int nombreCasesSupprime = distrSupprime2(generation);

                // On supprimer une partie de la sequence
                auto sequence = listeSequences_.back();
                sequence.supprimer(indexDepartSupprime, nombreCasesSupprime);
                listeSequences_.push_back(sequence);

                mouvement = Mouvement("suppression", indexDepartSupprime, nombreCasesSupprime,
                                      0, "");
                listeMouvements_.push_back(mouvement);

                break;
            }

            case 5: {
                uniform_int_distribution<> distrModifie1(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexModifie = distrModifie1(generation);
                uniform_int_distribution<> distrLettreModifie1(0, 25);
                const int lettreModifie = distrLettreModifie1(generation);
                uniform_int_distribution<> distrSigneModifie1(0, 1);
                const unsigned int signeModifie = distrSigneModifie1(generation);

                string signeLettreModifie;
                if (signeModifie == 0) {
                    signeLettreModifie += "+";
                } else {
                    signeLettreModifie += "-";
                }

                char lettre;
                lettre = static_cast<char>('A' + lettreModifie);
                auto lettrerenvoi = string(1, lettre);
                signeLettreModifie += lettrerenvoi;

                // On modifie une case de la sequence
                auto sequence = listeSequences_.back();
                sequence.modifierCase(indexModifie, signeLettreModifie);
                listeSequences_.push_back(sequence);

                mouvement = Mouvement("substitution", indexModifie, 0,
                                      0, signeLettreModifie);
                listeMouvements_.push_back(mouvement);

                break;
            }

            case 6: {
                uniform_int_distribution<> distrAjoute1(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexAjoute = distrAjoute1(generation);
                uniform_int_distribution<> distrLettreAjoute1(0, 25);
                const unsigned int lettreAjoute = distrLettreAjoute1(generation);
                uniform_int_distribution<> distrSigneAjoute1(0, 1);
                const unsigned int signeAjoute = distrSigneAjoute1(generation);

                string signeLettreAjoute;
                if (signeAjoute == 0) {
                    signeLettreAjoute += "+";
                } else {
                    signeLettreAjoute += "-";
                }

                char lettre;
                lettre = static_cast<char>('A' + lettreAjoute);
                auto lettrerenvoi = string(1, lettre);
                signeLettreAjoute += lettrerenvoi;

                // On ajoute une case a la sequence
                auto sequence = listeSequences_.back();
                sequence.ajouterCase(indexAjoute, signeLettreAjoute);
                listeSequences_.push_back(sequence);

                mouvement = Mouvement("ajout", indexAjoute, 0,
                                      0, signeLettreAjoute);
                listeMouvements_.push_back(mouvement);

                break;
            }

            default: { break; }
        }
    }
}

/***********************************************************************************************
***** Solution : Le constructeur de confort via une liste de mouvements (apres croisement) *****
***********************************************************************************************/
Solution::Solution(const vector<Mouvement> &mouvements) {
}

/********************************************************************
***** Mutation : Pour modifier un des mouvements de la Solution *****
********************************************************************/
void Solution::Mutation(unsigned int index, const Mouvement &mouvement) {
}

/**********************************************************************************************
***** ObtenirDerniereSequence : Pour copier et manipuler la derniere sequence de la liste *****
**********************************************************************************************/
Sequence Solution::obtenirDerniereSequence() const {
    return listeSequences_.back();
}

/****************************************************************************
***** ObtenirListeSequences : Pour avoir la suite de sequences modifies *****
****************************************************************************/
vector<Sequence> Solution::obtenirListeSequences() const {
    return listeSequences_;
}

/**********************************************************************************************
***** ObtenirListeMouvements : Pour avoir tous les mouvements effectues sur la sequence S *****
**********************************************************************************************/
vector<Mouvement> Solution::obtenirListeMouvements() const {
    return listeMouvements_;
}

/***************************************************************************************************
***** AfficherSolution : Affiche la solution avec l'ensemble des mouvements de cette solution. *****
***************************************************************************************************/
void Solution::afficherSolution() const {
    const unsigned int nbSequences = listeSequences_.size();
    const unsigned int nbMouvements = listeMouvements_.size();

    //!!!!! Faire une gestion d'expression plus propre
    if (nbMouvements + 1 != nbSequences) {
        //!!!!! Faire une gestion d'exception plus propre
        cout << "Solution incohérente : Nombre de séquences incohérent par rapport au nombre de mouvements." << endl;
    } else {
        // Recherche de la longueur max parmis la liste de séquences pour aligner l'affichage des mouvements
        unsigned int taille_sequence_max = 0;
        for (const auto &sequence: listeSequences_) {
            taille_sequence_max = max(taille_sequence_max, sequence.obtenirTailleSequence());
        }

        // Affichage
        for (int i = 0; i < nbMouvements; i++) {
            const auto &sequence = listeSequences_[i];
            const auto &mouvement = listeMouvements_[i];

            sequence.afficherSequence();

            afficherMouvement(mouvement, '|', '_', taille_sequence_max);
        }
        // Affichage de la séquence finale
        listeSequences_[nbSequences - 1].afficherSequence();
    }
}

/**********************************************************************************************************
***** afficherMouvement : Fonction utile à afficherSolution, permet d'améliorer la lisibilité du code *****
**********************************************************************************************************/
void Solution::afficherMouvement(const Mouvement &mouvement,
                                 const char delimiteur, const char symbole, const unsigned int longueurSequence) {
    // L'affichage varie selon si on a qu'un seul caractère affecté par le mouvement ou plusieurs
    if (mouvement.nombreCases == 1) {
        const string debutMouvement(mouvement.indexDepart * 2 - 1, ' ');
        cout << debutMouvement << delimiteur;
    } else {
        const string debutMouvement(mouvement.indexDepart * 2 - 2, ' ');
        const string milieuMouvement(mouvement.nombreCases * 2 - 2, symbole);

        cout << debutMouvement << delimiteur << milieuMouvement << delimiteur;
    }

    // Calcul de l'espace à rajouter pour aligner l'affichage des noms des mouvements
    int posFinMouvement = ((int) longueurSequence - mouvement.indexDepart - mouvement.nombreCases + 1) * 2;

    const string finMouvement(posFinMouvement, ' ');
    cout << finMouvement << " -> ";

    switch(mouvement.nomMouvement) {
        case "inversion": {
            cout << "INVERSION" << endl;
            break;
        }
        case "transposition": {
            cout << "TRANSPOSITION" << endl;
            break;
        }
        case "inversion_transposee": {
            cout << "INVERSION TRANSPOSEE" << endl;
            break;
        }
        case "duplication": {
            cout << "DUPLICATION" << endl;
            break;
        }
        case "suppression": {
            cout << "PERTE" << endl;
            break;
        }
        case "substitution": {
            cout << "SUBSTITUTION" << endl;
            break;
        }
        case "ajout": {
            cout << "AJOUT" << endl;
            break;
        }
        default: {
            cout << "MOUVEMENT INCONNU !!!" << endl;
            break;
        }
    }

    /*// Affichage du nom du mouvement
    if (mouvement.nomMouvement == "inversion")
        cout << "INVERSION" << endl;
    else if (mouvement.nomMouvement == "transposition")
        cout << "TRANSPOSITION" << endl;
    else if (mouvement.nomMouvement == "inversion_transposee")
        cout << "INVERSION TRANSPOSEE" << endl;
    else if (mouvement.nomMouvement == "duplication")
        cout << "DUPLICATION" << endl;
    else if (mouvement.nomMouvement == "suppression")
        cout << "PERTE" << endl;
    else if (mouvement.nomMouvement == "substitution")
        cout << "SUBSTITUTION" << endl;
    else if (mouvement.nomMouvement == "ajout")
        cout << "AJOUT" << endl;
    else
        //!!!!! N'est pas censé se produire si le code est bien fait
        // Est ce qu'on lève quand même une exception si ça arrive ?
        cout << "Mouvement inconnu." << endl;*/
}
