//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 11/03/2013 - 15h15
// Fichier : déclaraction de la classe Robot.hpp hérité d'une FSM
// Dernière modification : 11/03/2013
//@@@@@@@@@@@@@@@@@@@


#include "Robot.hpp"


CRobot::CRobot()
{
	m_RobotFSM = NULL;
	m_Cible = NULL;
	LOG("creation d'un robot");
}

CRobot::CRobot(bool _Ia)
{
	m_RobotFSM = NULL;
	m_Cible = NULL;
	LOG("creation d'un robot");

	sf::Texture* TempTexture;
	float X,Y;


	if(_Ia)
	{
		TempTexture = DATA->getTextureByName("ROBOT_DROITE");
		X = DATA->getFloatByName("Combat_ia_pos_robot_x");
		Y = DATA->getFloatByName("Combat_ia_pos_robot_y");
	}
	else
	{
		TempTexture = DATA->getTextureByName("ROBOT_GAUCHE");	
		X = DATA->getFloatByName("Combat_joueur_pos_robot_x");
		Y = DATA->getFloatByName("Combat_joueur_pos_robot_y");
	}

	m_initPositionRobot.x = X;
	m_initPositionRobot.y = Y;

	if(TempTexture)
		m_spriteRobot.setTexture(*TempTexture);

	m_spriteRobot.setPosition(m_initPositionRobot);
	//chargement des valeur de combat

	m_Vie = DATA->getIntByName("Combat_robot_vie");
	m_Attaque = DATA->getIntByName("Combat_robot_attaque");
	m_defense = DATA->getIntByName("Combat_robot_defense");

}

CRobot::~CRobot()
{
	m_RobotFSM = NULL;
	m_Cible = NULL;
	LOG("destruction d'un robot");
}


void CRobot::Display()
{
	RENDER->draw(m_spriteRobot);
}


void CRobot::InitFSM()
{
	if( m_RobotFSM) 
	{
		LOG("<< Initialisation de la FSM du robot") 

		m_RobotFSM->UserFonction(this);
		m_RobotFSM->Initialize();
	}
}

void CRobot::UpdateFSM()
{
	if( m_RobotFSM) 
	{
		m_RobotFSM->Update();
	}
}

bool CRobot::ActionFini()
{
	if( m_RobotFSM) 
	{
		return m_RobotFSM->IsEnd();
	}

	return false;
}

