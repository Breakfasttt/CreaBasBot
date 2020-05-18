//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 11/02/2013 - 15h15
// Fichier : déclaraction de la classe options.hpp hérité d'une FSM
// Dernière modification : 06/02/2013
//@@@@@@@@@@@@@@@@@@@

#pragma once 

#include "GeneralConfig.hpp"
#include "DataCenter.hpp"
#include "EventManager.hpp"
#include "FSM.hpp"



enum Options_State
{
	OPTIONS_INIT = 0,
	OPTIONS_UPDATE,
};



class Coptions : public FSM
{

protected : 

	sf::Sprite Background_options;
	sf::Text Titre_options;
	sf::Text Titre_sous_options[2];
	sf::Text Options_langues[4];
	sf::Text m_Volume;

	T_Langue m_langue;
	int m_choix;
	bool m_onVolume;
	bool m_onClickVolume;
	float m_vitesse_volume;
	

	//@@@@ fonction general @@@@
	virtual bool States( StateMachineEvent event, int state );
	virtual FSM* Clone(){return NULL;};
	virtual std::string GetName(){return "options";};
	void Init_options();
	void Update_options();
	void Display_options();


	void change_langue();
	void change_volume();

public :

	Coptions();
	~Coptions();

};