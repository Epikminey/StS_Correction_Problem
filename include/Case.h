#ifndef CASE_H
#define CASE_H

#include <tuple>

using namespace std;

// Contient la structure d'une case de la sequence.
class Case {
private:
    //***Attributs***//
    char lettre_; // Une lettre de l'alphabet majuscule.
    char signe_; //'+' ou '-'.

public:
    //***Constructeurs et destructeurs***//

    // On supprime le constructeur par defaut
    Case() = delete;

    /********************************************
    ***** Case : Le constructeur de confort *****
    ********************************************/
    Case(char signe, char lettre);

    /*********************************************************
    ***** Case : Le constructeur de recopie (par defaut) *****
    *********************************************************/
    Case(const Case &param) = default;

    /**********************************************
    ***** ~Case : Le destructeur (par defaut) *****
    **********************************************/
    ~Case() = default;

    //***Methodes***//

    /*****************************************************************************
    ***** Operator= : Pour recopier un objet Case sur un objet deja existant *****
    *****************************************************************************/
    Case &operator=(const Case &param) = default;

    /*************************************************************************
    ***** Operator!= : Pour comparer si deux objets Case sont différents *****
    *************************************************************************/
    bool operator!=(const Case &param) const;

    /***************************************************************
    ***** LireLettre : Accesseur direct de lecture sur lettre_ *****
    ***************************************************************/
    [[nodiscard]] char lireLettre() const;

    /*************************************************************
    ***** LireSigne : Accesseur direct de lecture sur signe_ *****
    *************************************************************/
    [[nodiscard]] char lireSigne() const;

    /***********************************************************************
    ***** LireCase : Accesseur direct de lecture sur lettre_ et signe_ *****
    ***********************************************************************/
    [[nodiscard]] tuple<char, char> lireCase() const;

    /******************************************************
    ***** AfficherCase : Affiche la valeur de la case *****
    ******************************************************/
    void afficherCase() const;

    /******************************************************************
    ***** ModifierSigne : Accesseur direct en ecriture sur signe_ *****
    ******************************************************************/
    void modifierSigne();

    /****************************************************************************
    ***** ModifierCase : Accesseur direct en ecriture sur lettre_ et signe_ *****
    ****************************************************************************/
    void modifierCase(char signe, char lettre);
};

#endif //CASE_H
