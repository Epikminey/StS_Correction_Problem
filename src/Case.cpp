#include "Case.h"

#include <iostream>

/********************************************
***** Case : Le constructeur de confort *****
********************************************/
Case::Case(const char signe, const char lettre) {
    if (lettre >= 'A' && lettre <= 'Z') {
        lettre_ = lettre;
    } else {
        throw runtime_error("Le caractere n'est pas une lettre majuscule.");
    }
    if (signe == '+' || signe == '-') {
        signe_ = signe;
    } else {
        throw runtime_error("Il faut donner un signe '+' ou '-'.");
    }
}

/***************************************************************
***** LireLettre : Accesseur direct de lecture sur lettre_ *****
***************************************************************/
char Case::lireLettre() const {
    return lettre_;
}

/*************************************************************
***** LireSigne : Accesseur direct de lecture sur signe_ *****
*************************************************************/
char Case::lireSigne() const {
    return signe_;
}

/***********************************************************************
***** LireCase : Accesseur direct de lecture sur lettre_ et signe_ *****
***********************************************************************/
tuple<char, char> Case::lireCase() const {
    return {signe_, lettre_};
}

/******************************************************
***** AfficherCase : Affiche la valeur de la case *****
******************************************************/
void Case::afficherCase() const {
    cout << signe_ << lettre_;
}

/******************************************************************
***** ModifierSigne : Accesseur direct en ecriture sur signe_ *****
******************************************************************/
void Case::modifierSigne() {
    if (signe_ == '+') {
        signe_ = '-';
    } else {
        signe_ = '+';
    }
}

/****************************************************************************
***** ModifierCase : Accesseur direct en ecriture sur lettre_ et signe_ *****
****************************************************************************/
void Case::modifierCase(const char signe, const char lettre) {
    if (lettre >= 'A' && lettre <= 'Z') {
        lettre_ = lettre;
    } else {
        throw runtime_error("Le caractere n'est pas une lettre majuscule.");
    }
    if (signe == '+' || signe == '-') {
        signe_ = signe;
    } else {
        throw runtime_error("Il faut donner un signe '+' ou '-'.");
    }
}


/*****************************************************************************
***** Operator== : Pour comparer si deux objets Case sont égaux          *****
*****************************************************************************/
bool Case::operator==(const Case &param) const {
    return (lettre_ == param.lettre_ && signe_ == param.signe_);
}

/*****************************************************************************
***** Operator!= : Pour comparer si deux objets Case sont différents     *****
*****************************************************************************/
bool Case::operator!=(const Case &param) const {
    return (lettre_ != param.lettre_ || signe_ != param.signe_);
}
