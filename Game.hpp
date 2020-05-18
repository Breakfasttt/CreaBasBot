//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 02/02/2013 - 10h40
// Fichier : définition de la classe game.hpp
// Dernière modification : 02/02/2013
//@@@@@@@@@@@@@@@@@@@

#pragma once

#include "GeneralConfig.hpp"
#include "DataCenter.hpp"
#include "EventManager.hpp"
#include "BibliothequeCartes.hpp"
#include "BiblioDeck.hpp"
#include "Menu.hpp"




class Game
{
protected :

	
	sf::Clock MainClock;
	float DeltaTime;
	CMenu m_Menu;
	bool m_ActualiseTitre;


public :

	Game();
	~Game();

	void init();
	void update();
	void deinit();
	void debugMode();
};