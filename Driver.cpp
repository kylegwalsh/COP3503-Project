#include "game.h" 
#include "MapCreator.h"

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