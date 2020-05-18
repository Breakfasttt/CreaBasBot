//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 13/02/2013 - 14h58
// Fichier : définition de la classe carte.cpp 
// Dernière modification : 13/02/2013
//@@@@@@@@@@@@@@@@@@@


#include "Carte.hpp"



Carte::Carte()
{

}


Carte::Carte(T_carte _carte)
{	
	m_Retourner = true;
	m_prise = false;

	m_InfosCartes.m_CleIllustration = _carte.m_CleIllustration;
	m_InfosCartes.m_description = _carte.m_description;
	m_InfosCartes.m_name = _carte.m_name;
	m_InfosCartes.m_ScriptName = _carte.m_ScriptName;


	// << on charge le dos >>
	sf::Texture* TempTexture = DATA->getTextureByName("DOS_CARTE");

	if(TempTexture)
		m_SkinDos.setTexture(*TempTexture);

	// << on charge la face >>
	TempTexture = DATA->getTextureByName("FACE_CARTE");

	if(TempTexture)
		m_SkinGeneral.setTexture(*TempTexture);

	// << on charge l'illustration >>
	TempTexture = BIBLI->getIllusByKey(m_InfosCartes.m_CleIllustration) ;

	if(TempTexture)
		m_Illustration.setTexture(*TempTexture);
	
	int maxX = DATA->getIntByName("Carte_illu_Max_x");
	int maxY = DATA->getIntByName("Carte_illu_Max_y");

	m_Illustration.setTextureRect( sf::IntRect(0,0,maxX,maxY) );


	// << on décalle l'illustration >>
	m_vecdecalIllu.x = DATA->getFloatByName("Carte_illu_Decal_x");
	m_vecdecalIllu.y = DATA->getFloatByName("Carte_illu_Decal_y");

	sf::Vector2f posTemp = m_SkinGeneral.getPosition();
	posTemp += m_vecdecalIllu;
	m_Illustration.setPosition(posTemp);


	// << on charge le script >>

	m_ScriptCarte = BIBLI->GetCloneScriptByName( _carte.m_ScriptName ) ;

	if(m_ScriptCarte)
		LOG(_carte.m_name +  " Loading : " + m_ScriptCarte->GetName() )

}

void Carte::setPositionCarte(sf::Vector2f _vec)
{
	m_SkinDos.setPosition(_vec);
	m_SkinGeneral.setPosition(_vec);

	sf::Vector2f posTemp = m_SkinGeneral.getPosition();
	posTemp += m_vecdecalIllu;
	m_Illustration.setPosition(posTemp);
}



void Carte::Affiche_carte()
{
	if(m_Retourner)
	{
		RENDER->draw(m_SkinDos);
	}
	else
	{
		RENDER->draw(m_SkinGeneral);
		RENDER->draw(m_Illustration);
	}
}