//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 11/03/2013 - 15h15
// Fichier : déclaraction de la classe Combat.hpp hérité d'une FSM
// Dernière modification : 11/03/2013
//@@@@@@@@@@@@@@@@@@@

#pragma once 

#include "GeneralConfig.hpp"
#include "DataCenter.hpp"
#include "EventManager.hpp"
#include "FSM.hpp"
#include "Joueur.hpp"



enum Combat_State
{
	COMBAT_INIT = 0,
	COMBAT_INTRO,
	COMBAT_UPDATE,
	COMBAT_FIN,
};

enum Type_joueur
{
	HUMAIN = 0,
	IA 
};



class CCombat : public FSM
{

protected : 

	//@@@ Attributs @@@

	sf::Sprite m_plateau;
	Cjoueur* m_Joueurs[2];


	// -- intro -- 
	float m_timerIntro;
	sf::Text m_TextIntro;

	// -- fin --
	sf::Text m_InfosFin;

	
	//@@@@ fonction general @@@@
	virtual bool States( StateMachineEvent event, int state );
	virtual FSM* Clone(){return NULL;};
	virtual std::string GetName(){return "Combat";};

	//@@@@ fonction de combat @@@@

	void Init_combat();
	void Init_Intro();
	void Intro();
	void DisplayArene();

	void ConditionFin();
	void DisplayFin();

	void Init_Joueur();
	void Update_combat() ;

public :

	CCombat();
	~CCombat();


};