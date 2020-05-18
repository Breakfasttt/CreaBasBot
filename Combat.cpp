//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 11/03/2013 - 15h15
// Fichier : déclaraction de la classe Combat.hpp hérité d'une FSM
// Dernière modification : 11/03/2013
//@@@@@@@@@@@@@@@@@@@


#include "Combat.hpp"



CCombat::CCombat()
{
	m_Joueurs[HUMAIN] = NULL;
	m_Joueurs[IA] = NULL;
}

CCombat::~CCombat()
{
	delete m_Joueurs[HUMAIN];
	delete m_Joueurs[IA];

	m_Joueurs[HUMAIN] = NULL;
	m_Joueurs[IA] = NULL;
}


bool CCombat::States( StateMachineEvent event, int state )
{
	BeginStateMachine

		//***********************
		State(COMBAT_INIT)
	OnEnter
		LOG("COMBAT : COMBAT_INIT");
		Init_combat();
		SetState(COMBAT_INTRO);

	OnUpdate
		OnExit
		//#######################

		//***********************
		State(COMBAT_INTRO)
	OnEnter
		LOG("COMBAT : COMBAT_INTRO");
		Init_Intro();
	OnUpdate
		DisplayArene();
		Intro();

	OnExit
		//#######################

		//***********************
		State(COMBAT_UPDATE)
	OnEnter
		LOG("COMBAT : COMBAT_UPDATE");
		Init_Joueur();
	OnUpdate
		DisplayArene();
		Update_combat();
		

	OnExit
		//#######################


		//***********************
		State(COMBAT_FIN)
	OnEnter
		LOG("COMBAT : COMBAT_FIN");

		//on détermine le type de fin /victoire du joueur/egaliter/defaite
		ConditionFin();


	OnUpdate
		DisplayArene();
		DisplayFin();
	OnExit
		//#######################


	EndStateMachine
}



void CCombat::Init_combat()
{

	if(m_Joueurs[HUMAIN])
	{
		delete m_Joueurs[HUMAIN] ;
		m_Joueurs[HUMAIN] = NULL;
	}

	if(m_Joueurs[IA])
	{
		delete m_Joueurs[IA] ;
		m_Joueurs[IA] = NULL;
	}

	m_Joueurs[HUMAIN] = new Cjoueur(false);
	m_Joueurs[IA] = new Cjoueur(true);


	sf::Texture* TempTexture = DATA->getTextureByName("ARENE");

	if ( TempTexture )
	{
		m_plateau.setTexture(*TempTexture);
	}

}


// << INTRO >>
void CCombat::Init_Intro()
{
	m_timerIntro = DATA->getFloatByName("Combat_intro_time");
	std::ostringstream oss;
	oss << m_timerIntro;


	m_TextIntro.setString( DATA->getTextByName("COMBAT_INTRO") + oss.str()  ) ;

	m_TextIntro.setPosition( DATA->getFloatByName( "Combat_intro_infos_x" ) ,
								 DATA->getFloatByName( "Combat_intro_infos_y" ) ) ;
}

void CCombat::Intro()
{
	float TempDt  = DATA->getDT() ; 
	m_timerIntro -= TempDt;

	if(  m_timerIntro <= 0.0f)
	{
		SetState(COMBAT_UPDATE);
	}
	else
	{
		int Infos = (int)m_timerIntro;
		std::ostringstream oss;
		oss << Infos;
		m_TextIntro.setString( DATA->getTextByName("COMBAT_INTRO") + oss.str()  ) ;
	
	}
	

	RENDER->draw(m_TextIntro);

}

// << update>>


void CCombat::Init_Joueur()
{
	if( m_Joueurs[HUMAIN] && m_Joueurs[IA] )
	{
		m_Joueurs[HUMAIN]->Initialize();
		m_Joueurs[IA]->Initialize();
	
		m_Joueurs[HUMAIN]->setAdversaire(m_Joueurs[IA]);
		m_Joueurs[IA]->setAdversaire(m_Joueurs[HUMAIN]);
	
	}
}

void CCombat::Update_combat()
{	
	if( m_Joueurs[HUMAIN] && m_Joueurs[IA] )
	{
	
		m_Joueurs[HUMAIN]->Update();
		m_Joueurs[IA]->Update();		
	}


	if( m_Joueurs[HUMAIN]->estMort() || m_Joueurs[IA]->estMort() )
	{
		SetState(COMBAT_FIN);
	}

}

// << Affichage >>

void CCombat::DisplayArene()
{
	RENDER->draw(m_plateau);
}

// << autre >>


void CCombat::ConditionFin()
{
	m_InfosFin.setPosition( DATA->getFloatByName("Combat_fin_x") ,  DATA->getFloatByName("Combat_fin_y") );

	// choix de la fin
	int VieJoueur = m_Joueurs[HUMAIN]->getRobot()->getVie();
	int VieAi = m_Joueurs[IA]->getRobot()->getVie();

	if( VieJoueur > VieAi)
		m_InfosFin.setString( DATA->getTextByName("COMBAT_FIN_VICTOIRE") ) ;
	else if( VieJoueur < VieAi)
		m_InfosFin.setString( DATA->getTextByName("COMBAT_FIN_DEFAITE") ) ;
	else if( VieJoueur == VieAi)
		m_InfosFin.setString( DATA->getTextByName("COMBAT_FIN_EGALITE") ) ;
}

void CCombat::DisplayFin()
{
	RENDER->draw(m_InfosFin);
}

