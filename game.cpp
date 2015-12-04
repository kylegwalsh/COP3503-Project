#include "game.h"

Game::Game()
{
	ResizeScrn();
	StartScrn();
	
	playing=true;

	map = Map();
	setPadding();
	
	while(playing)
	{	
		playLevel();
		
		//if quit, break
		//else level++
	}
};

Game::setHorizontalPadding()
{
	horizontalPadding = (70-map.getColumns())/2;
}

bool Game::combat(Player al, Enemy enemy)
{
	return true;
};

void Game::playLevel()
{
	//~ random_device rd;
	//~ mt19937 gen(rd());
	
	char dir;
	int x, y;
	string place;
	
	bool bossBeaten = false;
	bool keyFound = false;
	bool alive = true;
	bool moved = false;
	
	Enemy** bosses = new Enemy*[3];
	bosses[0] = new Dragon();
	bosses[1] = new Gorilla();
	bosses[2] = new Seminole();
	
	Enemy** type1 = new Enemy*[3];
	Enemy** type2 = new Enemy*[3];
	
	switch (level)
	{
		case 1:
			Level1IntroScrn();
			break;
			
		case 2:
			Level2IntroScrn();
			break;
			
		case 3:
			Level3IntroScrn();
	}
	
	//place character?
	
	update();
	
	while(!bossBeaten)
	{
		moved = false;
		
		x = al.GetxLocation();
		y = al.GetyLocation();
	
		type1[0] = new Bat();
		type1[1] = new Rhino();
		type1[2] = new Centaur();
		
		type2[0] = new Scorpion();
		type2[1] = new Tiger();
		type2[2] = new Griffin();
		
		//if possible -> move
		dir = getch();
		
		switch(dir)
		{
			case 'w': 
				//if possible, move up
				if (allow[y-1][x] == 1)
				{
					al.MoveUp();
					moved = true;
				}
				break;
			case 's': 
				//if possible, move down
				if (allow[y+1][x] == 1)
				{
					al.MoveDown();
					moved = true;
				}
				break;
			case 'a': 
				//if possible, move left
				if (allow[y][x-1] == 1)
				{
					al.MoveLeft();
					moved = true;
				}
				break;
			case 'd': 
				//if possible, move right
				if (allow[y][x+1] == 1)
				{
					al.MoveRight();
					moved = true;
				}
				break;
			case 'q':
				//quit screen
				break;
			default:
				message = "Invalid key pressed!";
				break;
		}
		
		if (moved)
		{
			//with new position
			 x = al.GetxLocation();
			 y = al.GetyLocation();
			 
			 place = mapData[y][x];
			 
			 if (place.compare("H") == 0)
			 {
				 //find key, food, or monster?
			 }
			 else if (place.compare("T") == 0)
			 {
				 //find food or monster
			 }
			 else if(place.compare("G") == 0)
			 {
				 al.FindGatorade();
				 message = "You found a Gatorade machine! Your Gatorade has increased!";
			 }
			 else if (place.compare("M") == 0)
			 {
				 //sleep; recovers hp
				 int toAdd = al.GetMaxHealth()-al.GetHealth();
				 al.ChangeHealth(toAdd);
				 message = "You took a rest in the Barracks. Health is now full!";
			 }
			 else if (place.compare("B") == 0)
			 {
				 if (keyFound) 
				 {
					 bossBeaten = combat(al, *bosses[level-1]);
					 alive = bossBeaten;
					 if (bossBeaten)
					 {
					 	loadNextLevel();
					 }
				 }
				 else message="You must find the key before you can battle the boss!";
			 }
			 else //if place=/
			 {
				 srand(time(0)); //might not need this line?
				 if (rand()%10 == 0) //10% chance of finding an enemy
				 {
					 //chooses randomly bat or scorpion
					 if (rand()%2 == 0)
					 {
						 alive = combat(al, *type1[level-1]);
					 }
					 else
					 {
						 alive = combat(al, *type2[level-1]);
					 }
				 }
			 }
			 //check stats
			 if (al.GetHealth()<=0 || !alive)
				GameOverScrn();
		}
		update();
	}
};

void Game::loadNextLevel()
{
	level++;
	map.loadNext();
	mapData = map.getMapData();
	allow = map.getAllowableArea();
	setHorizontalPadding();
}

void Game::printMap() 
{
	for (int i=0; i<rows; i++)
	{
		for (int p=0; p<horizontalPad; p++)
		{
			std::cout << " ";
		}
		for (int j=0; j<columns; j++)
		{
			if (allow[i][j])
			{
				std::cout << mapData[i][j] << " ";
			}
			else
			{
				std::cout << "X" << " ";
			}
		}
	}
}

void Game::update()
{
	int spaces = (20-map.getRows())/2;
	//prints screen
	cout<<" ======================================================================= \n";
	cout<<"| "<<al.PrintMapStats()<<std::string(69-(al.PrintMapStats().size()), ' ')<<"|\n";
	cout<<"|-----------------------------------------------------------------------|\n";
	for (int i=0; i<spaces; i++)
	{
		cout<<"|                                                                       |\n";
	}
	printMap();
	for (int i=0; i<spaces; i++)
	{
		cout<<"|                                                                       |\n";
	}
	cout<<"|-----------------------------------------------------------------------|\n";
	cout<<"|  Messages: "<<message<<string(58-message.size(), ' ')<<"|\n";
	cout<<"|                                                                       |\n";
	cout<<"|  Controls: wasd - move		q - quit	other controls?                |\n";
	cout<<"|                                                                       |\n";
	cout<<" ======================================================================= \n";
	
};
