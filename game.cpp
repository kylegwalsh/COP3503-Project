#include "game.h"

Game::Game()
{
	ResizeScrn();
	StartScrn();
	map = Map();
	setHorizontalPadding();
};

void Game::start()
{
	playing = true;
	while (playing)
	{
		playLevel();
	}
}

void Game::setHorizontalPadding()
{
	horizontalPadding = (70-map.getColumns())/2;
}

bool Game::combat(Player al, Enemy enemy)
{
	return true;
};

void Game::playLevel()
{
	al.SaveStats();
	
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
	
	mapData = map.getMapData();
	
	//place character: bottom middle
	x = map.getColumns()/2;
	y = map.getRows();
	
	al.SetLocation(x, y);
	
	update();
	
	uniform_int_distribution<mt19337::result_type> dist(1,100);
	int random;

	while(!bossBeaten)
	{
		random = dist(al.gen);

		moved = false;
		
		allow = map.getAllowableArea();
		
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
				QuitScrn();
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
			 
			 //house
			 if (place.compare("H") == 0)
			 {
				 if (random<=40)
				 {
				 	al.FindFood();
				 }
				 if (random>40 && <=80)
				 {
				 	alive = combat(al, *type1[level-1]);
				 }
				 if (random>80 && <=90)
				 {
				 	message = "You found a nice comfy little bed to sit your butt on! Gained health && stamina!"
				 	al.sleep();
				 }
				 if (random>90)
				 {
				 	message = "You stubbed your toe! You lost 5 health!";
				 	al.ChangeHealth(-5);
				 }
				 allow[y][x] = 0;
			}
			//tower
			else if (place.compare("T") == 0)
			{
				alive = combat(al, *type1[level-1]);
				alive = combat(al, *type2[level-1]);
				if (alive)
				{
					keyFound = true;
				}
				allow[y][x] = 0;
			 }
			else if(place.compare("G") == 0)
			{
				 al.FindGatorade();
				 message = "You found a Gatorade machine! Your Gatorade has increased!";
				 allow[y][x] = 0;
			}
			//barracks
			else if (place.compare("M") == 0)
			{
				if (random<=10)
				{
					message = "You stepped on a landmine";
					al.ChangeHealth(-25);
				}
				if (random>10 && random<=20)
				{
					message = "You found some good eats";
					al.FindFood();
					al.FindFood();
				}
				if (random>20 && random<=50)
				{
					alive = combat(al, *type2[level-1]);
					alive = combat(al, *type2[level-1]);
				}
				if (random>50 && random<=65)
				{
					alive = combat(al, *type1[level-1]);
					alive = combat(al, *type2[level-1]);
				}
				if (random>65 && random<=75)
				{
					message = "You got caught in a booby trap, and got a little banged up";
					al.ChangeHealth(-15);
				}
				if (random>75 && random<=97)
				{
					message = "You found one of Alberta's scales! Now you're motivated";
					al.ChangeStamina(10);
				}
				if (random>97)
				{
					alive = combat(al, *type2[level-1]);
					alive = combat(al, *type1[level-1]);
					alive = combat(al, *type2[level-1]);
				}
			}
			//level boss
			else if (place.compare("B") == 0)
			{
				 if (keyFound) 
				 {
					 bossBeaten = combat(&al, *bosses[level-1]);
					 alive = bossBeaten;
					 if (bossBeaten)
					 {
						if (level==3)
						{
							BeatGameScrn();
							playing = false;
						}
						else
						{
							loadNextLevel();
						}
					 }
				 }
				 else 
				 {
				 	message="You must find the key before you can battle the boss!";
				 }
			}
			else //if place=/
			{
				 if (random<=10)
				 {
					 //chooses randomly type 1 or type 2 enemy for level
				 	 random = dist(al.gen)
					 if (random<=62)
					 {
						 alive = combat(&al, *type1[level-1]);
					 }
					 else
					 {
						 alive = combat(&al, *type2[level-1]);
					 }
				 }
			}
		}
		
		//check stats
		if (al.GetHealth()<=0 || !alive)
		{
			if (GameOverScrn()) //user chose to continue, starts level over
			{
				al.RevertStats();
				//reset level map
				keyFound = false;
			}
			else //user chose not to continue
			{
				playing = false;
				break;
			}
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

void Game::printMap(int playerX, int playerY) //changed to include border because pretty
{
	
	for (int i=0; i<rows; i++)
	{
		for (int p=0; p<horizontalPad; p++)
		{
			std::cout << " ";
		}
		for (int j=0; j<columns; j++)
		{
			if (allow[i][j]==1)
			{
				if (i==playerY && j==playerX)
				{
					std::cout << "@" << " ";
				}
				else 
				{
					std::cout << mapData[i][j] << " ";
				}
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
	int verticalPadding = (20-map.getRows())/2;
	//prints screen
	cout<<" ======================================================================= \n";
	cout<<"| "<<al.PrintMapStats()<<std::string(69-(al.PrintMapStats().size()), ' ')<<"|\n";
	cout<<"|-----------------------------------------------------------------------|\n";
	for (int i=0; i<verticalPadding; i++)
	{
		cout<<"|                                                                       |\n";
	}
	place\
	for (int i=0; i<verticalPadding; i++)
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
