#include <iostream>
#include <string>
//#include <conio.h>
#include <ctime>
#include "screen.h"
#include "character.h"
#include "Map.h"

class Game
{
	private:
		int level;
		int horizontalPadding;
		Map map;
		string message;
		Player al;
		bool playing;
		std::vector< std::vector<std::string> > mapData;
		std::vector< std::vector<int> > allow;

		bool combat(Player al, Enemy enemy);
		void playLevel();
		void printMap();
		void update();
		void gameOver();
		void setHorizontalPadding();
		void loadNextLevel();
		

	public:
		Game();
};
