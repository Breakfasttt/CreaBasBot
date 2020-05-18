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

#define Valeur_Bouclier 1

enum BouBouFsm_State
{
	boubou_INIT = 0,
	boubou_UPDATE,
};

class BouclierFsm : public FSM
{

public : 

	virtual void UserFonction(void* _infos)  {	 m_Robot = (CRobot*)_infos;} ;
	virtual std::string GetName(){return "Bouclier";};
	virtual FSM* Clone();
	BouclierFsm(){m_Robot = NULL;};
	~BouclierFsm(){m_Robot=NULL;};


protected :

	CRobot* m_Robot;

	sf::Text m_defRecup;

	virtual bool States( StateMachineEvent event, int state );
	
	

};