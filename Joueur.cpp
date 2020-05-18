//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 11/03/2013 - 15h15
// Fichier : déclaraction de la classe joueur.hpp hérité d'une FSM
// Dernière modification : 11/03/2013
//@@@@@@@@@@@@@@@@@@@


#include "Joueur.hpp"


Cjoueur::Cjoueur()
{
	LOG("creation d'un joueur");
}

Cjoueur::Cjoueur(bool _b)
{
	m_mort= false;
	m_IA = _b;
	m_DeckJoueur = NULL;
	m_RobotJoueur = NULL;
	m_adversaire = NULL;

	m_IndexCartePioche[0] = -1;
	m_IndexCartePioche[1] = -1;
	m_IndexCartePioche[2] = -1;

	m_CarteRestante = MAX_CARTE - 1;
	m_carteChoisie = -1;
	 
	if(m_IA)
	{
		LOG("creation d'une IA");
		m_positionCarteChoisie.x = DATA->getFloatByName("Combat_IA_CarteChoisie_x");
		m_positionCarteChoisie.y = DATA->getFloatByName("Combat_IA_CarteChoisie_y");
	}
	else
	{
		LOG("creation d'un joueur");

		m_positionCarteChoisie.x = DATA->getFloatByName("Combat_joueur_CarteChoisie_x");
		m_positionCarteChoisie.y = DATA->getFloatByName("Combat_joueur_CarteChoisie_y");
	}

}

Cjoueur::~Cjoueur()
{

	LOG("destruction d'un joueur")

	m_adversaire = NULL;

	if( m_DeckJoueur)
	{
		delete m_DeckJoueur ;
		m_DeckJoueur = NULL;
	}

	if( m_RobotJoueur)
	{
		delete m_RobotJoueur ;
		m_RobotJoueur = NULL;
	}

	

}


//@@@@ fonction general @@@@

bool Cjoueur::States( StateMachineEvent event, int state )
{
	BeginStateMachine

		//***********************
		State(JOUEUR_INIT)
		OnEnter
		if(m_IA)
		{
			LOG("JOUEUR_IA : JOUEUR_INIT");
		}
		else
		{
			LOG("JOUEUR : JOUEUR_INIT");
		}

		InitialisationJoueur();
		SetState(JOUEUR_MELANGE);

	OnUpdate
		OnExit
		//#######################



		//***********************
		State(JOUEUR_MELANGE)
	OnEnter

		MelangeCarte();
		SetState(JOUEUR_PIOCHE);

	OnUpdate
		

	OnExit
		//#######################


		//***********************
		State(JOUEUR_PIOCHE)
	OnEnter
		
	if ( m_RobotJoueur->getVie() >0)
	{
		if(m_IA)
		{
			LOG("JOUEUR_IA : JOUEUR_PIOCHE");
			PiocheCarte_ia();
		}
		else
		{
			LOG("JOUEUR : JOUEUR_PIOCHE");
			PiocheCarte();
		}


		actualisationInfos();
		SetState(JOUEUR_POSE);
	}
	else
	{
		SetState(JOUEUR_FIN);
	}

	OnUpdate


		OnExit
		//#######################



		//***********************
		State(JOUEUR_POSE)
	OnEnter
		
		if(m_IA)
		{
			LOG("JOUEUR_IA : JOUEUR_POSE");
		}
		else
		{
			LOG("JOUEUR : JOUEUR_POSE");
		}

		m_InfosPhase.setString( DATA->getTextByName("COMBAT_INFOS_PHASE_POSE") );

	OnUpdate

		AffichageDeck();
		AffichageInfos();
		AfficheInfosCarte();


		if(m_IA)
		{
			if( AttenteParTimer_ia() )
			{
				PoseCarte_ia();
			}
		}
		else
		{
			PoseCarte();
		}


	OnExit
		//#######################


		//***********************
		State(JOUEUR_RESOLUTION)
	OnEnter
		if(m_IA)
		{
			LOG("JOUEUR_IA : JOUEUR_RESOLUTION");
		}
		else
		{
			LOG("JOUEUR : JOUEUR_RESOLUTION");
		}
		m_InfosPhase.setString( DATA->getTextByName("COMBAT_INFOS_PHASE_RESOLUTION") );
		InitResolution();

	OnUpdate
		AffichageDeck();
		AffichageInfos();
		AfficheInfosCarte();

		Resolutions();
		actualisationInfos();
		FinResolution();

	OnExit
		
		//#######################


		//***********************
		State(JOUEUR_ATTENTE)
	OnEnter
		
		if(m_IA)
		{
			LOG("JOUEUR_IA : JOUEUR_ATTENTE");
		}
		else
		{
			LOG("JOUEUR : JOUEUR_ATTENTE");
		}

		m_InfosPhase.setString( DATA->getTextByName("COMBAT_INFOS_PHASE_ATTENTE") );
		m_enAttente = true; 

	OnUpdate
		AffichageDeck();
		AffichageInfos();
		AfficheInfosCarte();
		

		if( m_adversaire)
		{
			if ( m_adversaire->estPret() || m_adversaire->getStateJoueur() == JOUEUR_RESOLUTION )
			{
				if(m_IA)
				{
					LOG("JOUEUR_IA : adversaire pret");
				}
				else
				{
					LOG("JOUEUR : adversaire pret");
				}


				SetState( JOUEUR_RESOLUTION ) ;

			}
		}

	OnExit
		m_enAttente = false;
		//#######################

		//***********************
		State(JOUEUR_ATTENTE_PIOCHE)
	OnEnter
		
		if(m_IA)
		{
			LOG("JOUEUR_IA : JOUEUR_ATTENTE_PIOCHE");
		}
		else
		{
			LOG("JOUEUR : JOUEUR_ATTENTE_PIOCHE");
		}

		m_InfosPhase.setString( DATA->getTextByName("COMBAT_INFOS_PHASE_ATTENTE") );
		m_enAttente = true; 

	OnUpdate
		AffichageDeck();
		AffichageInfos();
		AfficheInfosCarte();
		

		if( m_adversaire)
		{
			if ( m_adversaire->estPret() || m_adversaire->getStateJoueur() == JOUEUR_PIOCHE
											|| m_adversaire->getStateJoueur() == JOUEUR_POSE)
			{
				if(m_IA)
				{
					LOG("JOUEUR_IA : adversaire pret");
				}
				else
				{
					LOG("JOUEUR : adversaire pret");
				}


				SetState( JOUEUR_PIOCHE ) ;			
			}
		}


	OnExit
		m_enAttente = false;
		//#######################
		//***********************
		State(JOUEUR_FIN)
	OnEnter
		
		if(m_IA)
		{
			LOG("JOUEUR_IA : JOUEUR_FIN");
		}
		else
		{
			LOG("JOUEUR : JOUEUR_FIN");
		}
		m_mort = true;

	OnUpdate


	OnExit
		//#######################


		EndStateMachine
}


//@@@@ fonction de jeu @@@@

// << init >> 

void Cjoueur::InitialisationJoueur()
{
	LOG("Creation d'une copie du deck")
	
	m_DeckJoueur = NULL;
	m_DeckJoueur =  new Deck( *(DECK->getDeck()) );
	m_RobotJoueur = NULL;
	
	m_enAttente = false;

	if(m_IA)
	{
		m_timerIA = DATA->getFloatByName("Combat_IA_Timer");
		m_RobotJoueur = new CRobot(true);
	}
	else
	{
		m_timerIA = 0.0f;
		m_RobotJoueur = new CRobot(false);
	}

	InitialisationTexte();
}

void Cjoueur::InitialisationTexte()
{
	// << position des textes >>

	float X , Y ,decal;
	unsigned int size = DATA->getIntByName("Combat_infos_size");

	decal = DATA->getFloatByName("Combat_infos_decalage");

	if(m_IA)
	{
		X = DATA->getFloatByName("Combat_ia_infos_robot_x");
		Y = DATA->getFloatByName("Combat_ia_infos_robot_y");			
	}
	else
	{
		X = DATA->getFloatByName("Combat_joueur_infos_robot_x");
		Y = DATA->getFloatByName("Combat_joueur_infos_robot_y");
	}


	int i = 0 ;

	m_InfosNbreCarte.setPosition( X , Y + i * decal);
	++i;
	m_InfosVieRobot.setPosition( X , Y + i * decal);
	++i;
	m_InfosAttaqueRobot.setPosition( X , Y + i * decal);
	++i;
	m_InfosDefenseRobot.setPosition( X , Y + i * decal);
	++i;
	m_InfosPhase.setPosition( X , Y + i * decal);

	X = DATA->getFloatByName("Combat_carte_infos_x");
	Y = DATA->getFloatByName("Combat_carte_infos_y");
	decal = DATA->getFloatByName("Combat_decalage_infoscarte");

	m_NomCarte.setPosition(X,Y);
	m_DescriptionCarte.setPosition(X,Y+decal);


	// character size 

	m_InfosNbreCarte.setCharacterSize(size);
	m_InfosVieRobot.setCharacterSize(size);
	m_InfosAttaqueRobot.setCharacterSize(size);
	m_InfosDefenseRobot.setCharacterSize(size);
	m_InfosPhase.setCharacterSize(size);

	m_NomCarte.setCharacterSize(size);
	m_DescriptionCarte.setCharacterSize(size);

	//chargement des textes :

	m_infosNbrecarteStr = DATA->getTextByName("COMBAT_INFOS_NBRE_CARTE");
	m_infosVieStr = DATA->getTextByName("COMBAT_INFOS_VIE");
	m_infosAttqStr= DATA->getTextByName("COMBAT_INFOS_ATTAQUE");
	m_infosDefStr = DATA->getTextByName("COMBAT_INFOS_DEFENSE");

	m_NomCarteStr= DATA->getTextByName("COMBAT_INFOS_CARTE_NOM");
	m_DescriptionCarteStr = DATA->getTextByName("COMBAT_INFOS_CARTE_DESC");

	m_InfosNbreCarte.setString(m_infosNbrecarteStr);
	m_InfosVieRobot.setString(m_infosVieStr);
	m_InfosAttaqueRobot.setString(m_infosAttqStr);
	m_InfosDefenseRobot.setString(m_infosDefStr);

	m_NomCarte.setString(m_NomCarteStr);
	m_DescriptionCarte.setString(m_DescriptionCarteStr);

}

void Cjoueur::actualisationInfos()
{
	if( m_RobotJoueur)
	{

		std::ostringstream oss ,oss1, oss2,oss3;
		oss << m_RobotJoueur->getVie();
		m_InfosVieRobot.setString(m_infosVieStr + oss.str());

		oss1 << m_RobotJoueur->getAttaque();
		m_InfosAttaqueRobot.setString(m_infosAttqStr+ oss1.str());

		oss2 << m_RobotJoueur->getDefense();
		m_InfosDefenseRobot.setString(m_infosDefStr+ oss2.str());	

		oss3 << m_CarteRestante+1 ;
		m_InfosNbreCarte.setString(m_infosNbrecarteStr + oss3.str() );

	}
}


void Cjoueur::setAdversaire(Cjoueur* _j)
{
	m_adversaire = _j;

	actualisationInfos();
}

// << commun >>

void Cjoueur::MelangeCarte()
{
	m_DeckJoueur->melangeDeck();
}

void Cjoueur::AffichageDeck()
{
	
	// affichage des cartes piocher 

	for (int i = 0 ; i < 3 ; ++i)
	{
		if( m_IndexCartePioche[i] >=0 && m_IndexCartePioche[i] < MAX_CARTE )
		{
			if(  m_DeckJoueur->getCarte( m_IndexCartePioche[i] ) )
				m_DeckJoueur->getCarte( m_IndexCartePioche[i] )->Affiche_carte();

		}	
	}

	//affichage de la carte choisie

	if( m_carteChoisie > -1 &&  m_carteChoisie < 15)
	{
		//m_DeckJoueur->getCarte( m_carteChoisie )->setPositionCarte(m_positionCarteChoisie);
		m_DeckJoueur->getCarte( m_carteChoisie )->Affiche_carte();
	}

	//affichage robot 

	if(m_RobotJoueur)
		m_RobotJoueur->Display();


	// affichage debug

	if( EVENT->isKeyPressed(sf::Keyboard::F2 )  )
	{
		if(m_IA && DDEBUG)
		{
			if( m_IndexCartePioche[0] != -1 )
				m_DeckJoueur->getCarte( m_IndexCartePioche[0] )->Retourner();
			if( m_IndexCartePioche[1] != -1 )
				m_DeckJoueur->getCarte( m_IndexCartePioche[1] )->Retourner();
			if( m_IndexCartePioche[2] != -1 )
				m_DeckJoueur->getCarte( m_IndexCartePioche[2] )->Retourner();
		}
		else
		{
			EVENT->AnnuleKeyPressed(sf::Keyboard::F2);
		}
	}

	 CommandeDebug();

}

void Cjoueur::AffichageInfos()
{
	RENDER->draw(m_InfosNbreCarte);
	RENDER->draw(m_InfosVieRobot);
	RENDER->draw(m_InfosAttaqueRobot);
	RENDER->draw(m_InfosDefenseRobot);
	RENDER->draw(m_InfosPhase);

}


// << joueur >>


void Cjoueur::PiocheCarte()
{
	m_carteChoisie = -1;

	if( m_CarteRestante >=0 )
	{
		for (int i = 0 ; i < 3 ; ++i)
		{
			if( m_IndexCartePioche[i] == -1)
			{
				m_IndexCartePioche[i] = m_CarteRestante;
				m_DeckJoueur->getCarte( m_IndexCartePioche[i] )->Retourner();


				m_DeckJoueur->getCarte( m_IndexCartePioche[i] )->setPositionCarte( 
																	sf::Vector2f(	DATA->getFloatByName("Combat_joueur_CartePioche_x") ,
																					DATA->getFloatByName("Combat_joueur_CartePioche_y") 
																					+ i * DATA->getFloatByName("Combat_Decal_CartePiocher" ) ) ) ;	


				m_CarteRestante--;
			}
		}
	}
}


void Cjoueur::PoseCarte()
{

	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

	int modulo = 0;

	if(  m_IndexCartePioche[0] != -1)
		modulo++;
	if(  m_IndexCartePioche[1] != -1)
		modulo++;
	if(  m_IndexCartePioche[2] != -1)
		modulo++;

	if (modulo >0  &&  m_RobotJoueur->getVie() > 0)
	{
		for(int i = 0 ; i < 3 ; ++i)
		{
			if(  m_IndexCartePioche[i] > -1)
			{

				Carte* TempCarte =  m_DeckJoueur->getCarte( m_IndexCartePioche[i] ) ;

				if( TempCarte->getGeneralSprite().getGlobalBounds().contains( TestVecteur ) )
				{
					if( EVENT->isMButtonPressed(sf::Mouse::Left) )
					{
						if(  m_carteChoisie == -1)
						{
							m_carteChoisie = m_IndexCartePioche[i];
							m_IndexCartePioche[i] = -1;
							m_DeckJoueur->getCarte( m_carteChoisie )->setPositionCarte(m_positionCarteChoisie);					
							SetState( JOUEUR_ATTENTE ) ;
						}
						else
						{
							EVENT->AnnuleMouseButton(sf::Mouse::Left) ;
						}
					}	
				}
			}
		}
	}
	else
	{
		SetState(JOUEUR_FIN);
	}
}


void Cjoueur::InitResolution()
{
	if ( m_RobotJoueur)
	{
		m_RobotJoueur->setCible( m_adversaire->getRobot() );
		m_RobotJoueur->setFSM( m_DeckJoueur->getCarte( m_carteChoisie )->getScriptCarte() );
		m_RobotJoueur->InitFSM() ;
	
	}
}

void Cjoueur::Resolutions()
{
	if( m_RobotJoueur)
	{
		m_RobotJoueur->UpdateFSM();
	}
}

void Cjoueur::FinResolution()
{
	if( m_RobotJoueur)
	{
		if ( m_RobotJoueur->ActionFini() )
		{
			
			if( m_IA)
			{
				if( AttenteParTimer_ia() )
				{
					m_RobotJoueur->setFSM(NULL);
					SetState(JOUEUR_ATTENTE_PIOCHE);
				}
				
			}
			else
			{
				m_RobotJoueur->setFSM(NULL);
				SetState(JOUEUR_ATTENTE_PIOCHE);
			}
		}
	}	
}

// << IA >>

void Cjoueur::PiocheCarte_ia()
{

	m_carteChoisie = -1;
	if( m_CarteRestante >=0 &&  m_RobotJoueur->getVie() > 0  )
	{
		for (int i = 0 ; i < 3 ; ++i)
		{
			if( m_IndexCartePioche[i] == -1)
			{
				m_IndexCartePioche[i] = m_CarteRestante;
			


				m_DeckJoueur->getCarte( m_IndexCartePioche[i] )->setPositionCarte( 
																	sf::Vector2f(	DATA->getFloatByName("Combat_IA_CartePioche_x") ,
																					DATA->getFloatByName("Combat_IA_CartePioche_y") 
																					+ i * DATA->getFloatByName("Combat_Decal_CartePiocher" ) ) ) ;	


				m_CarteRestante--;
			}
		}
	}
	else
	{
		SetState( JOUEUR_FIN ) ;
	}
}

void Cjoueur::PoseCarte_ia()
{

	int modulo = 0;

	if(  m_IndexCartePioche[0] != -1)
		modulo++;
	if(  m_IndexCartePioche[1] != -1)
		modulo++;
	if(  m_IndexCartePioche[2] != -1)
		modulo++;


	if( modulo >0 &&  m_RobotJoueur->getVie() > 0)
	{	
		int randChoix = -1;

		do
		{
		 randChoix = rand()%3 ;
		}while( m_IndexCartePioche[randChoix] == -1  );

		m_carteChoisie = m_IndexCartePioche[randChoix];


		m_IndexCartePioche[randChoix] = -1;

	
		if( m_DeckJoueur->getCarte( m_carteChoisie )->isRetourner() )
		{
			m_DeckJoueur->getCarte( m_carteChoisie )->Retourner();
		}

		m_DeckJoueur->getCarte( m_carteChoisie )->setPositionCarte(m_positionCarteChoisie);					
		SetState( JOUEUR_ATTENTE ) ;
	}
}

bool Cjoueur::AttenteParTimer_ia()
{

	float dt = DATA->getDT();
	m_timerIA -= dt;

	if(  m_timerIA <=0.0f)
	{
		m_timerIA = DATA->getFloatByName("Combat_IA_Timer");
		return true;
	}

	return false;

}

void Cjoueur::Resolutions_ia()
{

}



bool Cjoueur::estMort()
{
	return m_mort;
}

bool Cjoueur::estPret()
{
	return m_enAttente;
}

void  Cjoueur::CommandeDebug()
{
	//commande de debug pour le joueur
	if( !m_IA && DDEBUG)
	{

		if(EVENT->isKeyPressed(sf::Keyboard::Numpad1) )
		{
			m_RobotJoueur->setVie(20);
			actualisationInfos();
		}

		if(EVENT->isKeyPressed(sf::Keyboard::Numpad2) )
		{
			m_RobotJoueur->addVie(1);
			actualisationInfos();
		}

		if(EVENT->isKeyPressed(sf::Keyboard::Numpad3) )
		{
			m_RobotJoueur->addVie(-1);
			actualisationInfos();
		}

		if(EVENT->isKeyPressed(sf::Keyboard::Numpad4) )
		{
			m_RobotJoueur->setAttaque(1);
			actualisationInfos();
		}

		if(EVENT->isKeyPressed(sf::Keyboard::Numpad5) )
		{
			m_RobotJoueur->addAttaque(1);
			actualisationInfos();
		}

		if(EVENT->isKeyPressed(sf::Keyboard::Numpad6) )
		{
			m_RobotJoueur->addAttaque(-1);
			actualisationInfos();
		}

		if(EVENT->isKeyPressed(sf::Keyboard::Numpad7) )
		{
			m_RobotJoueur->setDefense(1);
			actualisationInfos();
		}

		if(EVENT->isKeyPressed(sf::Keyboard::Numpad8) )
		{
			m_RobotJoueur->addDefense(1);
			actualisationInfos();
		}

		if(EVENT->isKeyPressed(sf::Keyboard::Numpad9) )
		{
			m_RobotJoueur->addDefense(-1);
			actualisationInfos();
		}

	}

}

void Cjoueur::AfficheInfosCarte()
{
	if (!m_IA)
	{
		sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

		int modulo = 0;

		if(  m_IndexCartePioche[0] != -1)
			modulo++;
		if(  m_IndexCartePioche[1] != -1)
			modulo++;
		if(  m_IndexCartePioche[2] != -1)
			modulo++;

		// affichage de ses propres cartes
		if (modulo >0  )
		{
			for(int i = 0 ; i < 3 ; ++i)
			{
				if(  m_IndexCartePioche[i] > -1)
				{

					Carte* TempCarte =  m_DeckJoueur->getCarte( m_IndexCartePioche[i] ) ;

					if( TempCarte->getGeneralSprite().getGlobalBounds().contains( TestVecteur ) )
					{
						std::string TempName = TempCarte->getInfosCarte().m_name;
						std::string Tempdesc = TempCarte->getInfosCarte().m_description;

						m_NomCarte.setString(m_NomCarteStr + TempName);
						m_DescriptionCarte.setString(m_DescriptionCarteStr + Tempdesc);

						RENDER->draw(m_NomCarte);
						RENDER->draw(m_DescriptionCarte);
						break;

					}
				}
			}
		}	

		//Affichage de la carte ennemi utilisé

		if( m_adversaire )
		{		
			Deck* TempDeck = m_adversaire->getDeck();

			if ( TempDeck )
			{
				int index = m_adversaire->getCarteChoisie();

				if (index >= 0 && index < MAX_CARTE)
				{
					Carte* Tempcarte =  TempDeck->getCarte(index) ;
					if(Tempcarte)
					{

						if (Tempcarte->getGeneralSprite().getGlobalBounds().contains( TestVecteur ) )
						{
							std::string TempName = Tempcarte->getInfosCarte().m_name;
							std::string Tempdesc = Tempcarte->getInfosCarte().m_description;

							m_NomCarte.setString(m_NomCarteStr + TempName);
							m_DescriptionCarte.setString(m_DescriptionCarteStr + Tempdesc);

							RENDER->draw(m_NomCarte);
							RENDER->draw(m_DescriptionCarte);
						}			
					}				
				}			
			}	
		}
	}
}
