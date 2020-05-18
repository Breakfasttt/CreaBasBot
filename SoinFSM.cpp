//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 04/03/2013 - 14h55
// Fichier : Script d'attaque de base - def
// Dernière modification : 4/03/2013
//@@@@@@@@@@@@@@@@@@@


#include "SoinFSM.hpp"



FSM* SoinFsm::Clone()
{
	SoinFsm* NewScript =  new SoinFsm();
	
	NewScript->m_currentState = m_currentState;
	NewScript->m_nextState = m_nextState;
	NewScript->m_stateChange = m_stateChange;
	NewScript->m_MaxRegistedState = m_MaxRegistedState;

	return NewScript;
}


bool SoinFsm::States( StateMachineEvent event, int state )
{
	BeginStateMachine

		//***********************
		State(soin_INIT)
	OnEnter
		LOG("FSM Script  : soin_INIT");
		m_end = false;
		SetState(soin_UPDATE);
	OnUpdate
	OnExit
		//#######################

		//***********************
		State(soin_UPDATE)
	OnEnter
		LOG("FSM Script  : soin_UPDATE");

		if( m_Robot)
		{
			m_Robot->addVie(Valeur_Soin);

			sf::Vector2f Temp = m_Robot->getActualPosition();

			m_vieRecup.setString("+2 pv");
			m_vieRecup.setPosition(Temp.x,Temp.y );
			m_vieRecup.setColor(sf::Color::Green);
		}
		
		
	OnUpdate

		if ( ! m_end )
		{
			float dt = DATA->getDT();

			sf::Vector2f TempPos = m_vieRecup.getPosition() ;			
			TempPos.y -= 100.0f  * dt;
			m_vieRecup.setPosition(TempPos);


			if( TempPos.y < 200.0f)
			{
				m_Robot->setPosition( m_Robot->getInitPosition() ) ;
				m_end = true;
			}

			RENDER->draw(m_vieRecup);

		}

	OnExit
		
		//#######################

	EndStateMachine
}



