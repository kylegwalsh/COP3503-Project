#include <iostream>
#include <string>
#include <conio.h>
#include <ctime>

int level = 1;
Map m;
string message = "";

void game()
{
	ResizeScrn();
	StartScrn();
	
	Player al();
	
	while(true)
	{	
		if (playLevel(level, &al))
		{
			level++;
		}
	}
}

bool combat(Enemy enemy, Player* al)
{
	
}

void doStuff(char place)
{
	//if house, do stuff
	//if barracks, do other stuff,
	//if tower, other stuff
	//if gatorade, +gatorade
	
	//end with prev position
}

void playLevel(Player* al)
{
	char dir;
	int x, y;
	string place;
	
	bool bossBeaten = false;
	bool keyFound = false;
	bool alive = true;
	bool moved = false;
	
	Enemy bosses[3];
	bosses[0] = new Dragon();
	bosses[1] = new Gorilla();
	bosses[2] = new Seminole();
	
	Enemy type1[3], type2[3];
	
	switch level:
	{
		case 1: Level1IntroScrn();
		
		case 2: Level2IntroScrn();
		
		case 3: Level3IntroScrn();
	}
	
	m = Map(level);
	map = m.getMapData();
	allow = m.getAllowableArea();
	
	//place character?
	
	while(!bossBeaten)
	{
		moved = false;
		
		x = al->GetXLocation();
		y = al->GetYLocation();
	
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
					al->MoveUp();
					moved = true;
				}
				break;
			case 's': 
				//if possible, move down
				if (allow[y+1][x] == 1)
				{
					al->MoveDown();
					moved = true;
				}
				break;
			case 'a': 
				//if possible, move left
				if (allow[y][x-1] == 1)
				{
					al->MoveLeft();
					moved = true;
				}
				break;
			case 'd': 
				//if possible, move right
				if (allow[y][x+1] == 1)
				{
					al->MoveRight();
					moved = true;
				}
				break;
			case 'q':
				//quit screen
				break;
			default:
				break;
		}
		
		if (moved)
		{
			//with new position
			 x = al->GetXLocation();
			 y = al->GetYLocation();
			 
			 place = map[y][x];
			 
			 if (place.compare("H") == 0)
			 {
				 doStuff('H');
				 //find key, gatorade, food, or monster?
			 }
			 else if (place.compare("T") == 0)
			 {
				 doStuff('T');
			 }
			 else if(place.compare("G") == 0)
			 {
				 doStuff('G');
				 //get gatorade, how much?
			 }
			 else if (place.compare("M") == 0)
			 {
				 doStuff('M');
				 //sleep? recovers hp?
			 }
			 else if (place.compare("B") == 0)
			 {
				 if (keyFound) 
				 {
					 bossBeaten = combat(bosses[lev-1], al);
					 alive = bossBeaten;
				 }
				 else message="You must find the key before you can battle the boss!";
			 }
			 else //if place=/
			 {
				 srand(time(0));
				 if (rand()%10 == 0) //10% chance of finding an enemy
				 {
					 //chooses randomly bat or scorpion
					 if (rand()%2 == 0)
					 {
						 alive = combat(type1[lev-1], al);
					 }
					 else
					 {
						 alive = combat(type2[lev-2], al);
					 }
				 }
			 }
			 //check stats
			 if (al->GetHealth()<=0 || !alive)
				GameOverScrn();
				//change level?
		}
		update();
	}
}

void printMap()

void update()
{
	int spaces = (20-m.getRows())/2;
	//prints screen
	cout<<" ----------------------------------------------------------------------- \n";
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
	cout<<" ----------------------------------------------------------------------- \n";
	
}
