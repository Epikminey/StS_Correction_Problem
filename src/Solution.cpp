#include "Solution.h"

#include <random>
#include <iostream>

/***************************************************************************
***** Solution : Le constructeur de confort avec mouvements aleatoires *****
***************************************************************************/
Solution::Solution(const Instance &instance, const unsigned int nombreMutations) {
    // On ajoute la premiere sequence, la sequence Source.
    listeSequences_.push_back(instance.obtenirSource());
    evaluation_ = instance.obtenirTerminale().obtenirTailleSequence();

    // On initialise le generateur de nombre aleatoire
    std::random_device graine;
    std::mt19937 generation(graine());

    for (unsigned int boucle = 0; boucle < nombreMutations; ++boucle) {
        std::uniform_int_distribution<> distrOperation1(0, 6);
        const unsigned int chiffreAleatoire = distrOperation1(generation);

        // Pour obtenir la taille de la sequence precedente
        const unsigned int tailleSequence = listeSequences_.back().obtenirTailleSequence();

        Mouvement mouvement;

        // Switch case pour les differentes valeurs de randomNumber
        switch (chiffreAleatoire) {
            case 0: {
                std::uniform_int_distribution<> distrInverse1(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexDepartInverse = distrInverse1(generation);
                std::uniform_int_distribution<> distrInverse2(1, static_cast<int>(tailleSequence - indexDepartInverse));
                const unsigned int nombreCasesInverse = distrInverse2(generation);

                // On inverse une partie de la sequence
                auto sequence = listeSequences_.back();
                sequence.inverser(indexDepartInverse, nombreCasesInverse);
                listeSequences_.push_back(sequence);

                mouvement = Mouvement(INVERSION, indexDepartInverse, nombreCasesInverse, 0, "");
                listeMouvements_.push_back(mouvement);

                break;
            }
            case 1: {
                std::uniform_int_distribution<> distrTranspose1(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexDepartTranspose = distrTranspose1(generation);
                std::uniform_int_distribution<> distrTranspose2(1, static_cast<int>(tailleSequence - indexDepartTranspose));
                const unsigned int nombreCasesTranspose = distrTranspose2(generation);
                std::uniform_int_distribution<> distrTranspose3(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexDestinationTranspose = distrTranspose3(generation);

                // On transpose une partie de la sequence
                auto sequence = listeSequences_.back();
                sequence.transposer(indexDepartTranspose, nombreCasesTranspose, indexDestinationTranspose);
                listeSequences_.push_back(sequence);

                mouvement = Mouvement(TRANSPOSITION, indexDepartTranspose, nombreCasesTranspose,
                                      indexDestinationTranspose, "");
                listeMouvements_.push_back(mouvement);

                break;
            }
            case 2: {
                std::uniform_int_distribution<> distrInverseTranspose1(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexDepartInverseTranspose = distrInverseTranspose1(generation);
                std::uniform_int_distribution<> distrInverseTranspose2(
                    1, static_cast<int>(tailleSequence - indexDepartInverseTranspose));
                const unsigned int nombreCasesInverseTranspose = distrInverseTranspose2(generation);
                std::uniform_int_distribution<> distrInverseTranspose3(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexDestinationInverseTranspose = distrInverseTranspose3(generation);

                // On inverse et transpose une partie de la sequence
                auto sequence = listeSequences_.back();
                sequence.inverserTransposer(indexDepartInverseTranspose, nombreCasesInverseTranspose,
                                            indexDestinationInverseTranspose);
                listeSequences_.push_back(sequence);

                mouvement = Mouvement(INVERSION_TRANSPOSEE, indexDepartInverseTranspose, nombreCasesInverseTranspose,
                                      indexDestinationInverseTranspose, "");
                listeMouvements_.push_back(mouvement);

                break;
            }
            case 3: {
                std::uniform_int_distribution<> distrDuplique1(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexDepartDuplique = distrDuplique1(generation);
                std::uniform_int_distribution<> distrDuplique2(1, static_cast<int>(tailleSequence - indexDepartDuplique));
                const unsigned int nombreCasesDuplique = distrDuplique2(generation);

                // On duplique une partie de la sequence
                auto sequence = listeSequences_.back();
                sequence.dupliquer(indexDepartDuplique, nombreCasesDuplique);
                listeSequences_.push_back(sequence);

                mouvement = Mouvement(DUPLICATION, indexDepartDuplique, nombreCasesDuplique, 0, "");
                listeMouvements_.push_back(mouvement);

                break;
            }

            case 4: {
                std::uniform_int_distribution<> distrSupprime1(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexDepartSupprime = distrSupprime1(generation);
                std::uniform_int_distribution<> distrSupprime2(1, static_cast<int>(tailleSequence - indexDepartSupprime));
                const unsigned int nombreCasesSupprime = distrSupprime2(generation);

                // On supprimer une partie de la sequence
                auto sequence = listeSequences_.back();
                sequence.supprimer(indexDepartSupprime, nombreCasesSupprime);
                listeSequences_.push_back(sequence);

                mouvement = Mouvement(SUPPRESSION, indexDepartSupprime, nombreCasesSupprime, 0, "");
                listeMouvements_.push_back(mouvement);

                break;
            }

            case 5: {
                std::uniform_int_distribution<> distrModifie1(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexModifie = distrModifie1(generation);
                std::uniform_int_distribution<> distrLettreModifie1(0, 25);
                const int lettreModifie = distrLettreModifie1(generation);
                std::uniform_int_distribution<> distrSigneModifie1(0, 1);
                const unsigned int signeModifie = distrSigneModifie1(generation);

                std::string signeLettreModifie;
                if (signeModifie == 0) {
                    signeLettreModifie += "+";
                } else {
                    signeLettreModifie += "-";
                }

                char lettre;
                lettre = static_cast<char>('A' + lettreModifie);
                auto lettrerenvoi = std::string(1, lettre);
                signeLettreModifie += lettrerenvoi;

                // On modifie une case de la sequence
                auto sequence = listeSequences_.back();
                sequence.modifierCase(indexModifie, signeLettreModifie);
                listeSequences_.push_back(sequence);

                mouvement = Mouvement(SUBSTITUTION, indexModifie, 1, 0, signeLettreModifie);
                listeMouvements_.push_back(mouvement);

                break;
            }

            case 6: {
                std::uniform_int_distribution<> distrAjoute1(0, static_cast<int>(tailleSequence) - 1);
                const unsigned int indexAjoute = distrAjoute1(generation);
                std::uniform_int_distribution<> distrLettreAjoute1(0, 25);
                const unsigned int lettreAjoute = distrLettreAjoute1(generation);
                std::uniform_int_distribution<> distrSigneAjoute1(0, 1);
                const unsigned int signeAjoute = distrSigneAjoute1(generation);

                std::string signeLettreAjoute;
                if (signeAjoute == 0) {
                    signeLettreAjoute += "+";
                } else {
                    signeLettreAjoute += "-";
                }

                char lettre;
                lettre = static_cast<char>('A' + lettreAjoute);
                auto lettrerenvoi = std::string(1, lettre);
                signeLettreAjoute += lettrerenvoi;

                // On ajoute une case a la sequence
                auto sequence = listeSequences_.back();
                sequence.ajouterCase(indexAjoute, signeLettreAjoute);
                listeSequences_.push_back(sequence);

                mouvement = Mouvement(AJOUT, indexAjoute, 1, 0, signeLettreAjoute);
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
Solution::Solution(const Instance &instance, const std::vector<Mouvement> &mouvements): evaluation_(0) {
    // On ajoute la premiere sequence, la sequence Source.
    listeMouvements_ = mouvements;
    listeSequences_.push_back(instance.obtenirSource());

    for (const auto &[idMouvement, indexDepart, nombreCases, indexDestination, nomCase]: mouvements) {
        // Switch case pour les differentes valeurs de idMouvement
        switch (idMouvement) {
            case INVERSION: {
                // On inverse une partie de la sequence
                auto sequence = listeSequences_.back();
                sequence.inverser(indexDepart, nombreCases);
                listeSequences_.push_back(sequence);
                break;
            }
            case TRANSPOSITION: {
                // On transpose une partie de la sequence
                auto sequence = listeSequences_.back();
                sequence.transposer(indexDepart, nombreCases, indexDestination);
                listeSequences_.push_back(sequence);
                break;
            }
            case INVERSION_TRANSPOSEE: {
                // On inverse et transpose une partie de la sequence
                auto sequence = listeSequences_.back();
                sequence.inverserTransposer(indexDepart, nombreCases, indexDestination);
                listeSequences_.push_back(sequence);
                break;
            }
            case DUPLICATION: {
                // On duplique une partie de la sequence
                auto sequence = listeSequences_.back();
                sequence.dupliquer(indexDepart, nombreCases);
                listeSequences_.push_back(sequence);
                break;
            }
            case SUPPRESSION: {
                // On supprime une partie de la sequence
                auto sequence = listeSequences_.back();
                sequence.supprimer(indexDepart, nombreCases);
                listeSequences_.push_back(sequence);
                break;
            }
            case SUBSTITUTION: {
                // On modifie une case de la sequence
                auto sequence = listeSequences_.back();
                sequence.modifierCase(indexDepart, nomCase);
                listeSequences_.push_back(sequence);
                break;
            }
            case AJOUT: {
                // On ajoute une case a la sequence
                auto sequence = listeSequences_.back();
                sequence.ajouterCase(indexDepart, nomCase);
                listeSequences_.push_back(sequence);
                break;
            }
            default: { break; }
        }
    }
}


/*void Solution::Mutation(unsigned int index, const Mouvement &mouvement) {
    try {
        // Exception si le mouvement n'est pas possible
        listeMouvements_.push_back(mouvement);

        // Une nouvelle séquence est générée à partir de la dernière séquence enregistrée
        auto nouvelle_sequence = Sequence(listeSequences_.back());


        switch (mouvement.idMouvement) {
            case INVERSION: {
                nouvelle_sequence.inverser(mouvement.indexDepart, mouvement.nombreCases);
                break;
            }
            case TRANSPOSITION: {
                nouvelle_sequence.transposer(mouvement.indexDepart, mouvement.nombreCases, mouvement.indexDestination);
                break;
            }
            case INVERSION_TRANSPOSEE: {
                nouvelle_sequence.inverserTransposer(mouvement.indexDepart, mouvement.nombreCases,
                                                     mouvement.indexDestination);
                break;
            }
            case DUPLICATION: {
                nouvelle_sequence.dupliquer(mouvement.indexDepart, mouvement.nombreCases);
                break;
            }
            case SUPPRESSION: {
                nouvelle_sequence.supprimer(mouvement.indexDepart, mouvement.nombreCases);
                break;
            }
            case SUBSTITUTION: {
                nouvelle_sequence.modifierCase(mouvement.indexDepart, mouvement.nomCase);
                break;
            }
            case AJOUT: {
                nouvelle_sequence.ajouterCase(mouvement.indexDepart, mouvement.nomCase);
                break;
            }
            default: {
                throw std::invalid_argument("Mouvement impossible !");
            }
        }
    } catch (...) {
        throw std::invalid_argument("Erreur : Mouvement impossible pour cette solution.");
    }
}*/

/********************************************************************
***** Mutation : Pour modifier un des mouvements de la Solution *****
********************************************************************/
//void Solution::Mutation(float tauxMutation, unsigned int nombreMutations) {
//}

/***********************************************************************************************************************************
***** CalculerEvaluation : Pour calculer la distance de Levenshtein entre la dernière séquence de la Solution et la séquence T *****
***********************************************************************************************************************************/
void Solution::calculerEvaluation(const Sequence &sequenceTerminale) {
    evaluation_ = calculerDistanceLevenshtein(listeSequences_.back(), sequenceTerminale);
}

/*********************************************************************************************************************************
***** ObtenirEvaluation : Pour obtenir la distance de Levenshtein entre la dernière séquence de la Solution et la séquence T *****
*********************************************************************************************************************************/
unsigned int Solution::obtenirEvaluation() const {
    return evaluation_;
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
std::vector<Sequence> Solution::obtenirListeSequences() const {
    return listeSequences_;
}

/**********************************************************************************************
***** ObtenirListeMouvements : Pour avoir tous les mouvements effectues sur la sequence S *****
**********************************************************************************************/
std::vector<Mouvement> Solution::obtenirListeMouvements() const {
    return listeMouvements_;
}

/***************************************************************************************************
***** AfficherSolution : Affiche la solution avec l'ensemble des mouvements de cette solution. *****
***************************************************************************************************/
void Solution::afficherSolution() const {
    const unsigned int nbSequences = listeSequences_.size();

    //!!!!! Faire une gestion d'expression plus propre
    if (const unsigned int nbMouvements = listeMouvements_.size(); nbMouvements + 1 != nbSequences) {
        //!!!!! Faire une gestion d'exception plus propre
        std::cout << "Solution incohérente : Nombre de séquences incohérent par rapport au nombre de mouvements." << std::endl;
    } else {
        // Recherche de la longueur max parmis la liste de séquences pour aligner l'affichage des mouvements
        unsigned int taille_sequence_max = 0;
        for (const auto &sequence: listeSequences_) {
            taille_sequence_max = std::max(taille_sequence_max, sequence.obtenirTailleSequence());
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
void Solution::afficherMouvement(const Mouvement &mouvement, const char delimiteur, const char symbole,
                                 const unsigned int longueurSequence) {
    //Utile au débogage
    //cout << "Id : " << mouvement.idMouvement << " début : " << mouvement.indexDepart << " longeur : " << mouvement.nombreCases << " destination : " << mouvement.indexDestination << "\n";

    // L'affichage varie selon si on a qu'un seul caractère affecté par le mouvement ou plusieurs
    if (mouvement.nombreCases == 1) {
        const std::string debutMouvement(mouvement.indexDepart * 2, ' ');
        std::cout << debutMouvement << delimiteur;
    } else {
        const std::string debutMouvement(mouvement.indexDepart * 2, ' ');
        const std::string milieuMouvement(mouvement.nombreCases * 2 - 2, symbole);

        std::cout << debutMouvement << delimiteur << milieuMouvement << delimiteur;
    }

    // Calcul de l'espace à rajouter pour aligner l'affichage des noms des mouvements
    const unsigned int posAligmentNom = (longueurSequence - mouvement.indexDepart - mouvement.nombreCases) * 2;

    const std::string finMouvement(posAligmentNom, ' ');
    std::cout << finMouvement << " -> ";

    switch (mouvement.idMouvement) {
        case INVERSION: {
            std::cout << "Inversion de " << mouvement.nombreCases <<
                    " caractères à la position " << mouvement.indexDepart << std::endl;
            break;
        }
        case TRANSPOSITION: {
            std::cout << "Transposition de " << mouvement.nombreCases <<
                    " caractères à la position " << mouvement.indexDepart <<
                    " vers la position " << mouvement.indexDestination << std::endl;
            break;
        }
        case INVERSION_TRANSPOSEE: {
            std::cout << "Transposition et inversion de " << mouvement.nombreCases <<
                    " caractères à la position " << mouvement.indexDepart <<
                    " vers la position " << mouvement.indexDestination << std::endl;
            break;
        }
        case DUPLICATION: {
            std::cout << "Duplication de " << mouvement.nombreCases <<
                    " caractères à la position " << mouvement.indexDepart << std::endl;
            break;
        }
        case SUPPRESSION: {
            std::cout << "Suppresion de " << mouvement.nombreCases <<
                    " caractères à la position " << mouvement.indexDepart << std::endl;
            break;
        }
        case SUBSTITUTION: {
            std::cout << "Subsitution de " << mouvement.nombreCases <<
                    " caractères à la position " << mouvement.indexDepart << std::endl;
            break;
        }
        case AJOUT: {
            std::cout << "Ajout de " << mouvement.nombreCases <<
                    " caractères à la position " << mouvement.indexDepart << std::endl;
            break;
        }
        default: {
            std::cout << "MOUVEMENT INCONNU !!!" << std::endl;
            break;
        }
    }
}

void Solution::afficherSolutionSimplifiee() const {
    for (const auto &[idMouvement, indexDepart, nombreCases, indexDestination, nomCase]: listeMouvements_) {
        std::cout << idMouvement << " + ";
    }
    std::cout << std::endl;
}
