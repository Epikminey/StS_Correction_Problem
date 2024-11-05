#ifndef ALGORITHME_H
#define ALGORITHME_H

#include "Instance.h"
#include "Solution.h"

class Algorithme {
private:
    /*** Attributs ***/
    Solution meilleureSolution_; // Le chemin de sequences
    unsigned int nombreMouvements_; // Les mouvements pour faire le chemin de sequences

public:
    //***Constructeurs et destructeurs***//

    // On supprime le constructeur par defaut
    Algorithme() = delete;

    /************************************************
    ***** Solution : Le constructeur de confort *****
    ************************************************/
    explicit Algorithme(const Instance& instance);

    // On supprime le constructeur de recopie
    Algorithme(const Algorithme &param) = delete;

    /**************************************************
    ***** ~Solution : Le destructeur (par defaut) *****
    **************************************************/
    ~Algorithme() = default;

    //***Methodes***//

    // On supprime l'operateur =
    Algorithme &operator=(const Algorithme &param) = delete;

    void croisement(const Sequence &sequence1, const Sequence &sequence2);



    void afficherNombreMouvements() const;

    void afficherMeilleureSolution() const;
};

#endif //ALGORITHME_H
