//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 11/03/2013 - 15h15
// Fichier : déclaraction de la classe joueur.hpp hérité d'une FSM
// Dernière modification : 11/03/2013
//@@@@@@@@@@@@@@@@@@@



#pragma once 

#include "GeneralConfig.hpp"
#include "DataCenter.hpp"
#include "EventManager.hpp"
#include "FSM.hpp"
#include "BiblioDeck.hpp"
#include "Deck.hpp"
#include "Robot.hpp"


enum Joueur_State
{
	JOUEUR_INIT = 0,
	JOUEUR_MELANGE,
	JOUEUR_PIOCHE,
	JOUEUR_POSE,
	JOUEUR_RESOLUTION,
	JOUEUR_ATTENTE,
	JOUEUR_ATTENTE_PIOCHE,
	JOUEUR_FIN
};


class Cjoueur : public FSM
{

protected :

	Cjoueur* m_adversaire;
	Deck* m_DeckJoueur;
	CRobot* m_RobotJoueur;
	bool m_IA;
	bool m_enAttente;
	bool m_mort;
	float m_timerIA;

	int m_IndexCartePioche[3];
	int m_CarteRestante;
	int m_carteChoisie;
	sf::Vector2f m_positionCarteChoisie;

	// texte infos general

	sf::Text m_InfosNbreCarte;
	sf::Text m_InfosVieRobot;
	sf::Text m_InfosAttaqueRobot;
	sf::Text m_InfosDefenseRobot;
	sf::Text m_InfosPhase;

	std::string  m_infosNbrecarteStr;
	std::string m_infosVieStr;
	std::string m_infosAttqStr;
	std::string m_infosDefStr;

	// texte infos carte

	sf::Text  m_NomCarte;
	sf::Text  m_DescriptionCarte;
	std::string m_NomCarteStr;
	std::string m_DescriptionCarteStr;


	//@@@@ fonction general @@@@
	virtual bool States( StateMachineEvent event, int state );
	virtual FSM* Clone(){return NULL;};
	virtual std::string GetName(){return "joueur";};

public :

	Cjoueur();
	Cjoueur(bool);
	~Cjoueur();

	void setAdversaire(Cjoueur* _j) ;
	unsigned int getStateJoueur(){return this->getCurrentState();};
	CRobot* getRobot(){return m_RobotJoueur;};

	Deck* getDeck(){return m_DeckJoueur;};
	int getCarteChoisie(){return m_carteChoisie;};
	

	//@@@@ fonction de jeu @@@@

	void MelangeCarte();
	void PiocheCarte();
	void PoseCarte();
	
	void AffichageDeck();
	void AffichageInfos();
	void actualisationInfos();

	void InitResolution();
	void Resolutions();
	void FinResolution();

	void PiocheCarte_ia();
	void Resolutions_ia();
	void PoseCarte_ia();
	bool AttenteParTimer_ia();

	void InitialisationJoueur();
	void InitialisationTexte();

	void AfficheInfosCarte();

	void CommandeDebug();

	bool estMort();
	bool estPret();




};

