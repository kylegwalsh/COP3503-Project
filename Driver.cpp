#include "game.h" 
#include "MapCreator.h"

/*
* Main method 
* Creates new maps for the game
* Instantiates game and starts
*/
int main()
{
	MapCreator mC = MapCreator();
	for (int i=0; i<3; i++)
	{
		mC.createNewLevel();
	}
	game g = game();
	g.start();
}