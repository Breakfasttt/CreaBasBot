//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 06/03/2013 - 15h15
// Fichier : déclaraction de la classe bibliodeck.hpp 
// Dernière modification : 06/03/2013
//@@@@@@@@@@@@@@@@@@@


#include "BiblioDeck.hpp"



BiblioDeck* BiblioDeck::getDeckManager()
{
	static BiblioDeck* Instance = new BiblioDeck();
	return Instance;	
}

 BiblioDeck::BiblioDeck()
 {
	m_DeckPrincipal = NULL;
	m_DeckPrincipal = new Deck();
	LoadDeck();
 }


 BiblioDeck::~BiblioDeck()
 {
	delete m_DeckPrincipal;
 }


void BiblioDeck::LoadDeck()
{
	std::ifstream DataScores  ;
	std::ofstream DaTa;
	bool DefautDeck = false;
	

	DataScores.open("Assets/BiblioDeck.DAT",std::ios::in | std::ios::binary);


	// << création du fichier s'il nexiste pas  >>
	if( !DataScores.is_open() )
	{
		LOG("ouverture du fichier BiblioDeck echoue ! " )
		LOG("Creation d'un fichier..." )
		DaTa.open("Assets/BiblioDeck.DAT",std::ios::out | std::ios::binary  );

		if(DaTa.is_open())
		{
			DaTa.close();
		}
		else
		{
			LOG("problème de création de la bibliothèque de deck")
				exit(-1);
		}

		DataScores.open("Assets/BiblioDeck.DAT",std::ios::in | std::ios::binary);

		if(DataScores.is_open())
		{
			LOG("Fichier creer")
			DataScores.close();
		}

		//création d'un deck par defaut
		FabriqueDefautDeck();
		SaveDeck();
		DefautDeck = true;
	}

	if( !DefautDeck)
	{		

		if ( DataScores.is_open() )
		{

			while( !DataScores.eof() )
			{
				T_infosDeck TempInfos;

				DataScores.read( (char*)&TempInfos, sizeof(T_infosDeck) );				

				std::string TempString = TempInfos.nom ;

				m_DeckPrincipal->AjouterCarteAuDeck( BIBLI->CreerCartes( TempString ) );

			}
			DataScores.close();
		}
		else
		{
			LOG("la création a echouer" )
		}
	}
}


bool BiblioDeck::SaveDeck()
{
	std::ofstream DataScores ;

	DataScores.open("Assets/BiblioDeck.DAT",std::ios::out | std::ios::binary);

	if( !DataScores.is_open() )
	{
		
		LOG("Erreur lors de la sauvegarde de la biblioDeck")
		return false;
	}
	else
	{
		if( m_DeckPrincipal )
		{
			for(int i = 0; i < MAX_CARTE ; ++i)
			{
				Carte* TempCarte = m_DeckPrincipal->getCarte(i);

				if(TempCarte)
				{
					std::string NomAStocker = TempCarte->getInfosCarte().m_name;
					T_infosDeck TempInfos;

					int index = 0; 

					for(int i = 0 ; (i < 30) && i < NomAStocker.size()  ; ++i)
					{
						index++;
						TempInfos.nom[i] = NomAStocker[i];
					}

					if( index >=30)
						index = 29;

					TempInfos.nom[index] = '\0';

					DataScores.write( (char*)&TempInfos, sizeof(T_infosDeck) );	
				}
			}
		}
			
		DataScores.close();
		return true;
	}
}


void BiblioDeck::FabriqueDefautDeck()
{
	int NombreCarteDansBibli = BIBLI->getNbreCarte();
	int i =0;
	int NombreCarte = 0;
	 
	while( !m_DeckPrincipal->ValideDeck() && NombreCarteDansBibli > 0)
	{
		T_carte Temp  = BIBLI->getInfosCartes(i) ;

		i++;
		if( i >= NombreCarteDansBibli)
			i =0;

		m_DeckPrincipal->AjouterCarteAuDeck( BIBLI->CreerCartes(Temp.m_name) );
	}	

}

