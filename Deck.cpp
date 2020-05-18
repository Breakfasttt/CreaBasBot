//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 06/03/2013 - 15h15
// Fichier : définition de la classe deck.hpp 
// Dernière modification : 06/03/2013
//@@@@@@@@@@@@@@@@@@@


#include "Deck.hpp"


Deck::Deck()
{
	m_CarteRestante = MAX_CARTE;

	for(unsigned int i = 0 ; i < MAX_CARTE ; ++i)
	{
		m_TabCarte[i] = NULL;
		m_TabCarteMorte[i] = NULL;
	}
}

Deck::Deck(Deck& _deck)
{
	m_CarteRestante = MAX_CARTE;

	for(unsigned int i = 0 ; i < MAX_CARTE ; ++i)
	{
		m_TabCarte[i] = new Carte(  _deck.getCarte(i)->getInfosCarte() );
		m_TabCarteMorte[i] = NULL;
	}	

}

Deck::~Deck()
{
	//m_CarteRestante = MAX_CARTE;

	for(unsigned int i = 0 ; i < MAX_CARTE ; ++i)
	{
		if( m_TabCarte[i])
			delete m_TabCarte[i];


		m_TabCarte[i] = NULL;

		if( m_TabCarteMorte[i])
			delete m_TabCarteMorte[i];

		m_TabCarteMorte[i] = NULL;
	}
}


// ## fonction de création de deck

void Deck::SupprimerCarteDuDeck(int _i)
{
	if( _i>=0 && _i < MAX_CARTE)
	{
		delete m_TabCarte[_i];
		m_TabCarte[_i] = NULL;
	}
}

int Deck::AjouterCarteAuDeck(Carte* _c)
{
	int i =0;
	while( m_TabCarte[i] != NULL)
	{
		++i;

		if( i >=MAX_CARTE)
			return -1;
	}

	if( _c)
	{
		m_TabCarte[i] =  _c;
		return i;
	}

	return -1;
}


//## fonction de jeu du deck

bool Deck::ValideDeck()
{
	for(unsigned int i = 0 ; i < MAX_CARTE ; ++i)
	{
		if ( m_TabCarte[i] == NULL )
		{
			LOG("Il n'y a pas le nombre de carte requis")
			return false;
		}
	}

	return true;
}

void Deck::melangeDeck()
{

	for(int i = 0 ; i < NBRE_MELANGE ; ++i)
	{
		int index1 = rand() %MAX_CARTE ;
		int index2 = rand() %MAX_CARTE ;


		if( index1 != index2 )
		{
			Carte* TempCarte = 	m_TabCarte[index1] ;
			m_TabCarte[index1]  = m_TabCarte[index2]  ;
			m_TabCarte[index2] =  TempCarte;
		}
	
	}


}

void Deck::AjouterCarteMorte(Carte*)
{

}

void Deck::ReinitCarteMorte()
{

}

Carte* Deck::piocheDeck()
{
	return NULL;
}
