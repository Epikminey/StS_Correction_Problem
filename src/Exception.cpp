#include "Exception.h"

#include <iostream>

using namespace std;

/*************************************************
***** Exception : le constructeur de confort *****
*************************************************/
Exception::Exception(const unsigned int valeur) : valeur_(valeur) {}

/***************************************************************
***** LireValeur : accesseur direct de lecture sur valeur_ *****
***************************************************************/
unsigned int Exception::lireValeur() const {
    return valeur_;
}

/********************************************************************
***** ModifierValeur : accesseur direct en ecriture sur valeur_ *****
********************************************************************/
void Exception::modifierValeur(const unsigned int valeur) {
    valeur_ = valeur;
}

/*****************************************************
***** LireMessage : precise l'exception survenue *****
*****************************************************/
void Exception::lireMessage() const {
    switch (valeur_) {
        case 1:
            cout << "Le caractere n'est ni une lettre majuscule, ni un vide.\n";
            break;

        default:
            cout << "Une erreur est survenue.\n";
            break;
    }
}
