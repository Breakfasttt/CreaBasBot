//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 11/03/2013 - 15h15
// Fichier : déclaraction de la classe Robot.hpp hérité d'une FSM
// Dernière modification : 11/03/2013
//@@@@@@@@@@@@@@@@@@@



#pragma once 


#include "GeneralConfig.hpp"
#include "DataCenter.hpp"
#include "EventManager.hpp"
#include "FSM.hpp"


class CRobot
{
protected :


	FSM* m_RobotFSM;
	CRobot* m_Cible;
	sf::Sprite m_spriteRobot;
	sf::Vector2f m_initPositionRobot;

	int m_Attaque;
	int m_defense;
	int m_Vie;


public : 


	CRobot();
	CRobot(bool);

	~CRobot();

	int getAttaque(){return m_Attaque;};
	int getDefense(){return m_defense;};
	int getVie(){return m_Vie;};

	void addVie(int _i) { m_Vie += _i;}
	void addDefense(int _i) { m_defense += _i;}
	void addAttaque(int _i) { m_Attaque += _i;}

	void setVie(int _i) { m_Vie = _i;}
	void setDefense(int _i) { m_defense = _i;}
	void setAttaque(int _i) { m_Attaque = _i;}

	sf::Vector2f getInitPosition(){return m_initPositionRobot;};
	sf::Vector2f getActualPosition(){return m_spriteRobot.getPosition();};
	void setPosition(sf::Vector2f _v ){m_spriteRobot.setPosition(_v);};


	void setFSM(FSM* _f){m_RobotFSM = _f;};
	void setCible(CRobot* _r){m_Cible = _r;};
	CRobot* getCible() {return m_Cible;};


	void InitFSM();
	void UpdateFSM();
	bool ActionFini();


	void Display();


};