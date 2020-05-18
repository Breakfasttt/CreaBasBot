//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 06/02/2013 - 14h44
// Fichier : définition de la classe menu.hpp hérité d'une FSM
// Dernière modification : 06/02/2013
//@@@@@@@@@@@@@@@@@@@

#include "Menu.hpp"


CMenu::CMenu()
{

}

CMenu::~CMenu()
{

}


// @@@@ FSM @@@@

bool CMenu::States( StateMachineEvent event, int state )
{
	BeginStateMachine

	//***********************
		State(MENU_INIT)
			OnEnter
				LOG( "MENU : INIT") 
				Init_Menu();
				SetState(MENU_CHOIX);
			OnUpdate
			OnExit
	//#######################

	//***********************
		State(MENU_CHOIX)
			OnEnter
				LOG( "MENU : CHOIX" )
			OnUpdate				
				Update_Menu();
				Display_Menu();
				Debug_Infos();
			OnExit
	//#######################

	//***********************
		State(MENU_EDITEUR_DECK)
			OnEnter
				LOG(  "MENU : MENU_EDITEUR_DECK")
				m_EditeurDeck.ForceCurrentState(0);
				m_EditeurDeck.Initialize();
			OnUpdate

				m_EditeurDeck.Update();

				Affiche_Retour_Menu();
				Test_Demande_Retour_Menu();
			OnExit
	//#######################

	//***********************
		State(MENU_OPTIONS)
			OnEnter
				LOG( "MENU : MENU_OPTIONS" )
				m_options.Initialize();
			OnUpdate

				m_options.Update();

				Affiche_Retour_Menu();
				Test_Demande_Retour_Menu();
			OnExit
	//#######################

	//***********************
		State(MENU_EDITEUR_CARTES)
			OnEnter
				LOG(  "MENU : MENU_EDITEUR_CARTES" )
				
				m_EditeurCarte.ForceCurrentState(0);
				m_EditeurCarte.Initialize();

			OnUpdate

				Affiche_Retour_Menu();
				Test_Demande_Retour_Menu();

				m_EditeurCarte.Update();

			OnExit


	//#######################

	//***********************
		State(MENU_JEU)
			OnEnter
				LOG(  "MENU : MENU_JEU" )
				
				unsigned int TestState = this->getStateBefore();

				if( TestState != MENU_RETOUR_MENU )
				{
					m_combat.ForceCurrentState(0);
					m_combat.Initialize();
				}

			OnUpdate

				m_combat.Update();

				Affiche_Retour_Menu();
				Test_Demande_Retour_Menu();
			OnExit
	//#######################

	//***********************
		State(MENU_EXIT)
			OnEnter
				LOG(  "MENU : MENU_EXIT" )
				RENDER->close();
			OnUpdate		
			OnExit
	//#######################

	//***********************
		State(MENU_RETOUR_MENU)
			OnEnter
				LOG(  "MENU : MENU_RETOUR_MENU" )
				Reinit_Retour_Menu();
			OnUpdate

				Test_Accepte_Retour();
				Affiche_Demande_Retour();
			OnExit
	//#######################

	EndStateMachine
}


// @@@@ Fonction General @@@@

void CMenu::Init_Menu()
{
	// <<chargement de la texture>>
	sf::Texture* TextureBG = DATA->getTextureByName("MENU_BG");

	if(TextureBG)
		m_Background.setTexture(*TextureBG,true);

	TextureBG = NULL;

	//<<chargement de la Font>>
	sf::Font* Temp = NULL;
	Temp = DATA->getFontByName("datacron") ;

	int Taille = DATA->getIntByName("Menu_Choix_Taille");

	 //<<chargement du titre>>

	m_Titre.setString ( DATA->getTextByName("MENU_TITRE") );	
	m_Titre.setPosition( DATA->getFloatByName("Menu_Titre_X") ,
						 DATA->getFloatByName("Menu_Titre_Y") ) ;

	if( Temp )
	{
		m_Titre.setFont(*Temp);
		m_Titre.setCharacterSize(Taille * 2.0f);
	}

	//<<chargement des texte de choix>>

	m_ChoixText[0].setString( DATA->getTextByName("MENU_CHOIX_COMBAT") );
	m_ChoixText[1].setString( DATA->getTextByName("MENU_CHOIX_DECK") );
	m_ChoixText[2].setString( DATA->getTextByName("MENU_CHOIX_OPTIONS") );
	m_ChoixText[3].setString( DATA->getTextByName("MENU_CHOIX_CARTE") );	
	m_ChoixText[4].setString( DATA->getTextByName("MENU_CHOIX_QUIT") );

	float Xdepart = DATA->getFloatByName("Menu_Choix_X");
	float Ydepart = DATA->getFloatByName("Menu_Choix_Y");
	float decalage = DATA->getFloatByName("Menu_Choix_Decalage");
	float AntiDecalage = 0;
	

	for(int i = 0 ; i < 5 ; ++i)
	{
		if( DDEBUG )
		{
			m_ChoixText[i].setColor(sf::Color::White);
			m_ChoixText[i].setFont(*Temp);
			m_ChoixText[i].setCharacterSize(Taille);
			m_ChoixText[i].setPosition( Xdepart  ,
										Ydepart + decalage * (float)i );
		}
		else if( (Echoix)i == CARTES_EDITEUR )
		{
			m_ChoixText[i].setColor(sf::Color::White);
			m_ChoixText[i].setFont(*Temp);
			m_ChoixText[i].setCharacterSize(Taille);
			m_ChoixText[i].setPosition( Xdepart  ,
										Ydepart + decalage * (float)i + AntiDecalage );	
			AntiDecalage = -decalage ;
		}
		else
		{
			m_ChoixText[i].setColor(sf::Color::White);
			m_ChoixText[i].setFont(*Temp);
			m_ChoixText[i].setCharacterSize(Taille);
			m_ChoixText[i].setPosition( Xdepart  ,
										Ydepart + decalage * (float)i + AntiDecalage );				
		}
	}


	//<<chargement des images du retour menu>>

	TextureBG = DATA->getTextureByName("RETOUR_MENU");

	if(TextureBG)
		m_Bouton_Retour.setTexture(*TextureBG);

	m_Bouton_Retour.setPosition( DATA->getFloatByName("Menu_bouton_retour_x") ,
								 DATA->getFloatByName("Menu_bouton_retour_y") ) ;

	TextureBG = NULL;

	//<<chargement des texte du retour menu>>
	m_Demande_Retour.setString( DATA->getTextByName("MENU_RETOUR_DEMANDE") );
	m_Reponse_Retour[0].setString( DATA->getTextByName("MENU_RETOUR_OUI") );
	m_Reponse_Retour[1].setString( DATA->getTextByName("MENU_RETOUR_NON") );

	Xdepart = DATA->getFloatByName("Menu_choix_oui_x");
	Ydepart = DATA->getFloatByName("Menu_choix_oui_y");
	decalage = DATA->getFloatByName("Menu_choix_non_decal");
	Taille = DATA->getIntByName("Menu_Choix_Taille_oui");

	m_Demande_Retour.setColor(sf::Color::White);
	m_Demande_Retour.setFont(*Temp);
	m_Demande_Retour.setCharacterSize(Taille);
	m_Demande_Retour.setPosition( DATA->getFloatByName("Menu_Retour_infos_x"),
								  DATA->getFloatByName("Menu_Retour_infos_y") ) ;

	for(int i = 0 ; i < 2 ; ++i)
	{
		m_Reponse_Retour[i].setColor(sf::Color::White);
		m_Reponse_Retour[i].setFont(*Temp);
		m_Reponse_Retour[i].setCharacterSize(Taille);
		m_Reponse_Retour[i].setPosition( Xdepart + decalage * (float)i ,
										 Ydepart  );	
	}

	m_Accept_retour = false;

	Temp = NULL;
	m_choix = AUCUN ;

}

void CMenu::Reinit_Retour_Menu()
{
	m_Demande_Retour.setString( DATA->getTextByName("MENU_RETOUR_DEMANDE") );
	m_Reponse_Retour[0].setString( DATA->getTextByName("MENU_RETOUR_OUI") );
	m_Reponse_Retour[1].setString( DATA->getTextByName("MENU_RETOUR_NON") );
}

void CMenu::Update_Menu()
{

	Selection();
}

void CMenu::Display_Menu()
{
	RENDER->draw(m_Background);
	RENDER->draw(m_Titre);

	for(int i = 0 ; i < 5 ; ++i)
	{
		if( DDEBUG )
		{
			RENDER->draw( m_ChoixText[i] );
		}
		else 
		{
			if( (Echoix)i != CARTES_EDITEUR )
				RENDER->draw( m_ChoixText[i] );
		}
	}
}

void CMenu::Deinit_Menu()
{

}

void CMenu::Debug_Infos()
{
	if( DDEBUG )
	{
		std::ostringstream oss;
		oss << "State : " << (int)m_choix << std::endl;
		sf::Text Infos( oss.str() ) ;
		Infos.setCharacterSize(12);

		RENDER->draw(Infos);

		if( m_ChoixText[QUITTER].getPosition().y == m_ChoixText[CARTES_EDITEUR].getPosition().y )
		{
			m_ChoixText[QUITTER].setPosition( m_ChoixText[QUITTER].getPosition().x ,
										     m_ChoixText[CARTES_EDITEUR].getPosition().y 
																+ DATA->getFloatByName("Menu_Choix_Decalage") ) ;	 
		}	
	}
	else
	{
	
		if( m_ChoixText[QUITTER].getPosition().y != m_ChoixText[CARTES_EDITEUR].getPosition().y )
		{
			m_ChoixText[QUITTER].setPosition( m_ChoixText[CARTES_EDITEUR].getPosition() ) ;
		}
	
	
	}
}


// @@@@ Fonction Outils @@@@

void CMenu::Selection()
{

	Echoix LastChoix = m_choix ;
	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );
	bool OnText = false;

	for(int i = 0 ; i < 5 ; ++i)
	{
		if(!DDEBUG &&  (Echoix)i == CARTES_EDITEUR)
		{
			++i;
		}

		if( m_ChoixText[i].getGlobalBounds().contains( TestVecteur ) )
		{

			m_choix = (Echoix)i;

			if( LastChoix  != m_choix  && LastChoix != AUCUN )
			{
				m_ChoixText[(int)LastChoix].setColor( sf::Color::White );	
				m_ChoixText[i].setColor( sf::Color::Cyan );	
			}
			else
			{
				m_ChoixText[i].setColor( sf::Color::Cyan );	
			}
			OnText = true;
			break;
		}

	}

	if(!OnText && LastChoix != AUCUN )
	{
		m_choix = AUCUN;

		for(int i = 0 ; i < 5 ; ++i)
		{
			m_ChoixText[i].setColor( sf::Color::White );	
		}	
	}

	if( EVENT->isMButtonPressed(sf::Mouse::Left) && m_choix!=AUCUN)
	{
		switch(m_choix)
		{
			case JOUER : SetState(MENU_JEU); break;
			case DECK_EDITEUR : SetState(MENU_EDITEUR_DECK); break;
			case OPTIONS : SetState(MENU_OPTIONS); break;
			case CARTES_EDITEUR : SetState(MENU_EDITEUR_CARTES); break;
			case QUITTER : SetState(MENU_EXIT); break;
			default : break;		
		}	
	}
}


	// @@@@ Fonction Retour @@@@

void CMenu::Affiche_Retour_Menu()
{
	RENDER->draw(m_Bouton_Retour);
}

void CMenu::Affiche_Demande_Retour()
{
	RENDER->draw(m_Background);
	RENDER->draw(m_Demande_Retour);

	for(int i = 0 ; i < 2 ; ++i)
	{
		RENDER->draw( m_Reponse_Retour[i] ) ;
	}
}

void CMenu::Test_Demande_Retour_Menu()
{
	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

	if( m_Bouton_Retour.getGlobalBounds().contains(TestVecteur)   ) 
	{
		if(EVENT->isMButtonPressed(sf::Mouse::Left) )
			SetState(MENU_RETOUR_MENU);
	}
	
}


void CMenu::Test_Accepte_Retour()
{
	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );
	bool test_Deja_sur_texte = m_Accept_retour;

	if( m_Reponse_Retour[0].getGlobalBounds().contains(TestVecteur)   ) 
	{
		if(!m_Accept_retour)
		{
			m_Reponse_Retour[0].setColor(sf::Color::Cyan) ;
			m_Accept_retour = true;
		}

		if( EVENT->isMButtonPressed(sf::Mouse::Left) )
			SetState(MENU_INIT);
	}
	else if( m_Reponse_Retour[1].getGlobalBounds().contains(TestVecteur)   )
	{
		if(!m_Accept_retour)
		{
			m_Reponse_Retour[1].setColor(sf::Color::Cyan) ;
			m_Accept_retour = true;
		}

		if( EVENT->isMButtonPressed(sf::Mouse::Left) ) 
		{
			RetourEtatPrecedent();

			if(DDEBUG)
			{
				LOG("### historique menu ### ");
				AfficheHistorique();
			}
		}
	}
	else
	{
		m_Accept_retour = false;
	}

	if(  (m_Accept_retour != test_Deja_sur_texte)  && m_Accept_retour == false )
	{
		m_Reponse_Retour[0].setColor(sf::Color::White) ;
		m_Reponse_Retour[1].setColor(sf::Color::White) ;
	
	}


}