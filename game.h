#include <iostream>
#include <string>
//#include <curses.h>
#include <ctime>
#include "screen.h"
#include "character.h"
#include "MapCreator.h"
#include "Map.h"

class Game
{
	private:
		int level;
		Map map;
		string message;
		Player al;
	public:
		Game();
		bool combat(Enemy enemy);
		void playLevel();
		void printMap();
		void update();
		void gameOver();
}
