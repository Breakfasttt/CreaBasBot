//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 04/03/2013 - 14h55
// Fichier : Script de bouclier - def
// Dernière modification : 4/03/2013
//@@@@@@@@@@@@@@@@@@@


#include "BouclierFSM.hpp"



FSM* BouclierFsm::Clone()
{
	BouclierFsm* NewScript =  new BouclierFsm();
	
	NewScript->m_currentState = m_currentState;
	NewScript->m_nextState = m_nextState;
	NewScript->m_stateChange = m_stateChange;
	NewScript->m_MaxRegistedState = m_MaxRegistedState;

	return NewScript;
}


bool BouclierFsm::States( StateMachineEvent event, int state )
{
	BeginStateMachine

		//***********************
		State(boubou_INIT)
	OnEnter
		LOG("FSM Script  : boubou_INIT");
		m_end = false;
		SetState(boubou_UPDATE);
	OnUpdate
	OnExit
		//#######################

		//***********************
		State(boubou_UPDATE)
	OnEnter
		LOG("FSM Script  : boubou_UPDATE");

		if( m_Robot)
		{
			m_Robot->addDefense(Valeur_Bouclier);

			sf::Vector2f Temp = m_Robot->getActualPosition();

			m_defRecup.setString("+1 def");
			m_defRecup.setPosition(Temp.x,Temp.y );
			m_defRecup.setColor(sf::Color::Blue);
		}
		
		
	OnUpdate

		if ( ! m_end )
		{
			float dt = DATA->getDT();

			sf::Vector2f TempPos = m_defRecup.getPosition() ;			
			TempPos.y -= 100.0f  * dt;
			m_defRecup.setPosition(TempPos);


			if( TempPos.y < 200.0f)
			{
				m_Robot->setPosition( m_Robot->getInitPosition() ) ;
				m_end = true;
			}

			RENDER->draw(m_defRecup);

		}

	OnExit
		
		//#######################

	EndStateMachine
}



