//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 06/03/2013 - 15h15
// Fichier : déclaraction de la classe bibliodeck.hpp 
// Dernière modification : 06/03/2013
//@@@@@@@@@@@@@@@@@@@


#pragma once 

#include "GeneralConfig.hpp"
#include "BibliothequeCartes.hpp"
#include "Carte.hpp"
#include "Deck.hpp"

#define DECK BiblioDeck::getDeckManager()

typedef struct
{
	char nom[30];
}T_infosDeck;

// << class singleton >>
class BiblioDeck
{
public :

	static BiblioDeck* getDeckManager();
	~BiblioDeck();

	void FabriqueDefautDeck();
	void LoadDeck();
	bool SaveDeck();
	void setDeck(Deck* _d){m_DeckPrincipal = _d;};
	Deck* getDeck(){return m_DeckPrincipal;};


private : 
	
	BiblioDeck();

protected : 

	Deck* m_DeckPrincipal;

};