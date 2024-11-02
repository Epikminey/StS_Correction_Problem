#include "Case.h"

#include <Exception.h>
#include <iostream>

using namespace std;

/********************************************
***** Case : le constructeur de confort *****
********************************************/
Case::Case(const char lettre, const bool signe) {
    if ((lettre >= 'A' && lettre <= 'Z') || lettre == '_') {
        lettre_ = lettre;
    } else {
        throw Exception(1);
    }
    signe_ = signe;
}

/*************************************************************
***** LireChar : accesseur direct de lecture sur lettre_ *****
*************************************************************/
char Case::lireChar() const {
    return lettre_;
}

/*************************************************************
***** Exception : accesseur direct de lecture sur signe_ *****
*************************************************************/
bool Case::lireBooleen() const {
    return signe_;
}

/************************************************************************
***** Exception : accesseur direct de lecture sur lettre_ et signe_ *****
************************************************************************/
tuple<char, bool> Case::lireCase() const {
    return {lettre_, signe_};
}

/***************************************************
***** Exception : affiche la valeur de la case *****
***************************************************/
void Case::afficherCase() const {
    char signe;
    if (lettre_ == '_') {
        signe = '_';
    } else if (signe_ == true) {
        signe = '+';
    } else {
        signe = '-';
    }
    cout << signe << lettre_;
}

/***************************************************************
***** Exception : accesseur direct en ecriture sur lettre_ *****
***************************************************************/
void Case::modifierChar(const char lettre) {
    if ((lettre >= 'A' && lettre <= 'Z') || lettre == '_') {
        lettre_ = lettre;
    } else {
        throw Exception(1);
    }
}

/**************************************************************
***** Exception : accesseur direct en ecriture sur signe_ *****
**************************************************************/
void Case::modifierBooleen() {
    if (signe_ == true) {
        signe_ = false;
    } else {
        signe_ = true;
    }
}

/*************************************************************************
***** Exception : accesseur direct en ecriture sur lettre_ et signe_ *****
*************************************************************************/
void Case::modifierCase(const char lettre) {
    if ((lettre >= 'A' && lettre <= 'Z') || lettre == '_') {
        lettre_ = lettre;
    } else {
        throw Exception(1);
    }
    if (signe_ == true) {
        signe_ = false;
    } else {
        signe_ = true;
    }
}
