//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 04/03/2013 - 14h44
// Fichier : définition de la classe EditeurCarte.hpp hérité d'une FSM
// Dernière modification : 04/03/2013
//@@@@@@@@@@@@@@@@@@@


#include "EditeurCarte.hpp"


bool EditeurCarte::States( StateMachineEvent event, int state )
{
	BeginStateMachine

		//***********************
		State(EditCard_INIT)

		OnEnter
		LOG("EditeurCarte : EditCard_INIT");
	Init_EditeurCarte();
	Init_ListCarte();
	init_ListScript();
	init_ListIllus();
	SetState(EditCard_Update);
	OnUpdate
		OnExit
		//#######################

		//***********************
		State(EditCard_Update)

		OnEnter
		LOG("EditeurCarte : EditCard_Update");
	OnUpdate

		//ajouter/Supprimer
		IsClickSurNouveau();
	ClickSurSupprimer();
	IsClickSurSauvegarder();

	//selectionner une carte
	ClickUpDownCarte();
	ClickSurCarte();

	//entrer en mode édition (seulement si carte dispo)
	ClickSurNom();
	ClickSurScript();
	ClickSurIllustration();
	ClickSurDescription();


	Display_Editeur_Carte();
	OnExit
		//#######################

		//***********************
		State(EditCard_EditName)

		OnEnter
		LOG("EditeurCarte : EditCard_EditName");
		EVENT->ReinitTextEntered();
	OnUpdate

		Ajouter_Nom();

		Display_Editeur_Carte();
	OnExit
		//#######################
		//***********************
		State(EditCard_EditScript)

		OnEnter
		LOG("EditeurCarte : EditCard_EditScript");
	OnUpdate

		ClickUpDownScript();
		Ajouter_Script();

	Display_Editeur_Carte();
	OnExit
		//#######################
		//***********************
		State(EditCard_EditIllus)

		OnEnter
		LOG("EditeurCarte : EditCard_EditIllus");
	OnUpdate

		ClickUpDownIllus();
		Ajouter_illustration();

	Display_Editeur_Carte();
	OnExit
		//#######################
		//***********************
		State(EditCard_EditDesc)

		OnEnter
		LOG("EditeurCarte : EditCard_EditDesc");
		EVENT->ReinitTextEntered();
	OnUpdate

		Ajouter_Description();
		Display_Editeur_Carte();
	OnExit
		//#######################


		EndStateMachine
}



// ## Fonction d'init
void EditeurCarte::Init_EditeurCarte()
{
	// << init des décalage >>

	m_decalCarte = 0;
	m_decalScript = 0;
	m_decalIllustration = 0;
	m_CarteEnCours = NULL;
	m_IndexCarteEnCours = -1;


	// << init de l'apperçu de l'illustration

	m_illustrationEnCours.setPosition(	DATA->getFloatByName("Editeur_c_appercuIllus_x"),
		DATA->getFloatByName("Editeur_c_appercuIllus_y") );

	// << chargement des textes >>
	// -- chargement des titres --

	m_TitreListeCarte.setString( DATA->getTextByName("EDITEUR_CARTE_TITRECARTE") );
	m_TitreListeScript.setString( DATA->getTextByName("EDITEUR_CARTE_TITRESCRIPT") );
	m_TitreListeIllustration.setString( DATA->getTextByName("EDITEUR_CARTE_TITREILLUS") );


	// -- chargement des infos --
	m_nom.setString( DATA->getTextByName("EDITEUR_CARTE_NOMCARTE") );
	m_Script.setString( DATA->getTextByName("EDITEUR_CARTE_NOMSCRIPT") );
	m_Illustration.setString( DATA->getTextByName("EDITEUR_CARTE_NOMILLUSTRATION") );
	m_Description.setString( DATA->getTextByName("EDITEUR_CARTE_DESCRIPTION") );

	// -- chargement des text boutons
	m_sauvegarder.setString( DATA->getTextByName("EDITEUR_CARTE_SAVE") );
	m_descCarte.setString( DATA->getTextByName("EDITEUR_CARTE_DOWN") );
	m_descScript.setString( DATA->getTextByName("EDITEUR_CARTE_DOWN") );
	m_descIllus.setString( DATA->getTextByName("EDITEUR_CARTE_DOWN") );
	m_monteCarte.setString( DATA->getTextByName("EDITEUR_CARTE_UP") );
	m_monteScript.setString( DATA->getTextByName("EDITEUR_CARTE_UP") );
	m_monteIllus.setString( DATA->getTextByName("EDITEUR_CARTE_UP") );
	m_Nouveau.setString( DATA->getTextByName("EDITEUR_CARTE_NEW") );
	m_Supprimer.setString( DATA->getTextByName("EDITEUR_CARTE_DELETE") );

	// << chargement des Taille de texte  >>

	// -- chargement des titres --

	//m_TitreListeCarte.setCharacterSize( DATA->getIntByName("EDITEUR_CARTE_TITRECARTE") );
	//m_TitreListeScript.setCharacterSize( DATA->getIntByName("EDITEUR_CARTE_TITRESCRIPT") );
	//m_TitreListeIllustration.setCharacterSize( DATA->getIntByName("EDITEUR_CARTE_TITREILLUS") );

	// -- chargement des infos --
	m_nom.setCharacterSize( DATA->getIntByName("Menu_Choix_Taille") );
	m_Script.setCharacterSize( DATA->getIntByName("Menu_Choix_Taille") );
	m_Illustration.setCharacterSize( DATA->getIntByName("Menu_Choix_Taille") );
	m_Description.setCharacterSize( DATA->getIntByName("Menu_Choix_Taille") );

	// -- chargement des text boutons
	m_sauvegarder.setCharacterSize( DATA->getIntByName("Menu_Choix_Taille") );
	m_descCarte.setCharacterSize( DATA->getIntByName("Menu_Choix_Taille") );
	m_descScript.setCharacterSize( DATA->getIntByName("Menu_Choix_Taille") );
	m_descIllus.setCharacterSize( DATA->getIntByName("Menu_Choix_Taille") );
	m_monteCarte.setCharacterSize( DATA->getIntByName("Menu_Choix_Taille") );
	m_monteScript.setCharacterSize( DATA->getIntByName("Menu_Choix_Taille") );
	m_monteIllus.setCharacterSize( DATA->getIntByName("Menu_Choix_Taille") );


	// << chargement des positions >>

	m_decal_y = DATA->getFloatByName("EDITEUR_c_decal");

	// -- position des titres

	m_TitreListeCarte.setPosition(	DATA->getFloatByName("Editeur_c_titre_carte_x") ,
		DATA->getFloatByName("Editeur_c_titre_carte_y") );

	m_TitreListeScript.setPosition(	DATA->getFloatByName("Editeur_c_titre_script_x") ,
		DATA->getFloatByName("Editeur_c_titre_script_y") );

	m_TitreListeIllustration.setPosition(	DATA->getFloatByName("Editeur_c_titre_Illus_x") ,
		DATA->getFloatByName("Editeur_c_titre_Illus_y") );

	// -- position des infos

	m_nom.setPosition(	DATA->getFloatByName("Editeur_c_infos_x") ,
		DATA->getFloatByName("Editeur_c_infos_y") );

	m_Script.setPosition(	DATA->getFloatByName("Editeur_c_infos_x") ,
		DATA->getFloatByName("Editeur_c_infos_y") + m_decal_y * 2.0f );

	m_Illustration.setPosition(	DATA->getFloatByName("Editeur_c_infos_x") ,
		DATA->getFloatByName("Editeur_c_infos_y") + m_decal_y * 4.0f );

	m_Description.setPosition(	DATA->getFloatByName("Editeur_c_infos_x") ,
		DATA->getFloatByName("Editeur_c_infos_y") + m_decal_y * 6.0f );

	//-- position des bouton

	m_sauvegarder.setPosition(	DATA->getFloatByName("Editeur_c_save_x") ,
		DATA->getFloatByName("Editeur_c_save_y") );

	m_descCarte.setPosition(	DATA->getFloatByName("Editeur_c_down_card_x") ,
		DATA->getFloatByName("Editeur_c_down_card_y") );

	m_monteCarte.setPosition(	DATA->getFloatByName("Editeur_c_up_card_x") ,
		DATA->getFloatByName("Editeur_c_up_card_y") );

	m_descScript.setPosition(	DATA->getFloatByName("Editeur_c_down_script_x") ,
		DATA->getFloatByName("Editeur_c_down_script_y") );

	m_monteScript.setPosition(	DATA->getFloatByName("Editeur_c_up_script_x") ,
		DATA->getFloatByName("Editeur_c_up_script_y") );

	m_descIllus.setPosition(	DATA->getFloatByName("Editeur_c_down_illus_x") ,
		DATA->getFloatByName("Editeur_c_down_illus_y") );

	m_monteIllus.setPosition(	DATA->getFloatByName("Editeur_c_up_illus_x") ,
		DATA->getFloatByName("Editeur_c_up_illus_y") );

	m_Nouveau.setPosition(	DATA->getFloatByName("Editeur_c_new_x") ,
		DATA->getFloatByName("Editeur_c_new_y") );

	m_Supprimer.setPosition(	DATA->getFloatByName("Editeur_c_new_x") ,
		DATA->getFloatByName("Editeur_c_new_y") + m_decal_y );

}

void EditeurCarte::Init_ListCarte()
{

	while(m_TabCarte.size() >0 )
	{
		m_TabCarte.pop_back();
	}

	while(m_TabNameCarte.size() >0 )
	{
		m_TabNameCarte.pop_back();
	}

	int NbreCarte = BIBLI->getNbreCarte();

	m_TabNameCarte.clear();
	m_TabCarte.clear();

	for(int i =0 ; i < NbreCarte ; ++i)
	{
		m_TabCarte.push_back(  BIBLI->getInfosCartes(i) );	
	}

	float X = DATA->getFloatByName("Editeur_c_up_card_x");
	float Y = DATA->getFloatByName("Editeur_c_up_card_y");
	float Decal = DATA->getFloatByName("EDITEUR_c_decal");
	int Position = 0;

	for(unsigned int i =0 ; i < m_TabCarte.size() ; ++i)
	{
		sf::Text TempText;
		TempText.setCharacterSize(18);
		TempText.setString(m_TabCarte[i].m_name);
		TempText.setPosition( X , Y + (Position+1)*Decal);

		Position++;

		if(Position==5)
			Position = 0;

		m_TabNameCarte.push_back(TempText);	
	}

}

void EditeurCarte::init_ListScript()
{

	while(m_TabScript.size() >0 )
	{
		m_TabScript.pop_back();
	}

	m_TabScript.clear();

	int NbreScript = BIBLI->getNbreScript();

	float X = DATA->getFloatByName("Editeur_c_up_script_x");
	float Y = DATA->getFloatByName("Editeur_c_up_script_y");
	float Decal = DATA->getFloatByName("EDITEUR_c_decal");
	int Position = 0;

	for(int i =0 ; i < NbreScript ; ++i)
	{
		sf::String TempString = BIBLI->getScriptName(i);
		sf::Text TempText;
		TempText.setCharacterSize(16);
		TempText.setString(TempString);
		TempText.setPosition( X , Y + (Position+1)*Decal);

		Position++;

		if(Position==5)
			Position = 0;

		m_TabScript.push_back(TempText);	
	}
}

void EditeurCarte::init_ListIllus()
{

	while(m_TabIllustration.size() >0 )
	{
		m_TabIllustration.pop_back();
	}

	m_TabIllustration.clear();

	int NbreScript = BIBLI->getNbreIllus();

	float X = DATA->getFloatByName("Editeur_c_up_illus_x");
	float Y = DATA->getFloatByName("Editeur_c_up_illus_y");
	float Decal = DATA->getFloatByName("EDITEUR_c_decal");
	int Position = 0;

	for(int i =0 ; i < NbreScript ; ++i)
	{
		sf::String TempString = BIBLI->getIllusName(i);
		sf::Text TempText;
		TempText.setCharacterSize(16);
		TempText.setString(TempString);
		TempText.setPosition( X , Y + (Position+1)*Decal);

		Position++;

		if(Position==5)
			Position = 0;

		m_TabIllustration.push_back(TempText);	
	}
}


// ## Fonction d'affichage

void EditeurCarte::Display_Editeur_Carte()
{
	RENDER->draw(m_TitreListeCarte);
	RENDER->draw(m_TitreListeScript);
	RENDER->draw(m_TitreListeIllustration);

	RENDER->draw(m_nom);
	RENDER->draw(m_Script);
	RENDER->draw(m_Illustration);
	RENDER->draw(m_Description);

	RENDER->draw(m_sauvegarder);
	RENDER->draw(m_descCarte);
	RENDER->draw(m_descScript);
	RENDER->draw(m_descIllus);
	RENDER->draw(m_monteCarte);
	RENDER->draw(m_monteScript);
	RENDER->draw(m_monteIllus);
	RENDER->draw(m_Nouveau);
	RENDER->draw(m_Supprimer);

	// -- rendu des nom de carte
	int min = m_decalCarte+5;
	if( m_decalCarte+5 >m_TabNameCarte.size() )
		min = m_TabNameCarte.size();

	for(int i = m_decalCarte ; i < min ; ++i)
	{
		RENDER->draw(m_TabNameCarte[i]);
	}

	// -- rendu des nom de script
	min = m_decalScript+5;
	if( m_decalScript+5 >m_TabScript.size() )
		min = m_TabScript.size();

	for(int i = m_decalScript ; i < min ; ++i)
	{
		RENDER->draw(m_TabScript[i]);
	}

	// -- rendu des nom d'illustration
	min = m_decalIllustration+5;
	if( m_decalIllustration+5 >m_TabIllustration.size() )
		min = m_TabIllustration.size();

	for(int i = m_decalIllustration ; i < min ; ++i)
	{
		RENDER->draw(m_TabIllustration[i]);
	}

	if( m_CarteEnCours )
	{
		RENDER->draw( m_illustrationEnCours ) ;
	}

}


// ## Fonction test d'evénement

void EditeurCarte::IsClickSurNouveau()
{

	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

	if( m_Nouveau.getGlobalBounds().contains(TestVecteur ) )
	{
		if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
		{
			Ajouter_carte();
		}
	}

}

void EditeurCarte::IsClickSurSauvegarder()
{
	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

	if( m_sauvegarder.getGlobalBounds().contains(TestVecteur ) )
	{
		if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
		{
			Sauvegarder_carte();
		}
	}	
}

void EditeurCarte::ClickSurSupprimer()
{
	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

	if( m_Supprimer.getGlobalBounds().contains(TestVecteur ) )
	{
		if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
		{
			Supprimer_carte();
		}
	}
}

void  EditeurCarte::ClickSurCarte()
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
				m_CarteEnCours = &m_TabCarte[i];
				m_IndexCarteEnCours = i ;


				m_nom.setString( DATA->getTextByName("EDITEUR_CARTE_NOMCARTE") + " : " + (m_CarteEnCours->m_name)  );
				m_Script.setString( DATA->getTextByName("EDITEUR_CARTE_NOMSCRIPT") + " : " + (m_CarteEnCours->m_ScriptName)  );
				m_Illustration.setString( DATA->getTextByName("EDITEUR_CARTE_NOMILLUSTRATION") + " : " + (m_CarteEnCours->m_CleIllustration)  );
				m_Description.setString( DATA->getTextByName("EDITEUR_CARTE_DESCRIPTION") + " : " + (m_CarteEnCours->m_description)  );

				// actualisation de l'illustration 

				sf::Texture* TempText = BIBLI->getIllusByKey(m_CarteEnCours->m_CleIllustration);

				if( TempText )
					m_illustrationEnCours.setTexture(*TempText);

			}
		}
	}	
}

void EditeurCarte::ClickSurNom()
{
	if( m_CarteEnCours != NULL)
	{
		sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

		if( m_nom.getGlobalBounds().contains(TestVecteur ) )
		{
			if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
			{
				SetState(EditCard_EditName);
			}
		}
	}
}

void EditeurCarte::ClickSurScript()
{
	if( m_CarteEnCours != NULL)
	{
		sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

		if( m_Script.getGlobalBounds().contains(TestVecteur ) )
		{
			if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
			{
				SetState(EditCard_EditScript);
			}
		}
	}
}

void EditeurCarte::ClickSurIllustration()
{
	if( m_CarteEnCours != NULL)
	{
		sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

		if( m_Illustration.getGlobalBounds().contains(TestVecteur ) )
		{
			if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
			{
				SetState(EditCard_EditIllus);
			}
		}
	}
}

void EditeurCarte::ClickSurDescription()
{
	if( m_CarteEnCours != NULL)
	{
		sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

		if( m_Description.getGlobalBounds().contains(TestVecteur ) )
		{
			if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
			{
				SetState(EditCard_EditDesc);
			}
		}
	}
}


void EditeurCarte::ClickUpDownIllus()
{
	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

	if( m_monteIllus.getGlobalBounds().contains(TestVecteur ) )
	{
		if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
		{		

			m_decalIllustration -= 5;

			if(m_decalIllustration < 0)
				m_decalIllustration = 0;
		}
	}

	if( m_TabIllustration.size() > m_decalIllustration+5 )
	{
		if(m_descIllus.getGlobalBounds().contains(TestVecteur ) )
		{
			if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
			{
				m_decalIllustration += 5;
			}	
		}
	}

}

void EditeurCarte::ClickUpDownScript()
{
	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

	if( m_monteScript.getGlobalBounds().contains(TestVecteur ) )
	{
		if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
		{		

			m_decalScript -= 5;

			if(m_decalScript < 0)
				m_decalScript = 0;
		}
	}

	if( m_TabScript.size() > m_decalScript+5 )
	{
		if(m_descScript.getGlobalBounds().contains(TestVecteur ) )
		{
			if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
			{
				m_decalScript += 5;
			}	
		}
	}
}

void EditeurCarte::ClickUpDownCarte()
{
	sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

	if( m_monteCarte.getGlobalBounds().contains(TestVecteur ) )
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
		if(m_descCarte.getGlobalBounds().contains(TestVecteur ) )
		{
			if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
			{
				m_decalCarte += 5;
			}	
		}
	}
}


// ## Fonction outils

void EditeurCarte::Ajouter_carte()
{
	T_carte NewCard;

	NewCard.m_name = "Na";
	NewCard.m_ScriptName = "Na";
	NewCard.m_CleIllustration = "Na";
	NewCard.m_description = "Na";
	m_TabCarte.push_back(NewCard);

	sf::Text TempText ;
	TempText.setCharacterSize(18);
	TempText.setString(NewCard.m_name);

	if(  m_TabNameCarte.size() > 0 && (m_TabNameCarte.size())%5 != 0 )
	{
		TempText.setPosition( m_TabNameCarte[ m_TabNameCarte.size()-1].getPosition().x ,
		m_TabNameCarte[ m_TabNameCarte.size()-1].getPosition().y	+ m_decal_y );
	}
	else
	{
		TempText.setPosition( DATA->getFloatByName("Editeur_c_up_card_x"),
		DATA->getFloatByName("Editeur_c_up_card_y")	+ m_decal_y );
	}

	m_TabNameCarte.push_back(TempText);	

}

void EditeurCarte::Sauvegarder_carte()
{
	LOG("")
	LOG("<< Debut de la sauvegarde >>")
	LOG("1-Reinitialisation des infos cartes ")
	BIBLI->ReinitInfosCarte();
	LOG("2-sauvegarde des infos cartes dans la bibliotheque")
	LOG("")
	for(unsigned int i = 0 ; i < m_TabCarte.size() ; ++i)
	{		
		if( BIBLI->addCartes(m_TabCarte[i]) )
		{
			LOG("Carte " + m_TabCarte[i].m_name + " ajouter")
		}
		else
		{
			LOG("Carte "+ m_TabCarte[i].m_name + " incorrect")
		}
	}

	LOG("")
	LOG("3-Destruction des cartes incorrectes ")
	BIBLI->DetruitCarteIncorrect();
	LOG("4-sauvegarde des infos cartes dans le fichier de donnees ")
	BIBLI->SaveInfosCartes();
	LOG("5-Retour a l'initialisation ")
	LOG("")
	SetState(EditCard_INIT);
}

void EditeurCarte::Supprimer_carte()
{
	//si une carte a été sélectionner
	if( m_CarteEnCours!=NULL)
	{

		LOG("Je supprime : " + m_CarteEnCours->m_name)

			//dans tout les cas on enléve la carte actuel
			m_CarteEnCours = NULL;
		m_nom.setString( DATA->getTextByName("EDITEUR_CARTE_NOMCARTE") );
		m_Script.setString( DATA->getTextByName("EDITEUR_CARTE_NOMSCRIPT")  );
		m_Illustration.setString( DATA->getTextByName("EDITEUR_CARTE_NOMILLUSTRATION") );
		m_Description.setString( DATA->getTextByName("EDITEUR_CARTE_DESCRIPTION") );


		//on la retrouve
		int index = m_IndexCarteEnCours;

		//on l'échange avec la dernière si il y a plus de 2 cartes
		//et on popback
		//sinon on popback direct

		if( m_TabCarte.size() >=2)
		{
			T_carte Temp = m_TabCarte[index] ;
			m_TabCarte[index] =  m_TabCarte[m_TabCarte.size()-1];
			m_TabCarte[m_TabCarte.size()-1] = Temp;
			m_TabCarte.pop_back();


			sf::Text TempText = m_TabNameCarte[index];
			m_TabNameCarte[index] =  m_TabNameCarte[m_TabNameCarte.size()-1];
			m_TabNameCarte[index].setPosition( TempText.getPosition() );

			m_TabNameCarte[m_TabNameCarte.size()-1] = TempText;
			m_TabNameCarte.pop_back();

		}
		else
		{
			m_TabCarte.pop_back();
			m_TabNameCarte.pop_back();
		}
	}
	else
	{
		LOG("Aucune carte selectionner pour la suppression")
	}
}

void EditeurCarte::Ajouter_Script()
{
	if( m_CarteEnCours)
	{

		sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

		int min = m_decalScript+5;
		if( m_decalScript+5 >m_TabScript.size() )
			min = m_TabScript.size();

		for(unsigned int i = m_decalScript ; i < min ; ++i)
		{

			if( m_TabScript[i].getGlobalBounds().contains(TestVecteur ) )
			{
				if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
				{
					m_CarteEnCours->m_ScriptName = m_TabScript[i].getString();
					m_Script.setString( DATA->getTextByName("EDITEUR_CARTE_NOMSCRIPT") + " : " + (m_CarteEnCours->m_ScriptName)  );
					SetState(EditCard_Update);
				}
			}
		}	
	}
}

void EditeurCarte::Ajouter_illustration()
{
	if( m_CarteEnCours)
	{

		sf::Vector2f TestVecteur( (float)SOURISX , (float)SOURISY );

		int min = m_decalIllustration+5;
		if( m_decalIllustration+5 >m_TabIllustration.size() )
			min = m_TabIllustration.size();

		for(unsigned int i = m_decalIllustration ; i < min ; ++i)
		{

			if( m_TabIllustration[i].getGlobalBounds().contains(TestVecteur ) )
			{
				if( EVENT->isMButtonPressed(sf::Mouse::Left ) )
				{
					m_CarteEnCours->m_CleIllustration = m_TabIllustration[i].getString();
					m_Illustration.setString( DATA->getTextByName("EDITEUR_CARTE_NOMILLUSTRATION") + " : " + (m_CarteEnCours->m_CleIllustration)  );
					SetState(EditCard_Update);

					sf::Texture* TempText = BIBLI->getIllusByKey(m_CarteEnCours->m_CleIllustration);

					if( TempText )
						m_illustrationEnCours.setTexture(*TempText);
				}
			}
		}	
	}
}

void EditeurCarte::Ajouter_Nom()
{
	if( m_CarteEnCours )
	{
		std::string TempText = EVENT->GetTextEntered();

		while( TempText.size() >30)
			TempText.pop_back();

		EVENT->SetTextEntered(TempText);
		
		if( EVENT->isKeyPressed( sf::Keyboard::Back ) )
			EVENT->SupprimeLettreTextEntered();

		m_nom.setString( DATA->getTextByName("EDITEUR_CARTE_NOMCARTE") + " : " + (TempText)  );

		if( EVENT->isKeyPressed( sf::Keyboard::Return ) )
		{
			EVENT->ReinitTextEntered();
			m_CarteEnCours->m_name = TempText;
			m_TabNameCarte[m_IndexCarteEnCours].setString(m_CarteEnCours->m_name);
			SetState(EditCard_Update);
		}
	}
}

void EditeurCarte::Ajouter_Description()
{
	if( m_CarteEnCours )
	{
		std::string TempText = EVENT->GetTextEntered();

		while( TempText.size() >300)
			TempText.pop_back();

		if( EVENT->isKeyPressed( sf::Keyboard::Return ) &&   TempText.size() < 299)
			TempText.push_back('\n');

		EVENT->SetTextEntered(TempText);
		
		if( EVENT->isKeyPressed( sf::Keyboard::Back ) )
			EVENT->SupprimeLettreTextEntered();

		m_Description.setString( DATA->getTextByName("EDITEUR_CARTE_DESCRIPTION") + " : " + (TempText)  );
		if( EVENT->isKeyPressed( sf::Keyboard::F2 ) )
		{
			EVENT->ReinitTextEntered();
			m_CarteEnCours->m_description = TempText;		
			SetState(EditCard_Update);
		}
	}
}
