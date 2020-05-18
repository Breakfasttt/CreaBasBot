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

#define Degats 1

enum AttFsm_State
{
	Att_INIT = 0,
	att_UPDATE,
};

class AttaqueFsm : public FSM
{

public : 

	virtual void UserFonction(void* _infos)  {	 m_Robot = (CRobot*)_infos;} ;
	virtual std::string GetName(){return "BasicAttack";};
	virtual FSM* Clone();
	AttaqueFsm(){m_Robot = NULL;};
	~AttaqueFsm(){m_Robot=NULL;};


protected :

	CRobot* m_Robot;
	float m_timer;

	virtual bool States( StateMachineEvent event, int state );
	
	

};