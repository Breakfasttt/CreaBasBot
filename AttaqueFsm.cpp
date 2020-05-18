//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 04/03/2013 - 14h55
// Fichier : Script d'attaque de base - def
// Dernière modification : 4/03/2013
//@@@@@@@@@@@@@@@@@@@


#include "AttaqueFsm.hpp"



FSM* AttaqueFsm::Clone()
{
	AttaqueFsm* NewScript =  new AttaqueFsm();
	
	NewScript->m_currentState = m_currentState;
	NewScript->m_nextState = m_nextState;
	NewScript->m_stateChange = m_stateChange;
	NewScript->m_MaxRegistedState = m_MaxRegistedState;

	return NewScript;
}


bool AttaqueFsm::States( StateMachineEvent event, int state )
{
	BeginStateMachine

		//***********************
		State(Att_INIT)
	OnEnter
		LOG("FSM Script  : Att_INIT");
		m_end = false;
		m_timer = 2.0f;
		SetState(att_UPDATE);
	OnUpdate
	OnExit
		//#######################

		//***********************
		State(att_UPDATE)
	OnEnter
		LOG("FSM Script  : att_UPDATE");

		if( m_Robot)
		{
			CRobot* Temp = m_Robot->getCible();

			if(	Temp)
			{
				int def = Temp->getDefense();
				int Att = m_Robot->getAttaque();
				int damage = (Degats+Att)-def  ;

				if (damage < 0)
					damage = 0;

				Temp->addVie(-damage);
			}
		}
		
		
	OnUpdate

		if ( ! m_end )
		{
			m_Robot->setPosition( m_Robot->getInitPosition() ) ;
			sf::Vector2f TempPos = m_Robot->getActualPosition();

			TempPos.x += rand()%10 - 5;
			TempPos.y += rand()%10 - 5;

			m_Robot->setPosition( TempPos );

			m_timer -= DATA->getDT();

			if( m_timer<=0)
			{
				m_Robot->setPosition( m_Robot->getInitPosition() ) ;
				m_end = true;
			}
		}

	OnExit
		
		//#######################

	EndStateMachine
}



