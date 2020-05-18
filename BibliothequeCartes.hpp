//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 13/02/2013 - 14h58
// Fichier : déclaraction de la classe Bilbiothèque.hpp 
// Dernière modification : 13/02/2013
//@@@@@@@@@@@@@@@@@@@


#pragma once

#include "GeneralConfig.hpp"
#include "DataCenter.hpp"
#include "FSM.hpp"
#include "ScriptInclude.hpp"


#define BIBLI BibliothequeCartes::getBibliManager()


typedef struct
{
	std::string m_name;
	std::string m_description;
	std::string m_CleIllustration;
	std::string m_ScriptName;

}T_carte;


typedef struct
{
	char m_name[30];
	char m_description[300];
	char m_CleIllustration[300];
	char m_ScriptName[300];

}T_carteBinaire;



#include "Carte.hpp"
class Carte;

// << class singleton >>
class BibliothequeCartes
{

public :
	
	static BibliothequeCartes* getBibliManager();
	~BibliothequeCartes();


	// << méthode de chargement/sauvegarde >>
	void LoadInfosCartes();
	void SaveInfosCartes();

	void SelfRegisterScript();


	// << accesseurs >>
	T_carte getInfosCartes(int _i) const;
	void setInfosCarte(int _i, T_carte _carte);
	void ReinitInfosCarte();
	bool addCartes(T_carte);
	unsigned int getNombreCartes() const {return m_VecInfosCartes.size();};

	Carte* CreerCartes(std::string _name);

	FSM* GetCloneScriptByName(std::string _name);

	sf::Texture* getIllusByKey(std::string);
	std::string getKey(int _i);

	std::string getScriptName(int _i);
	std::string getIllusName(int _i);
	T_carte* getAllCard();

	int getNbreCarte(){return m_VecInfosCartes.size();};
	int getNbreIllus(){return m_IllusMap.size();};
	int getNbreScript(){return m_ScriptMap.size();};
	bool DetruitCarteIncorrect();

private :

	BibliothequeCartes();
	std::vector<T_carte> m_VecInfosCartes ;
	std::map<std::string,sf::Texture*> m_IllusMap;
	std::map<std::string,FSM*> m_ScriptMap;
	
	void DetruitCarteMemeNom();
	
	std::string* m_TabKey;

};