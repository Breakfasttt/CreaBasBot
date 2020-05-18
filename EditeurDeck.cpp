//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 04/03/2013 - 14h44
// Fichier : déclaraction de la classe Editeurdeck.cpp hérité d'une FSM
// Dernière modification : 04/03/2013
//@@@@@@@@@@@@@@@@@@@

#include "EditeurDeck.hpp"



bool EditeurDeck::States( StateMachineEvent event, int state )
{
	BeginStateMachine

		//***********************
		State(EditDeck_INIT)

		OnEnter

		LOG("EditeurDeck : EditDeck_INIT");
	init_deckediteur();
	SetState(EditDeck_Update);


	OnUpdate

		OnExit
		//#######################

		//***********************
		State(EditDeck_Update)

		OnEnter
		LOG("EditeurDeck : EditDeck_Update");

	OnUpdate

		update_deckediteur();
	display_deckediteur();

	OnExit
		//#######################


		EndStateMachine
}


//## fonction général

// -- init

void EditeurDeck::init_deckediteur()
{
	m_choixCarte = -1;
	m_choixDeck = -1;

	// <<init des titres >>

	m_size = DATA->getIntByName("Editeur_d_taille") ;
	m_decal_y = DATA->getFloatByName("EDITEUR_c_decal"); 

	// __texte__
	m_titre.setString( DATA->getTextByName("EDITEUR_DECK_TITRE") );
	m_Titre_deck.setString( DATA->getTextByName("EDITEUR_DECK_TITRE_DECK") );
	m_Titre_carte.setString( DATA->getTextByName("EDITEUR_CARTE_TITRECARTE") );
	// __position__

	m_titre.setPosition(	DATA->getFloatByName("Editeur_d_Titre_g_x") ,
		DATA->getFloatByName("Editeur_d_Titre_g_y") );

	m_Titre_deck.setPosition(	DATA->getFloatByName("Editeur_d_TitreDeck_x") ,
		DATA->getFloatByName("Editeur_d_TitreDeck_y") );

	m_Titre_carte.setPosition(	DATA->getFloatByName("Editeur_c_titre_carte_x") ,
		DATA->getFloatByName("Editeur_c_titre_carte_y") );

	// << init des cartes >>
	Init_ListCarte();
	Init_ListDeck();


	// <<init des boutons >>

	//__texte__
	m_UpCarte.setString( DATA->getTextByName("EDITEUR_CARTE_UP") );
	m_DownCarte.setString( DATA->getTextByName("EDITEUR_CARTE_DOWN") );
	m_Ajouter.setString( DATA->getTextByName("EDITEUR_DECK_ADD") );
	m_Enlever.setString( DATA->getTextByName("EDITEUR_DECK_REMOVE") );
	m_sauvegarder.setString( DATA->getTextByName("EDITEUR_DECK_SAVE") );

	//__taille__

	m_sauvegarder.setCharacterSize( m_size );
	m_UpCarte.setCharacterSize( m_size );
	m_DownCarte.setCharacterSize( m_size );
	m_Ajouter.setCharacterSize( m_size );
	m_Enlever.setCharacterSize( m_size );

	//__position__

	m_DownCarte.setPosition(	DATA->getFloatByName("Editeur_c_down_card_x") ,
		DATA->getFloatByName("Editeur_c_down_card_y") );

	m_UpCarte.setPosition(	DATA->getFloatByName("Editeur_c_up_card_x") ,
		DATA->getFloatByName("Editeur_c_up_card_y") );

	m_sauvegarder.setPosition(	DATA->getFloatByName("Editeur_d_save_x") ,
		DATA->getFloatByName("Editeur_d_save_y") );

	m_Ajouter.setPosition(	DATA->getFloatByName("Editeur_d_Add_x") ,
		DATA->getFloatByName("Editeur_d_Add_y") );

	m_Enlever.setPosition(	DATA->getFloatByName("Editeur_d_remove_x") ,
		DATA->getFloatByName("Editeur_d_remove_y") );
}

void EditeurDeck::Init_ListCarte()
{
	m_decalCarte = 0;

	while(m_TabNameCarte.size() >0 )
	{
		m_TabNameCarte.pop_back();
	}

	int NbreCarte = BIBLI->getNbreCarte();

	m_TabNameCarte.clear();


	float X = DATA->getFloatByName("Editeur_c_up_card_x");
	float Y = DATA->getFloatByName("Editeur_c_up_card_y");
	float Decal = DATA->getFloatByName("EDITEUR_c_decal");
	int Position = 0;

	for(unsigned int i =0 ; i < NbreCarte ; ++i)
	{
		sf::Text TempText;
		TempText.setCharacterSize(m_size);
		TempText.setString(BIBLI->getInfosCartes(i).m_name);
		TempText.setPosition( X , Y + (Position+1)*(Decal));

		Position++;

		if(Position==5)
			Position = 0;

		m_TabNameCarte.push_back(TempText);	
	}

}

void EditeurDeck::Init_ListDeck()
{
	float X = DATA->getFloatByName("Editeur_d_TitreDeck_x");
	float Y = DATA->getFloatByName("Editeur_d_TitreDeck_y");

	for (int i = 0 ; i < MAX_CARTE ; ++i)
	{
		m_tabCarteDeck[i].setCharacterSize(m_size);
		m_tabCarteDeck[i].setPosition( X , Y + (i+1)*(m_decal_y+5.0f) ) ;
	}


	Deck* TempDeck =  DECK->getDeck();

	if( TempDeck)
	{

		for (int i = 0 ; i < MAX_CARTE ; ++i)
		{
			Carte* TempCarte  = TempDeck->getCarte(i) ;

			if(TempCarte)
			{
				m_tabCarteDeck[i].setString(TempCarte->getInfosCarte().m_name);
			}
			else
			{
				m_tabCarteDeck[i].setString("");
			}		
		}


	}
	else
	{
		LOG("Erreur, aucun deck disponible")
	}

}



// -- update

void EditeurDeck::update_deckediteur()
{
	ClickUpDownCarte();
	Click_Carte();
	Click_Deck();

	Click_Supprimer();
	Click_Ajouter();
	Click_sauvegarder();
}


// -- display

void EditeurDeck::display_deckediteur()
{
	//-- rendu des titres

	RENDER->draw(m_titre);
	RENDER->draw(m_Titre_deck);
	RENDER->draw(m_Titre_carte);

	//-- rendu des boutons

	RENDER->draw(m_UpCarte);
	RENDER->draw(m_DownCarte);
	RENDER->draw(m_Ajouter);
	RENDER->draw(m_Enlever);
	RENDER->draw(m_sauvegarder);


	// -- rendu des nom de carte
	int min = m_decalCarte+5;
	if( m_decalCarte+5 >m_TabNameCarte.size() )
		min = m_TabNameCarte.size();

	for(int i = m_decalCarte ; i < min ; ++i)
	{
		RENDER->draw(m_TabNameCarte[i]);
	}

	for(int i = 0 ; i < MAX_CARTE ; ++i)
	{
		RENDER->draw(m_tabCarteDeck[i]);
	}
}


// -- fonction des boutons


void EditeurDeck::Click_Carte()
{
	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

	int min = m_decalCarte+5;
	if( m_decalCarte+5 >m_TabNameCarte.size() )
		min = m_TabNameCarte.size();

	for(unsigned int i = m_decalCarte ; i < min ; ++i)
	{
		if( m_TabNameCarte[i].getGlobalBounds().contains(TestVecteur ) )
		{
			if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
			{

				if(m_choixCarte>=0)
					m_TabNameCarte[m_choixCarte].setColor(sf::Color::White);

				m_choixCarte = i ;
				m_TabNameCarte[i].setColor(sf::Color::Cyan);
				break;
			}
		}
	}	
}

void EditeurDeck::Click_Deck()
{
	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

	for(unsigned int i = 0 ; i < MAX_CARTE ; ++i)
	{
		if( m_tabCarteDeck[i].getGlobalBounds().contains(TestVecteur ) )
		{
			if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
			{

				if(m_choixDeck>=0)
					m_tabCarteDeck[m_choixDeck].setColor(sf::Color::White);

				m_choixDeck = i ;
				m_tabCarteDeck[i].setColor(sf::Color::Red);
				break;
			}
		}
	}
}

void EditeurDeck::Click_Ajouter()
{
	if( m_choixCarte >= 0)
	{
		sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );
	
		if( m_Ajouter.getGlobalBounds().contains(TestVecteur ) )
		{
			if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
			{
				Deck* TempDeck = DECK->getDeck();

				if( TempDeck )
				{
					Carte* carteTemp = BIBLI->CreerCartes( m_TabNameCarte[m_choixCarte].getString() ) ;
					int index = -2;

					if (carteTemp)
						index = TempDeck->AjouterCarteAuDeck( carteTemp );
				
					if( index>=0 && index < MAX_CARTE)
					{
						m_tabCarteDeck[index].setString( m_TabNameCarte[m_choixCarte].getString() );
						m_tabCarteDeck[index].setColor(sf::Color::White) ;
					}
					else
					{
						delete carteTemp;
						LOG("Trop de carte, la carte n'a pas ete rajoutee au deck")
					}
				}
			}
		}
	}

}

void EditeurDeck::Click_Supprimer()
{
	if( m_choixDeck >=0)
	{
		sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

		if( m_Enlever.getGlobalBounds().contains(TestVecteur ) )
		{
			if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
			{
				m_tabCarteDeck[m_choixDeck].setString("");
				

				Deck* TempDeck = DECK->getDeck();

				if (TempDeck)
				{
					TempDeck->SupprimerCarteDuDeck(m_choixDeck);		
				}

				m_choixDeck = -1;
			}
		}
	}
}

void EditeurDeck::Click_sauvegarder()
{
	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

	if( m_sauvegarder.getGlobalBounds().contains(TestVecteur ) )
	{
		if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
		{
			Deck* TempDeck = DECK->getDeck();

			if( TempDeck)
			{
				bool TempTest = false;

				if( TempDeck->ValideDeck() )
				{
					TempTest = DECK->SaveDeck();
				}

				if( TempTest)
				{
					LOG("Le deck a ete sauvegarder");
				}
				else
				{
					LOG("Erreur lors de la sauvegarde du deck");
				}
			}		
		}
	}	
}

void EditeurDeck::ClickUpDownCarte()
{
	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

	if( m_UpCarte.getGlobalBounds().contains(TestVecteur ) )
	{
		if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
		{		

			m_decalCarte -= 5;

			if(m_decalCarte < 0)
				m_decalCarte = 0;
		}
	}

	if( m_TabNameCarte.size() > m_decalCarte+5 )
	{
		if(m_DownCarte.getGlobalBounds().contains(TestVecteur ) )
		{
			if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
			{
				m_decalCarte += 5;
			}	
		}
	}
}

