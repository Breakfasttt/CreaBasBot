//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 11/02/2013 - 15h15
// Fichier : déclaraction de la classe options.hpp hérité d'une FSM
// Dernière modification : 06/02/2013
//@@@@@@@@@@@@@@@@@@@


#include "Options.hpp"




Coptions::Coptions()
{

}

Coptions::~Coptions()
{

}


bool Coptions::States( StateMachineEvent event, int state )
{
	BeginStateMachine

		//***********************
	State(OPTIONS_INIT)
	OnEnter
		LOG("OPTIONS : OPTIONS_INIT");
		Init_options();
		SetState(OPTIONS_UPDATE);
	OnUpdate
	OnExit
		//#######################

		//***********************
	State(OPTIONS_UPDATE)
	OnEnter
		LOG("OPTIONS : OPTIONS_UPDATE");
	OnUpdate
		Update_options();
		Display_options();
	OnExit
		//#######################


		EndStateMachine
}

//@@@@ fonction générale @@@@
void Coptions::Init_options()
{
	// <<chargement des variables designers local aux options >>
	m_vitesse_volume = DATA->getFloatByName("Opions_Vitesse_Volume");

	// <<chargement du background>>
	sf::Texture* TextureBG = DATA->getTextureByName("MENU_BG");

	if(TextureBG)
		Background_options.setTexture(*TextureBG,true);

	TextureBG = NULL;


	//<<chargement de la Font>>
	sf::Font* Temp = NULL;
	Temp = DATA->getFontByName("datacron") ;

	if( Temp )
	{
		Titre_options.setFont(*Temp);
		Titre_sous_options[0].setFont(*Temp);
		Titre_sous_options[1].setFont(*Temp);
		Options_langues[0].setFont(*Temp);
		Options_langues[1].setFont(*Temp);
		Options_langues[2].setFont(*Temp);
		Options_langues[3].setFont(*Temp);
		m_Volume.setFont(*Temp);
	}


	//<<chargement de la taille>>

	int Taille = DATA->getIntByName("Menu_Choix_Taille");
	Titre_options.setCharacterSize(Taille * 2.0f);
	Titre_sous_options[0].setCharacterSize(Taille);
	Titre_sous_options[1].setCharacterSize(Taille);
	Options_langues[0].setCharacterSize(Taille);
	Options_langues[1].setCharacterSize(Taille);
	Options_langues[2].setCharacterSize(Taille);
	Options_langues[3].setCharacterSize(Taille);
	m_Volume.setCharacterSize(Taille);


	//<<chargement des textes>>

	Titre_options.setString(DATA->getTextByName("OPTIONS_TITRE"));
	Titre_sous_options[0].setString(DATA->getTextByName("OPTIONS_TITRE_LANGUE"));
	Titre_sous_options[1].setString(DATA->getTextByName("OPTIONS_TITRE_VOLUME"));
	Options_langues[0].setString(DATA->getTextByName("OPTIONS_CHOIX_FR"));
	Options_langues[1].setString(DATA->getTextByName("OPTIONS_CHOIX_EN"));
	Options_langues[2].setString(DATA->getTextByName("OPTIONS_CHOIX_DE"));
	Options_langues[3].setString(DATA->getTextByName("OPTIONS_CHOIX_SP"));

	std::ostringstream oss;
	oss << (int)DATA->getGlobalVolume();
	m_Volume.setString(oss.str());


	//<<chargement des positions>>

	Titre_options.setPosition( DATA->getFloatByName("Options_Titre_x"),
							   DATA->getFloatByName("Options_Titre_y") );

	Titre_sous_options[0].setPosition(	DATA->getFloatByName("Options_Titre_Langue_x"),
										DATA->getFloatByName("Options_Titre_Langue_y") );

	Titre_sous_options[1].setPosition(	DATA->getFloatByName("Options_Titre_Volume_x"),
										DATA->getFloatByName("Options_Titre_Volume_y") );

	m_Volume.setPosition(	Titre_sous_options[1].getGlobalBounds().left + Titre_sous_options[1].getGlobalBounds().width + 10 ,
							DATA->getFloatByName("Options_Titre_Volume_y") )  ;


	float Xdep  = DATA->getFloatByName("Options_Langue_x");
	float Ydep  = DATA->getFloatByName("Options_Langue_y");
	float decal = DATA->getFloatByName("Options_Decalage");

	float Longueur = 0.0f;

	for(int i = 0 ; i < 4 ; ++i)
	{
		if(i!=0)
			Options_langues[i].setPosition( Xdep + Longueur  , Ydep );
		else
			Options_langues[i].setPosition( Xdep  , Ydep );

		Longueur += Options_langues[i].getGlobalBounds().width + decal;
	}

	// << couleur >>
	m_choix = -1;
	m_onVolume = false;
	m_onClickVolume = false;
	m_langue = DATA->getLangue();
	Options_langues[ (int)m_langue].setColor(sf::Color::Cyan);

}

void Coptions::Update_options()
{
	change_langue();
	change_volume();
}

void Coptions::Display_options()
{
	RENDER->draw(Background_options);

	RENDER->draw(Titre_options);

	for(int i = 0 ; i < 2 ; ++i)
	{
		RENDER->draw(Titre_sous_options[i]);
	}

	for(int i = 0 ; i < 4 ; ++i)
	{
		RENDER->draw(Options_langues[i]);
	}

	RENDER->draw(m_Volume);
}


//@@@@ fonction outils @@@@

void Coptions::change_langue()
{
	int LastChoix = m_choix ;
	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );
	bool OnText = false;

	for(int i = 0 ; i < 4 ; ++i)
	{

		if( i != (int)m_langue)
		{
			if( Options_langues[i].getGlobalBounds().contains( TestVecteur ) )
			{

				m_choix = i;

				if( LastChoix  != m_choix  && LastChoix != -1 )
				{
					Options_langues[(int)LastChoix].setColor( sf::Color::White );	
					Options_langues[i].setColor( sf::Color::Red );	
				}
				else
				{
					Options_langues[i].setColor( sf::Color::Red );	
				}

				OnText = true;
				break;
			}
		}

	}

	if(!OnText && LastChoix != -1 )
	{
		m_choix = -1;

		for(int i = 0 ; i < 4 ; ++i)
		{
			if( i != (int)m_langue)
				Options_langues[i].setColor( sf::Color::White );	
		}	
	}



	if( EVENT->isMButtonPressed(sf::Mouse::Left) )
	{
		if(m_choix!=-1 )
		{
			switch(m_choix)
			{
				case (int)T_Langue::FRENCH	:	m_langue = T_Langue::FRENCH;	break;
				case (int)T_Langue::ENGLISH	:	m_langue = T_Langue::ENGLISH;	break;
				case (int)T_Langue::DEUTCH	:	m_langue = T_Langue::DEUTCH;	break;
				case (int)T_Langue::SPANISH :	m_langue = T_Langue::SPANISH;	break;
				default : break;
			}

			for(int i = 0 ; i < 4 ; ++i)
			{
				Options_langues[i].setColor( sf::Color::White );	
			}	

			DATA->setLangue(m_langue);
			DATA->ReloadLanguage();
			SetState(OPTIONS_INIT);
		}
		else
		{
			EVENT->AnnuleMouseButton(sf::Mouse::Left);
		}
	}

	
}

void Coptions::change_volume()
{
	int LastChoix = m_choix ;
	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );
	bool lastOnVolume = m_onVolume ;

	if( Titre_sous_options[1].getGlobalBounds().contains(TestVecteur ) )
	{	
		m_onVolume =  true;

		if( m_onVolume != lastOnVolume)
			Titre_sous_options[1].setColor( sf::Color::Cyan);

		if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
		{
			m_onClickVolume= true;
			EVENT->AnnuleMouseButton(sf::Mouse::Left );
			Titre_sous_options[1].setColor( sf::Color::Green);

			float TempVolume = DATA->getGlobalVolume();
			TempVolume += m_vitesse_volume * DATA->getDT();

			if( TempVolume >100.0f)
				TempVolume = 100.0f;

			DATA->setGlobalVolume(TempVolume);
			

			std::ostringstream oss;
			oss << (int)TempVolume;

			m_Volume.setString( oss.str() );
		}
		else if( EVENT->isMButtonPressed(sf::Mouse::Right ) )
		{
			m_onClickVolume = true;
			EVENT->AnnuleMouseButton(sf::Mouse::Right );
			Titre_sous_options[1].setColor( sf::Color::Red);

			float TempVolume = DATA->getGlobalVolume();
			TempVolume -= m_vitesse_volume *  DATA->getDT();

			if( TempVolume < 0.0f )
			TempVolume = 0.0f;

			DATA->setGlobalVolume(TempVolume);

			std::ostringstream oss;
			oss << (int)TempVolume;

			m_Volume.setString( oss.str() );
		}
		else if(m_onClickVolume)
		{
			m_onClickVolume = false;
			Titre_sous_options[1].setColor( sf::Color::Cyan);
		}
	
	}
	else if(m_onVolume)
	{
		m_onVolume = false;
		Titre_sous_options[1].setColor( sf::Color::White);
	}
}

