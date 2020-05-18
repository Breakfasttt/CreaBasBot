//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 02/02/2013 - 10h40
// Fichier : game.cpp
// Dernière modification : 02/02/2013
//@@@@@@@@@@@@@@@@@@@

#include "Game.hpp"

Game::Game()
{
	//définition des singleton
	DATA;
	BIBLI;
	
	//inscription des script a la DB
	BIBLI->SelfRegisterScript();
	BIBLI->DetruitCarteIncorrect();

	DECK;

	// clock FPS
	DeltaTime = MainClock.restart().asSeconds();
}

Game::~Game()
{

}

void Game::init()
{
	m_ActualiseTitre = true;
	m_Menu.Initialize();
}

void Game::update()
{	

	while(RENDER->isOpen())
    {	
		// << Calcul Des FPS >>
		sf::Time TempDeltaTime = MainClock.restart();
		DeltaTime = TempDeltaTime.asSeconds();
		DATA->setDT(DeltaTime); // on l'actualisele dt dans le DataCenter
		DeltaTime = 1 / DeltaTime ; // calcul des fps
		
		// << Clear de la fenetre >>
		RENDER->clear();

		// << Process >>
		EVENT->update(RENDER);
		m_Menu.Update();
			
		// << debug >>
		debugMode();

		// << Affichage >>
		RENDER->display();

		if( EVENT->isClosed() || EVENT->isKeyPressed(sf::Keyboard::Escape ) )
		{
			RENDER->close();
		}

	}
}

void Game::deinit()
{

}


void Game::debugMode()
{
	if(DDEBUG)
	{
		m_ActualiseTitre = true;

		std::stringstream oss;

		oss << DATA->getMainTitleName() << "_debug_mode. Fps : " << DeltaTime ;

		DATA->setTitleName( oss.str() ) ;

	}
	else
	{
		if( m_ActualiseTitre )
		{
			DATA->setTitleName( DATA->getMainTitleName() ) ;
			m_ActualiseTitre = false;
		}
	}
}


