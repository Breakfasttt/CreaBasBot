//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 04/03/2013 - 14h44
// Fichier : déclaraction de la classe EditeurCarte.hpp hérité d'une FSM
// Dernière modification : 04/03/2013
//@@@@@@@@@@@@@@@@@@@


#include "GeneralConfig.hpp"
#include "DataCenter.hpp"
#include "EventManager.hpp"
#include "FSM.hpp"

#include "BibliothequeCartes.hpp"
#include "Carte.hpp"
#include "BiblioDeck.hpp"
#include "Deck.hpp"



enum Editeur_Deck_State
{
	EditDeck_INIT = 0,
	EditDeck_Update,
};


class EditeurDeck : public FSM
{

protected : 

	virtual bool States( StateMachineEvent event, int state );


	//## fonction général

	void init_deckediteur();
	void Init_ListCarte();
	void Init_ListDeck();

	void update_deckediteur();
	void display_deckediteur();

	//## fonction des boutons

	int m_choixCarte;
	int m_choixDeck;


	void Click_Carte();
	void Click_Deck();

	void Click_Ajouter();
	void Click_Supprimer();
	void Click_sauvegarder();
	void ClickUpDownCarte();


	//## attributs

	// -- Texte

	sf::Text m_titre;
	sf::Text m_Titre_deck;
	sf::Text m_Titre_carte;

	std::vector<sf::Text> m_TabNameCarte;
	sf::Text m_tabCarteDeck[MAX_CARTE];

	int m_decalCarte ,  decalDeck;
	float m_decal_y;
	int m_size;

	// -- bouton

	sf::Text m_UpCarte;
	sf::Text m_DownCarte;
	sf::Text m_Ajouter;
	sf::Text m_Enlever;
	sf::Text m_sauvegarder;


public :
		
	EditeurDeck(){};
	~EditeurDeck(){};

	virtual FSM* Clone(){return NULL;};
	virtual std::string GetName(){return "EditeurDeck";};

};