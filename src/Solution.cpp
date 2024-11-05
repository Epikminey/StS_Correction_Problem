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

// Ajout d'un élément au vecteur
vec.push_back({"texte1", "texte2", 1, 2, 3});

// Affichage du contenu du vecteur
for (const auto& element : vec) {
    std::cout << "String 1: " << element.str1 << ", String 2: " << element.str2
              << ", Int 1: " << element.num1 << ", Int 2: " << element.num2
              << ", Int 3: " << element.num3 << std::endl;
}
