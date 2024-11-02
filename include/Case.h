#ifndef CASE_H
#define CASE_H

#include <tuple>

using namespace std;

class Case {
private:
    //***Attributs***//
    char lettre_; // Une lettre de l'alphabet majuscule.
    bool signe_; //true = '+' , false = '-'.

public:
    //***Constructeurs et destructeurs***//

    // On supprime le constructeur par defaut
    Case() = delete;

    /********************************************
    ***** Case : le constructeur de confort *****
    ********************************************/
    Case(char lettre, bool signe);

    /*********************************************************
    ***** Case : le constructeur de recopie (par defaut) *****
    *********************************************************/
    Case(const Case &Param) = default;

    /*********************************************
    ***** Case : le destructeur (par defaut) *****
    *********************************************/
    ~Case() = default;

    //***Methodes***//

    /*****************************************************************************
    ***** Operator= : pour recopier un objet Case sur un objet deja existant *****
    *****************************************************************************/
    Case &operator=(const Case &Param) = default;

    /*************************************************************
    ***** LireChar : accesseur direct de lecture sur lettre_ *****
    *************************************************************/
    [[nodiscard]] char lireChar() const;

    /*************************************************************
    ***** Exception : accesseur direct de lecture sur signe_ *****
    *************************************************************/
    [[nodiscard]] bool lireBooleen() const;

    /************************************************************************
    ***** Exception : accesseur direct de lecture sur lettre_ et signe_ *****
    ************************************************************************/
    [[nodiscard]] tuple<char, bool> lireCase() const;

    /***************************************************
    ***** Exception : affiche la valeur de la case *****
    ***************************************************/
    void afficherCase() const;

    /***************************************************************
    ***** Exception : accesseur direct en ecriture sur lettre_ *****
    ***************************************************************/
    void modifierChar(char lettre);

    /**************************************************************
    ***** Exception : accesseur direct en ecriture sur signe_ *****
    **************************************************************/
    void modifierBooleen();

    /*************************************************************************
    ***** Exception : accesseur direct en ecriture sur lettre_ et signe_ *****
    *************************************************************************/
    void modifierCase(char lettre);
};

#endif //CASE_H
