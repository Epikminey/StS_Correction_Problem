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

    for (unsigned int boucle = 0; boucle < nombreMutations; ++boucle) {

        // Génération d'un mouvement aléatoire
        Mouvement mouvement = GenererMouvementAleatoire(listeSequences_.back());

        // Application du mouvement généré
        AppliquerMouvement(mouvement);
    }
}

/***********************************************************************************************
***** Solution : Le constructeur de confort via une liste de mouvements (apres croisement) *****
***********************************************************************************************/
Solution::Solution(const Instance &instance, const vector<Mouvement> &mouvements): evaluation_(0) {
    // On ajoute la premiere sequence, la sequence Source.
    listeSequences_.push_back(instance.obtenirSource());

    for (const auto &mouvement: mouvements) {
        AppliquerMouvement(mouvement);
    }
}

/**********************************************************************************
***** Mutation : Créée un mouvement aléatoire selon le taux de mutation donné *****
**********************************************************************************/
void Solution::Mutation(const float tauxMutation, const unsigned int nombreMutations) {

    // Détermine le nombre de mouvements à réaliser selon le taux de mutation.
    random_device rd;
    mt19937 generation(rd());
    bernoulli_distribution distribMutation(tauxMutation);

    // Initialisation du compteur
    unsigned int nbMutationsFinal = 0;
    for (unsigned int i = 0; i < nombreMutations; ++i) {
        if (distribMutation(generation)) {
            nbMutationsFinal += 1; // On ajoute une mutation en se basant sur le taux de mutation
        }
    }

    if(nbMutationsFinal > 0) {
        for (unsigned int boucle = 0; boucle < nombreMutations; ++boucle) {

            // Détermine quel mouvement sera modifié
            const unsigned int numMouvementMax = listeMouvements_.size() - 1;
            uniform_int_distribution<> distrNumMouvement(0, static_cast<int>(numMouvementMax));
            const unsigned int numMouvement = distrNumMouvement(generation);

            // Génère un mouvement aléatoire à appliquer sur la séquence précédent le mouvement à modifier
            Mouvement mouvement = GenererMouvementAleatoire(listeSequences_[numMouvement]);

            // Applique le mouvement généré
            ModifierMouvement(mouvement, numMouvement);
        }
    }
}


/****************************************************************************************
***** ModifierMouvement : Modifie un mouvement de la solution à une position donnée *****
****************************************************************************************/
void Solution::ModifierMouvement(const Mouvement &mouvement, const unsigned int numMouvement) {

    // Modification du mouvement dans la liste
    listeMouvements_[numMouvement] = mouvement;


    // Suppression des séquences "obsolètes"
    listeSequences_.erase(listeSequences_.begin() + numMouvement + 1, listeSequences_.end());

    // Recalcul des séquences en conséquent
    for(unsigned int numSequence = numMouvement; numSequence < listeSequences_.size(); numSequence++) {
        AppliquerMouvement(listeMouvements_[numMouvement]);
    }
}


/*******************************************************************************************
***** AppliquerMouvement :Applique un mouvement sur la dernière séquence de la solution *****
*******************************************************************************************/
void Solution::AppliquerMouvement(const Mouvement &mouvement) {

    // Ajout du mouvement dans la liste de mouvements
    listeMouvements_.push_back(mouvement);

    // Switch case pour les differentes valeurs de idMouvement
    switch (mouvement.idMouvement) {
        case INVERSION: {
            // On inverse une partie de la sequence
            auto sequence = listeSequences_.back();
            sequence.inverser(mouvement.indexDepart, mouvement.nombreCases);
            listeSequences_.push_back(sequence);
            break;
        }
        case TRANSPOSITION: {
            // On transpose une partie de la sequence
            auto sequence = listeSequences_.back();
            sequence.transposer(mouvement.indexDepart, mouvement.nombreCases, mouvement.indexDestination);
            listeSequences_.push_back(sequence);
            break;
        }
        case INVERSION_TRANSPOSEE: {
            // On inverse et transpose une partie de la sequence
            auto sequence = listeSequences_.back();
            sequence.inverserTransposer(mouvement.indexDepart, mouvement.nombreCases, mouvement.indexDestination);
            listeSequences_.push_back(sequence);
            break;
        }
        case DUPLICATION: {
            // On duplique une partie de la sequence
            auto sequence = listeSequences_.back();
            sequence.dupliquer(mouvement.indexDepart, mouvement.nombreCases);
            listeSequences_.push_back(sequence);
            break;
        }
        case SUPPRESSION: {
            // On supprime une partie de la sequence
            auto sequence = listeSequences_.back();
            sequence.supprimer(mouvement.indexDepart, mouvement.nombreCases);
            listeSequences_.push_back(sequence);
            break;
        }
        case SUBSTITUTION: {
            // On modifie une case de la sequence
            auto sequence = listeSequences_.back();
            sequence.modifierCase(mouvement.indexDepart, mouvement.nomCase);
            listeSequences_.push_back(sequence);
            break;
        }
        case AJOUT: {
            // On ajoute une case a la sequence
            auto sequence = listeSequences_.back();
            sequence.ajouterCase(mouvement.indexDepart, mouvement.nomCase);
            listeSequences_.push_back(sequence);
            break;
        }
        default: { break; }
    }
}

/*****************************************************************************************
***** GenererMouvementAleatoire : Créée et renvoie un mouvement généré aléatoirement *****
*****                             se base sur la dernière séquence de listeSequences *****
*****************************************************************************************/
Mouvement Solution::GenererMouvementAleatoire(Sequence &sequence) {

    // Mouvement aléatoire
    Mouvement mouvement;

    // On initialise le generateur de nombre aleatoire
    random_device graine;
    mt19937 generation(graine());

    uniform_int_distribution<> distrOperation1(0, 6);
    unsigned int chiffreAleatoire = distrOperation1(generation);

    if(chiffreAleatoire == 3)
        chiffreAleatoire = 2;

    // Pour obtenir la taille de la sequence precedente
    const unsigned int tailleSequence = sequence.obtenirTailleSequence();

    // Switch case pour les differentes valeurs de randomNumber
    switch (chiffreAleatoire) {
        case 0: {
            uniform_int_distribution<> distrInverse1(0, static_cast<int>(tailleSequence) - 1);
            const unsigned int indexDepartInverse = distrInverse1(generation);
            uniform_int_distribution<> distrInverse2(1, static_cast<int>(tailleSequence - indexDepartInverse));
            const unsigned int nombreCasesInverse = distrInverse2(generation);

            // On inverse une partie de la sequence
            mouvement = Mouvement(INVERSION, indexDepartInverse, nombreCasesInverse, 0, "");

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
            mouvement = Mouvement(TRANSPOSITION, indexDepartTranspose, nombreCasesTranspose,
                                  indexDestinationTranspose, "");

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
            mouvement = Mouvement(INVERSION_TRANSPOSEE, indexDepartInverseTranspose, nombreCasesInverseTranspose,
                                  indexDestinationInverseTranspose, "");

            break;
        }
        case 3: {
            uniform_int_distribution<> distrDuplique1(0, static_cast<int>(tailleSequence) - 1);
            const unsigned int indexDepartDuplique = distrDuplique1(generation);
            uniform_int_distribution<> distrDuplique2(1, static_cast<int>(tailleSequence - indexDepartDuplique));
            const unsigned int nombreCasesDuplique = distrDuplique2(generation);

            const unsigned int destinationDuplication = indexDepartDuplique + nombreCasesDuplique;

            // On duplique une partie de la sequence
            mouvement = Mouvement(DUPLICATION, indexDepartDuplique, nombreCasesDuplique, destinationDuplication, "");

            break;
        }

        case 4: {
            uniform_int_distribution<> distrSupprime1(0, static_cast<int>(tailleSequence) - 1);
            const unsigned int indexDepartSupprime = distrSupprime1(generation);
            uniform_int_distribution<> distrSupprime2(1, static_cast<int>(tailleSequence - indexDepartSupprime));
            const unsigned int nombreCasesSupprime = distrSupprime2(generation);

            // On supprimer une partie de la sequence
            mouvement = Mouvement(SUPPRESSION, indexDepartSupprime, nombreCasesSupprime, 0, "");

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
            mouvement = Mouvement(SUBSTITUTION, indexModifie, 1, 0, signeLettreModifie);

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
            mouvement = Mouvement(AJOUT, indexAjoute, 1, 0, signeLettreAjoute);

            break;
        }

        default: { break; }
    }

    return mouvement;
}


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

    //!!!!! Faire une gestion d'expression plus propre
    if (const unsigned int nbMouvements = listeMouvements_.size(); nbMouvements + 1 != nbSequences) {
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
void Solution::afficherMouvement(const Mouvement &mouvement, const char delimiteur, const char symbole,
                                 const unsigned int longueurSequence) {
    //Utile au débogage
    //cout << "Id : " << mouvement.idMouvement << " début : " << mouvement.indexDepart << " longeur : " << mouvement.nombreCases << " destination : " << mouvement.indexDestination << "\n";

    // L'affichage varie selon si on a qu'un seul caractère affecté par le mouvement ou plusieurs
    if (mouvement.nombreCases == 1) {
        const string debutMouvement(mouvement.indexDepart * 2, ' ');
        cout << debutMouvement << delimiteur;
    } else {
        const string debutMouvement(mouvement.indexDepart * 2, ' ');
        const string milieuMouvement(mouvement.nombreCases * 2 - 2, symbole);

        cout << debutMouvement << delimiteur << milieuMouvement << delimiteur;
    }

    // Calcul de l'espace à rajouter pour aligner l'affichage des noms des mouvements
    const unsigned int posAligmentNom = (longueurSequence - mouvement.indexDepart - mouvement.nombreCases) * 2;

    const string finMouvement(posAligmentNom, ' ');
    cout << finMouvement << " -> ";

    switch (mouvement.idMouvement) {
        case INVERSION: {
            cout << "Inversion de " << mouvement.nombreCases <<
                    " caractères à la position " << mouvement.indexDepart << endl;
            break;
        }
        case TRANSPOSITION: {
            cout << "Transposition de " << mouvement.nombreCases <<
                    " caractères à la position " << mouvement.indexDepart <<
                    " vers la position " << mouvement.indexDestination << endl;
            break;
        }
        case INVERSION_TRANSPOSEE: {
            cout << "Transposition et inversion de " << mouvement.nombreCases <<
                    " caractères à la position " << mouvement.indexDepart <<
                    " vers la position " << mouvement.indexDestination << endl;
            break;
        }
        case DUPLICATION: {
            cout << "Duplication de " << mouvement.nombreCases <<
                    " caractères à la position " << mouvement.indexDepart <<
                    " vers la position " << mouvement.indexDestination << endl;
            break;
        }
        case SUPPRESSION: {
            cout << "Suppresion de " << mouvement.nombreCases <<
                    " caractères à la position " << mouvement.indexDepart << endl;
            break;
        }
        case SUBSTITUTION: {
            cout << "Subsitution de " << mouvement.nombreCases <<
                    " caractères à la position " << mouvement.indexDepart << endl;
            break;
        }
        case AJOUT: {
            cout << "Ajout de " << mouvement.nombreCases <<
                    " caractères à la position " << mouvement.indexDepart << endl;
            break;
        }
        default: {
            cout << "MOUVEMENT INCONNU !!!" << endl;
            break;
        }
    }
}

void Solution::afficherSolutionSimplifiee() const {
    for (const auto &[idMouvement, indexDepart, nombreCases, indexDestination, nomCase]: listeMouvements_) {
        cout << idMouvement << " + ";
    }
    cout << endl;
}
