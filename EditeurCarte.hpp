//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 04/03/2013 - 14h44
// Fichier : d�claraction de la classe Editeurdeck.hpp h�rit� d'une FSM
// Derni�re modification : 04/03/2013
//@@@@@@@@@@@@@@@@@@@

#pragma once

#include "GeneralConfig.hpp"
#include "DataCenter.hpp"
#include "EventManager.hpp"
#include "FSM.hpp"

#include "BibliothequeCartes.hpp"
#include "Carte.hpp"



enum Editeur_Carte_State
{
	EditCard_INIT = 0,
	EditCard_Update,
	EditCard_EditName,
	EditCard_EditScript,
	EditCard_EditIllus,
	EditCard_EditDesc
};

class EditeurCarte : public FSM
{
protected :

	// @@ fonction general @@

	virtual bool States( StateMachineEvent event, int state );

	void Init_EditeurCarte();
	void Init_ListCarte();
	void init_ListScript();
	void init_ListIllus();
	void Display_Editeur_Carte();

	// @@ fonction outils @@

	void Ajouter_carte();
	void Sauvegarder_carte();
	void Supprimer_carte();

	void Ajouter_Script();
	void Ajouter_illustration();
	void Ajouter_Nom();
	void Ajouter_Description();


	// @@ fonction d'�venement @@
	void IsClickSurNouveau();
	void IsClickSurSauvegarder();
	void ClickSurSupprimer();

	void ClickSurCarte();
	void ClickSurNom();
	void ClickSurScript();
	void ClickSurIllustration();
	void ClickSurDescription();

	void ClickUpDownIllus();
	void ClickUpDownScript();
	void ClickUpDownCarte();
	

	// @@ Attributs @@

	// -- titre -- 
	sf::Text m_TitreListeCarte;
	sf::Text m_TitreListeScript;
	sf::Text m_TitreListeIllustration;

	// -- liste --
	std::vector<T_carte> m_TabCarte;
	std::vector<sf::Text> m_TabNameCarte;
	std::vector<sf::Text> m_TabScript;
	std::vector<sf::Text> m_TabIllustration;

	int m_decalCarte , m_decalScript, m_decalIllustration;
	float m_decal_y;
	
	// -- infos carte choisie
	sf::Text m_nom;
	sf::Text m_Script;
	sf::Text m_Illustration;
	sf::Text m_Description;

	T_carte* m_CarteEnCours;
	int m_IndexCarteEnCours;

	sf::Sprite m_illustrationEnCours;

	// -- bouton --

	sf::Text m_sauvegarder;
	sf::Text m_Nouveau;
	sf::Text m_Supprimer;
	sf::Text m_descCarte , m_descScript, m_descIllus;
	sf::Text m_monteCarte , m_monteScript ,m_monteIllus;


public :
		
	EditeurCarte(){};
	~EditeurCarte(){};

	virtual FSM* Clone(){return NULL;};
	virtual std::string GetName(){return "EditeurCarte";};


};