//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 13/02/2013 - 14h58
// Fichier : déclaraction de la classe carte.hpp 
// Dernière modification : 13/02/2013
//@@@@@@@@@@@@@@@@@@@



#pragma once

#include "GeneralConfig.hpp"
#include "DataCenter.hpp"
#include "FSM.hpp"
#include "BibliothequeCartes.hpp"


class BibliothequeCartes;

class Carte
{

protected :

	// << attributs description cartes >>
	T_carte m_InfosCartes;

	// << attributs images cartes >>
	sf::Sprite m_SkinGeneral;
	sf::Sprite m_Illustration;
	sf::Sprite m_SkinDos;
	FSM* m_ScriptCarte;

	// << attributs images cartes >>
	bool m_Retourner;
	bool m_prise;
	sf::Vector2f m_vecdecalIllu;


public :

	Carte();
	Carte(T_carte);
	~Carte(){m_ScriptCarte = NULL;};

	void Affiche_carte();

	T_carte getInfosCarte(){return m_InfosCartes;};
	FSM* getScriptCarte() const {return m_ScriptCarte;};
	void setScriptCarte(FSM* _fsm) {m_ScriptCarte = _fsm;};

	bool isRetourner() const {return m_Retourner;};
	bool isPrise() const {return m_prise;};

	void Retourner(){m_Retourner = !m_Retourner;}
	void PrendreOuPoser(){m_prise = !m_prise;}
	sf::Sprite getGeneralSprite(){return m_SkinDos;};

	void setPositionCarte(sf::Vector2f _vec);
	sf::Vector2f getPositionCarte() const {return m_SkinGeneral.getPosition() ; } ;

};