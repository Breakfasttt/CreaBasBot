//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 13/02/2013 - 14h58
// Fichier : déclaraction de la classe Bilbiothèque.hpp 
// Dernière modification : 13/02/2013
//@@@@@@@@@@@@@@@@@@@



#include "BibliothequeCartes.hpp"



BibliothequeCartes* BibliothequeCartes::getBibliManager()
{
	static BibliothequeCartes* Instance = new BibliothequeCartes();
	return Instance;

}

BibliothequeCartes::BibliothequeCartes() : m_VecInfosCartes() , m_IllusMap()
{
	LoadInfosCartes();
}

BibliothequeCartes::~BibliothequeCartes()
{
	if(m_TabKey)
	{
		delete m_TabKey;	
	}


	std::map<std::string,sf::Texture*>::iterator it;

	for(it = m_IllusMap.begin() ; it != m_IllusMap.end(); ++it)
	{
		delete (*it).second;
		(*it).second = NULL;
	}

	m_IllusMap.clear();


}

void BibliothequeCartes::LoadInfosCartes()
{
	std::ifstream DataScores  ;
	std::ofstream DaTa;

	// << chargement des structures >>

	DataScores.open("Assets/BiblioCard.DAT",std::ios::in | std::ios::binary);

	if( !DataScores.is_open() )
	{
		LOG("ouverture du fichier Bibliotheque echoue ! " )
			LOG("Creation d'un fichier..." )
			DaTa.open("Assets/BiblioCard.DAT",std::ios::out | std::ios::binary  );

		if(DaTa.is_open())
		{
			DaTa.close();
		}
		else
		{
			LOG("problème de création de la bibliothèque de carte")
				exit(-1);
		}

		DataScores.open("Assets/BiblioCard.DAT",std::ios::in | std::ios::binary);

		if(DataScores.is_open())
		{
			
			LOG("Fichier creer")
		}
	}

	if ( DataScores.is_open() )
	{

		while( !DataScores.eof() )
		{
			T_carte tempCarte;
			T_carteBinaire TempCarteBin;


			DataScores.read( (char*)&TempCarteBin,sizeof(T_carteBinaire) );

			if(TempCarteBin.m_CleIllustration)
			{

				tempCarte.m_CleIllustration = TempCarteBin.m_CleIllustration;
				tempCarte.m_description = TempCarteBin.m_description;
				tempCarte.m_name = TempCarteBin.m_name;
				tempCarte.m_ScriptName = TempCarteBin.m_ScriptName;
				m_VecInfosCartes.push_back(tempCarte);
			}		
		}
		
		DataScores.close();
	}
	else
	{
		LOG("la création a echouer" )
			m_TabKey = NULL;
	}

	DetruitCarteMemeNom();

	// << chargement des illustrations >>

	DataScores.open("Assets/Illustration.txt",std::ios::in );

	if( DataScores == NULL)
	{
		std::cout << "Erreur lors de l'ouverture du DataIllustration" << std::endl;
		m_TabKey = NULL;
	}
	else
	{

		while( !DataScores.eof() )
		{
			std::string TextureKey;
			std::string TextureLink;

			DataScores >> TextureKey >> TextureLink ;			

			if(TextureKey != "" && TextureLink != "")
			{
				sf::Texture* tempTexture = new sf::Texture();

				tempTexture->loadFromFile(TextureLink);

				m_IllusMap[TextureKey] = tempTexture;

				tempTexture = NULL;	
			}
		}
		DataScores.close();

		if( m_IllusMap.size() >0 )
		{
			m_TabKey = new std::string[m_IllusMap.size()];

			std::map<std::string,sf::Texture*>::iterator it;
			int i =0;

			for(it = m_IllusMap.begin() ; it != m_IllusMap.end(); ++it)
			{
				if( i < m_IllusMap.size() )
					m_TabKey[i] = (*it).first ;

				i++;
			}
		}
		else
		{
			m_TabKey = NULL;
		}
	}
}

void BibliothequeCartes::SaveInfosCartes()
{
	std::ofstream DataScores ;

	DataScores.open("Assets/BiblioCard.DAT",std::ios::out | std::ios::binary);

	if( !DataScores.is_open() )
	{
		LOG("Erreur lors de la sauvegarde de la bibliothèque")
	}
	else
	{
		for(unsigned int i = 0 ; i < m_VecInfosCartes.size() ; ++i)
		{	
			T_carte TempCarte  = getInfosCartes(i);
			T_carteBinaire TempCarteBinaire ;

			for(int i = 0 ; (i < TempCarte.m_CleIllustration.size()) && i < 300 ; ++i)
			{
				TempCarteBinaire.m_CleIllustration[i] = TempCarte.m_CleIllustration[i];
				if( i+1 <300)
					TempCarteBinaire.m_CleIllustration[i+1] = '\0';
			}
			for(int i = 0 ; (i < TempCarte.m_description.size()) && i < 300 ; ++i)
			{
				
				TempCarteBinaire.m_description[i] = TempCarte.m_description[i];
				if( i+1 <300)
					TempCarteBinaire.m_description[i+1] = '\0';

			}
			for(int i = 0 ; (i < TempCarte.m_name.size()) && i < 30 ; ++i)
			{
				TempCarteBinaire.m_name[i] = TempCarte.m_name[i];
				if( i+1 <30)
					TempCarteBinaire.m_name[i+1] = '\0';
			}
			for(int i = 0 ; (i < TempCarte.m_ScriptName.size()) && i < 300 ; ++i)
			{
				TempCarteBinaire.m_ScriptName[i] = TempCarte.m_ScriptName[i];
				if( i+1 <300)
					TempCarteBinaire.m_ScriptName[i+1] = '\0';
			}


			DataScores.write( (char*)&TempCarteBinaire,sizeof(T_carteBinaire));
		}

		DataScores.close();
	}
}

T_carte BibliothequeCartes::getInfosCartes(int _i) const
{
	
	return m_VecInfosCartes[_i] ;

}

void BibliothequeCartes::setInfosCarte(int _i, T_carte _carte)
{
	m_VecInfosCartes[_i].m_CleIllustration = _carte.m_CleIllustration;
	m_VecInfosCartes[_i].m_description = _carte.m_description;
	m_VecInfosCartes[_i].m_name = _carte.m_name;
	m_VecInfosCartes[_i].m_ScriptName = _carte.m_ScriptName;
}

bool BibliothequeCartes::addCartes(T_carte _carte)
{

	bool NomDejaPris = false;

	for(int i = 0 ; i < m_VecInfosCartes.size() ; ++i )
	{
		if(  m_VecInfosCartes[i].m_name == _carte.m_name )
		{
			NomDejaPris = true;
			break;
		}
	}
	// si le nom n'es pas pris et que la carte n'est pas détruite
	// on retourne Vrai
	if(!NomDejaPris) 
	{
		m_VecInfosCartes.push_back(_carte);
		return true;
	}
	else
	{
		LOG("Biblio : addcarte : nom de cartes deja pris")
		return false;
	}

	return false;
}

void BibliothequeCartes::ReinitInfosCarte()
{
	while(m_VecInfosCartes.size()>0)
	{
		m_VecInfosCartes.pop_back();
	}

	m_VecInfosCartes.clear();
}

sf::Texture* BibliothequeCartes::getIllusByKey(std::string _st)
{
	return m_IllusMap[_st];
}

std::string BibliothequeCartes::getKey(int _i)
{
	if( _i < m_IllusMap.size() &&  _i >=0  ) 
	{
		return m_TabKey[_i];
	}

	return "";
}

Carte* BibliothequeCartes::CreerCartes(std::string _name)
{
	unsigned int i =0;
	for(i = 0 ; i < m_VecInfosCartes.size() ; ++i)
	{
		if ( m_VecInfosCartes[i].m_name == _name )
			break;
	}

	if( i == m_VecInfosCartes.size())
		return NULL;

	return new Carte( m_VecInfosCartes[i] ) ;
}

bool BibliothequeCartes::DetruitCarteIncorrect()
{
	std::map<std::string,FSM*>::iterator it;
	bool Scriptconnu = false;
	bool Illusconnu = false;
	bool Destruction = false;

	for(int i = 0 ; i < m_VecInfosCartes.size(); ++i)
	{
		Scriptconnu = false;
		Illusconnu = false;

		//on cherche si le script existe
		for(it = m_ScriptMap.begin() ; it != m_ScriptMap.end() ; ++it)
		{
			if( (*it).first  == m_VecInfosCartes[i].m_ScriptName )
			{
				//le script est connu on vérifie si l'illustration est connu
				Scriptconnu = true;
				Illusconnu = false;
				break;
			}
		}	

		//on cherche si l'illustration existe, si le script existe seulement
		if(Scriptconnu)
		{
			std::map<std::string,sf::Texture*>::iterator itLus;
			for(itLus = m_IllusMap.begin() ; itLus != m_IllusMap.end() ; ++itLus)
			{
				if( (*itLus).first  == m_VecInfosCartes[i].m_CleIllustration )
				{
					Illusconnu = true;
					break;
				}
			}
		}

		//si le script ou l'illustration est inconnu on supprime l'infos cartes
		if( !Scriptconnu && !Illusconnu )
		{
			LOG("Script ou Illustration inconnu : " + m_VecInfosCartes[i].m_name)
			T_carte Temp = m_VecInfosCartes[m_VecInfosCartes.size()-1];
			m_VecInfosCartes[m_VecInfosCartes.size()-1] = m_VecInfosCartes[i];
			m_VecInfosCartes[i] = Temp;
			m_VecInfosCartes.pop_back();
			i--;
			//une destruction a été faite
			Destruction = true;
		}
	}

	return Destruction;
}

void BibliothequeCartes::DetruitCarteMemeNom()
{
	bool destruction = false;

	for(int i = 0 ; i < m_VecInfosCartes.size(); ++i)
	{
		destruction = false;
		for(int j = i+1 ; j < m_VecInfosCartes.size(); ++j)
		{
			if( m_VecInfosCartes[i].m_name == m_VecInfosCartes[j].m_name)
			{
				T_carte TempCarte = m_VecInfosCartes[m_VecInfosCartes.size()-1];
				m_VecInfosCartes[m_VecInfosCartes.size()-1] = m_VecInfosCartes[j] ;
				m_VecInfosCartes[j]  = TempCarte;
				m_VecInfosCartes.pop_back();
				destruction = true;

			}
		}

		if (destruction)
			i--;
	}
}

FSM* BibliothequeCartes::GetCloneScriptByName(std::string _name)
{
	std::map<std::string,FSM*>::iterator it;

	for(it = m_ScriptMap.begin(); it != m_ScriptMap.end(); ++it)
	{
		if( (*it).first == _name) 
		{
			return (*it).second->Clone();		
		}	
	}

	return NULL;
}


std::string BibliothequeCartes::getScriptName(int _i)
{

	if( _i < m_ScriptMap.size() && _i>=0 )
	{
		std::map<std::string,FSM*>::iterator it;
		it = m_ScriptMap.begin();
		int i =0; 
		while( i!=_i)
		{
			++it;
			++i;
		}

		return (*it).first;
	}

	return "Error";
}

std::string BibliothequeCartes::getIllusName(int _i)
{
	if( _i < m_IllusMap.size() && _i>=0 )
	{
		std::map<std::string,sf::Texture*>::iterator it;
		it = m_IllusMap.begin();
		int i =0; 
		while( i!=_i)
		{
			++it;
			++i;
		}

		return (*it).first;
	}

	return "Error";
}

T_carte* BibliothequeCartes::getAllCard()
{
	if(m_VecInfosCartes.size() >0)
	{
		T_carte* TempTab = new T_carte[ m_VecInfosCartes.size() ];
	

		for(int i =0 ; i < m_VecInfosCartes.size() ; ++i)
		{
			TempTab[i] = m_VecInfosCartes[i];
		}

		return TempTab;
	}

	return NULL;
}


void BibliothequeCartes::SelfRegisterScript()
{

	// << chargement des Script >>
	LOG(" << Chargement des scripts >>");
	LOG(" 1 - Ecriture des nom de script")
		//inscrire ici les script a sauvegarder

	m_ScriptMap["BasicAttack"] = new AttaqueFsm();
	m_ScriptMap["Soin"] = new SoinFsm();
	m_ScriptMap["Bouclier"] = new BouclierFsm();

	LOG(" 2 - Verification des infos cartes eronnees")
		DetruitCarteIncorrect();

}


