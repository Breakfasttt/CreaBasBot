//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 30/01/2013 - 13h29
// Fichier : Programme principal de CreaBasBot .cpp
// Dernière modification : 30/01/2013
//@@@@@@@@@@@@@@@@@@@


#include "Game.hpp"



int main()
{
	srand(time(NULL));
	Game MainGame;

	MainGame.init();
	MainGame.update();
	MainGame.deinit();

	return 0;
}
