//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 06/02/2013 - 14h44
// Fichier : déclaraction de la classe menu.hpp hérité d'une FSM
// Dernière modification : 06/02/2013
//@@@@@@@@@@@@@@@@@@@

#pragma once 

#include "GeneralConfig.hpp"
#include "DataCenter.hpp"
#include "EventManager.hpp"
#include "FSM.hpp"

//include des sous partie
#include "Options.hpp"
#include "EditeurCarte.hpp"
#include "EditeurDeck.hpp"
#include "Combat.hpp"


enum Menu_State
{
	MENU_INIT = 0,
	MENU_CHOIX,
	MENU_EDITEUR_DECK,
	MENU_OPTIONS,
	MENU_EDITEUR_CARTES,
	MENU_JEU,
	MENU_RETOUR_MENU,
	MENU_EXIT
};

typedef enum Menu_Text
{
	JOUER = 0,
	DECK_EDITEUR,
	OPTIONS,
	CARTES_EDITEUR,
	QUITTER,
	AUCUN
}Echoix ;


class CMenu : public FSM
{
public :

	CMenu();
	~CMenu();


protected :

	//méthode

	// @@@@ Fonction General @@@@
	virtual bool States( StateMachineEvent event, int state );
	virtual FSM* Clone(){return NULL;};
	virtual std::string GetName(){return "Menu";};
	void Init_Menu();	
	void Reinit_Retour_Menu();
	void Update_Menu();
	void Display_Menu();
	void Deinit_Menu();
	void Debug_Infos();

	// @@@@ Fonction Retour @@@@

	void Affiche_Retour_Menu();
	void Affiche_Demande_Retour();
	void Test_Demande_Retour_Menu();
	void Test_Accepte_Retour();


	// @@@@ Fonction Outils @@@@

	void Selection();

	
	//attributs de base
	sf::Sprite m_Background;
	sf::Text m_Titre;
	Echoix m_choix;
	sf::Text m_ChoixText[5];

	//attributs de retour Menu
	sf::Sprite m_Bouton_Retour;
	sf::Text m_Demande_Retour;
	sf::Text m_Reponse_Retour[2];
	bool m_Accept_retour ;

	// << Attributs sous partie  >>

	Coptions m_options;
	EditeurCarte m_EditeurCarte;
	EditeurDeck m_EditeurDeck;
	CCombat m_combat;


	// << Attributs test  >>

};

