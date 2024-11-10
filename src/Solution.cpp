#include "Solution.h"



/************************************************
***** Solution : Le constructeur par defaut *****
************************************************/
Solution::Solution() {
    listeSequences_ = vector<Sequence>();
    listeMouvements_ = vector<Mouvement>();
}

/************************************************
***** Solution : Le constructeur de confort *****
************************************************/
Solution::Solution(const vector<Mouvement>& mouvements) {
}

// // Ajout d'un élément au vecteur
// vec.push_back({"texte1", "texte2", 1, 2, 3});
//
// // Affichage du contenu du vecteur
// for (const auto& element : vec) {
//     std::cout << "String 1: " << element.str1 << ", String 2: " << element.str2
//               << ", Int 1: " << element.num1 << ", Int 2: " << element.num2
//               << ", Int 3: " << element.num3 << std::endl;
// }



/********************************************************************************
***** AfficherSolution : Affiche la solution avec l'ensemble des mouvements *****
*****                    de cette solution.                                 *****
********************************************************************************/
void Solution::afficherSolution() const {

    // Pour les test
    /*
    const string ADN1 = "+A-B+C-D+E-F+G-H+I";
    const string ADN2 = "+A-B+C-D+E-F+G-C+I";
    const string ADN3 = "+A-B+C-D+E-F-C+I";
    const string ADN4 = "+I-C-F+E-D+C-B+A";
    const string ADN5 = "+I-C+G-F+E-D+C-B+A";
    const string ADN6 = "+I-H+G-F+E-D+C-B+A";

    auto sequence1 = Sequence(ADN1);
    auto sequence2 = Sequence(ADN2);
    auto sequence3 = Sequence(ADN3);
    auto sequence4 = Sequence(ADN4);
    auto sequence5 = Sequence(ADN5);
    auto sequence6 = Sequence(ADN6);

    vector sequences = {sequence1, sequence2, sequence3, sequence4, sequence5, sequence6};


    Mouvement mouvement1 = {"substitution", 8, 1, SUBSTITUTION, "str"};
    Mouvement mouvement2 = {"perte", 7, 1, PERTE, "str"};
    Mouvement mouvement3 = {"inversion", 1, 8, INVERSION, "str"};
    Mouvement mouvement4 = {"ajout", 3, 1, AJOUT, "str"};
    Mouvement mouvement5 = {"substitution", 2, 1, SUBSTITUTION, "str"};


    Mouvement mouvement1 = {"substitution", 8, 1, 0, "str"};
    Mouvement mouvement2 = {"perte", 7, 1, 0, "str"};
    Mouvement mouvement3 = {"inversion", 1, 8, 0, "str"};
    Mouvement mouvement4 = {"ajout", 3, 1, 0, "str"};
    Mouvement mouvement5 = {"substitution", 2, 1, 0, "str"};
    vector mouvements = {mouvement1, mouvement2, mouvement3, mouvement4, mouvement5};

    const unsigned int nbSequences = sequences.size();
    const unsigned int nbMouvements = mouvements.size();
    */


    const unsigned int nbSequences = listeSequences_.size();
    const unsigned int nbMouvements = listeMouvements_.size();

    //!!!!! Faire une gestion d'expression plus propre
    if(nbMouvements + 1 != nbSequences) {
        //!!!!! Faire une gestion d'exception plus propre
        cout << "Solution incohérente : Nombre de séquences incohérent par rapport au nombre de mouvements." << endl;
    } else {

        // Recherche de la longueur max parmis la liste de séquences pour aligner l'affichage des mouvements
        unsigned int taille_sequence_max = 0;
        for(const auto& sequence : listeSequences_) {
            taille_sequence_max = max(taille_sequence_max,sequence.obtenirTailleSequence());
        }

        // Affichage
        for(int i = 0; i < nbMouvements; i++) {
            const auto& sequence = listeSequences_[i];
            const auto& mouvement = listeMouvements_[i];

            sequence.afficherSequence();

            afficherSolution_afficherMouvement(mouvement, '|', '_', taille_sequence_max);

        }
        // Affichage de la séquence finale
        listeSequences_[nbSequences - 1].afficherSequence();
    }

}

void Solution::afficherSolution_afficherMouvement(const Mouvement &mouvement,
    char delimiteur, char symbole, unsigned int longueurSequence) const {

    // L'affichage varie selon si on a qu'un seul caractère affecté par le mouvement ou plusieurs
    if(mouvement.nombreCases == 1) {
        const string debutMouvement(mouvement.indexDepart * 2 - 1, ' ');
        cout << debutMouvement << delimiteur;
    }
    else {
        const string debutMouvement(mouvement.indexDepart * 2 - 2, ' ');
        const string milieuMouvement(mouvement.nombreCases * 2 - 2, symbole);

        cout << debutMouvement << delimiteur << milieuMouvement << delimiteur;
    }

    // Calcul de l'espace à rajouter pour aligner l'affichage des noms des mouvements
    int posFinMouvement = ((int)longueurSequence - mouvement.indexDepart - mouvement.nombreCases + 1) * 2;

    const string finMouvement(posFinMouvement, ' ');
    cout <<finMouvement << " -> ";


    // Plus rapide en temps d'exécution avec un switch case, mais impossible si on a que "nomMouvement" en attribut de mouvement
    /*
    switch(mouvement.idMouvement) {
        case INVERSION:
            cout << "INVERSION";
        break;
        case TRANSPOSITION:
            cout << "TRANSPOSITION";
        break;
        case INVERSION_TRANSPOSEE:
            cout << "INVERSION TRANSPOSEE";
        break;
        case DUPLICATION:
            cout << "DUPLICATION";
        break;
        case PERTE:
            cout << "PERTE";
        break;
        case SUBSTITUTION:
            cout << "SUBSTITUTION";
        break;
        case AJOUT:
            cout << "AJOUT";
        break;
        default:
            cout << "MOUVEMENT INCONNU !!!";
    }
    */

    // Affichage du nom du mouvement
    if (mouvement.nomMouvement == "inversion")
        cout << "INVERSION";
    else if (mouvement.nomMouvement == "transposition")
        cout << "TRANSPOSITION";
    else if (mouvement.nomMouvement == "inversion_transposee")
        cout << "INVERSION TRANSPOSEE";
    else if (mouvement.nomMouvement == "duplication")
        cout << "DUPLICATION";
    else if (mouvement.nomMouvement == "perte")
        cout << "PERTE";
    else if (mouvement.nomMouvement == "substitution")
        cout << "SUBSTITUTION";
    else if (mouvement.nomMouvement == "ajout")
        cout << "AJOUT";
    else
        //!!!!! N'est pas censé se produire si le code est bien fait
        // Est ce qu'on lève quand même une exception si ça arrive ?
        cout << "Mouvement inconnu.";

    //Saut de ligne une fois le mouvement affiché
    cout << endl;
}

