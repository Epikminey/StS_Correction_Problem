#include "Exception.h"
#include <iostream>
using namespace std;

/*************************************************
***** Exception : le constructeur de confort *****
*************************************************/
Exception::Exception(const unsigned int valeur)
{
	valeur_ = valeur;
}

/***************************************************************
***** LireValeur : accesseur direct de lecture sur valeur_ *****
***************************************************************/
unsigned int Exception::lireValeur() const
{
	return valeur_;
}

/********************************************************************
***** ModifierValeur : accesseur direct en ecriture sur valeur_ *****
********************************************************************/
void Exception::modifierValeur(const unsigned int valeur)
{
	valeur_ = valeur;
}

/*****************************************************
***** LireMessage : precise l'exception survenue *****
*****************************************************/
void Exception::lireMessage() const
{
	switch (valeur_)
	{
		case 0:
			cout << "Vous avez initialise l'objet avec succes\n";
		break;

		case 1:
			cout << "Cast impossible\n";
		break;

		case 2:
			cout << "Pas assez ou trop de valeurs renseignees\n";
		break;

		default:
			cout << "Rien de special\n";
		break;
	}
}
