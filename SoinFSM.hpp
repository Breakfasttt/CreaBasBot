//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 04/03/2013 - 14h55
// Fichier : Script d'attaque de base - decl
// Dernière modification : 4/03/2013
//@@@@@@@@@@@@@@@@@@@

#pragma once 

#include "GeneralConfig.hpp"
#include "FSM.hpp"
#include "Robot.hpp"

#define Valeur_Soin 2

enum SoinFsm_State
{
	soin_INIT = 0,
	soin_UPDATE,
};

class SoinFsm : public FSM
{

public : 

	virtual void UserFonction(void* _infos)  {	 m_Robot = (CRobot*)_infos;} ;
	virtual std::string GetName(){return "Soin";};
	virtual FSM* Clone();
	SoinFsm(){m_Robot = NULL;};
	~SoinFsm(){m_Robot=NULL;};


protected :

	CRobot* m_Robot;

	sf::Text m_vieRecup;

	virtual bool States( StateMachineEvent event, int state );
	
	

};