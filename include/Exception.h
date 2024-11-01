#ifndef EXCEPTION_H
#define EXCEPTION_H

class Exception
{
private:
	//***Attributs***//
	unsigned int valeur_;

public:
	//***Constructeurs et destructeurs***//

	/*************************************************
	***** Exception : le constructeur de confort *****
	*************************************************/
	explicit Exception(unsigned int valeur);

	//***Methodes***//

	/***************************************************************
	***** LireValeur : accesseur direct de lecture sur valeur_ *****
	***************************************************************/
	[[nodiscard]] unsigned int lireValeur() const;

	/********************************************************************
	***** ModifierValeur : accesseur direct en ecriture sur valeur_ *****
	********************************************************************/
	void modifierValeur(unsigned int valeur);

	/*****************************************************
	***** LireMessage : precise l'exception survenue *****
	*****************************************************/
	void lireMessage() const;
};

#endif //EXCEPTION_H
