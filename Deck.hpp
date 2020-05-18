//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 06/03/2013 - 15h15
// Fichier : déclaraction de la classe deck.hpp 
// Dernière modification : 06/03/2013
//@@@@@@@@@@@@@@@@@@@

#pragma once

#include "GeneralConfig.hpp"
#include "BibliothequeCartes.hpp"
#include "Carte.hpp"


#define MAX_CARTE 15
#define NBRE_MELANGE 15

class Deck
{
protected :

	Carte* m_TabCarte[MAX_CARTE];
	Carte* m_TabCarteMorte[MAX_CARTE];
	int m_CarteRestante;


public :

	Deck();
	Deck(Deck&);
	~Deck();

	// ## fonction de création de deck
	void SupprimerCarteDuDeck(int);
	int AjouterCarteAuDeck(Carte*);

	//## fonction de jeu du accesseur
	Carte* getCarte(int _i){return m_TabCarte[_i];};

	//## fonction de jeu du deck
	bool ValideDeck();
	void melangeDeck();
	void AjouterCarteMorte(Carte*);
	void ReinitCarteMorte();

	Carte* piocheDeck();
	

};