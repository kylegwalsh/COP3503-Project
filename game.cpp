/*
 * game.cpp
 *
 *  Created on: Dec 5, 2015
 *      Author: Kyle
 */

#include "game.h"

//constructs the overall game object
Game::Game()
{
	level = 1;
	ResizeScrn();
	StartScrn();
	map = Map();
	initializeAllowableArea();
	setHorizontalPadding();
}

//starts the game
void Game::start()
{
	playing = true;
	playLevel();
}

//sets the horizontal padding (which is the amount of spaces that must be printed on the sides of the map)
void Game::setHorizontalPadding()
{
	horizontalPadding = (70 - (2 * map.getColumns())) / 2;
}

//the primary method for the game
//initializes the level and loops until the level is beaten
void Game::playLevel()
{
	//re-saves the player's stats
	al.SaveStats();

	char dir;
	int x, y;
	string place;

	bool bossBeaten = false;
	bool keyFound = false;
	bool moved = false;

	//creates and stores the first 2 bosses
	Enemy** bosses = new Enemy*[2];
	bosses[0] = new Dragon();
	bosses[1] = new Gorilla();

	//creates the final boss
	Seminole s;

	//creates the random enemies that will pop up throughout the game
	//type 1 is weaker than type 2
	Enemy** type1 = new Enemy*[3];
	Enemy** type2 = new Enemy*[3];

	//prints out the intro screen based on the level
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
		break;
	}

	//stores the maps data in a game field
	mapData = map.getMapData();

	//place character: bottom middle
	x = (map.getColumns() - 1) / 2;
	y = map.getRows() - 1;
	al.SetLocation(x, y);

	//a random number generator that will determine what events take place in the game
	uniform_int_distribution < mt19937::result_type > dist(1, 100);
	mt19937 gen = al.GetGen();
	int random;

	//loops until the player quits or the boss is beaten
	while (playing == true && !bossBeaten)
	{
		//checks if al has enough experience to level up
		if (al.GetExperience() >= al.GetLevelUpEXP())
		{
			al.LevelUp();
			LevelUpScrn();
		}

		//prints out the map screen
		update();

		//reverts the values stored in game at the start of each loop
		message = "";
		random = dist(gen);
		moved = false;

		//sets x and y to the player's new location
		x = al.GetxLocation();
		y = al.GetyLocation();

		//adds new enemies to the enemy type vectors to randomize their levels
		type1[0] = new Bat();
		type1[1] = new Rhino();
		type1[2] = new Centaur();

		type2[0] = new Scorpion();
		type2[1] = new Tiger();
		type2[2] = new Griffin();

		//if possible -> move
		dir = getch();

		switch (dir)
		{
		case 'w':
			//if possible, move up
			if ((y - 1) >= 0 && allow[y - 1][x])
			{
				al.MoveUp();
				moved = true;
			}
			break;
		case 's':
			//if possible, move down
			if ((y + 1) < map.getRows() && allow[y + 1][x])
			{
				al.MoveDown();
				moved = true;
			}
			break;
		case 'a':
			//if possible, move left
			if ((x - 1) >= 0 && allow[y][x - 1])
			{
				al.MoveLeft();
				moved = true;
			}
			break;
		case 'd':
			//if possible, move right
			if ((x + 1) < map.getColumns() && allow[y][x + 1])
			{
				al.MoveRight();
				moved = true;
			}
			break;
		case '3':
			//if possible, eat
			message = al.Eat();
			break;
		case '4':
			//if possible, drink
			message = al.Drink();
			break;
		case 'q':
			//calls quit screen
			QuitScrn();
			break;
		default:
			//creates error if invalid key is pressed
			message = "Invalid key pressed!";
			break;
		}

		//runs if the player has moved on the map
		if (moved)
		{
			//with new position
			x = al.GetxLocation();
			y = al.GetyLocation();

			//stores the place value located at the player's location
			place = mapData[y][x];

			//triggers if the player enters a house
			if (place.compare("H") == 0)
			{
				//find food
				if (random <= 75)
				{
					message = "You found some food in the House";
					al.FindFood();
				}
				//trigger non-fleeable combat
				if (random > 75 && random <= 85)
				{
					playing = NFCombat(&al, type1[level - 1]);
				}
				//find bed and sleep
				if (random > 85 && random <= 95)
				{
					message = "You found a nice comfy bed. Gained health && stamina!";
					al.Sleep();
				}
				//stub toe and lose health
				if (random > 95)
				{
					message = "You stubbed your toe! You lost 5 health!";
					al.ChangeHealth(-5);
				}
				//makes the house no longer enterable
				allow[y][x] = 0;
			}
			//triggers if the player enters a tower
			else if (place.compare("T") == 0)
			{
				//combat with an enemy of both type
				playing = NFCombat(&al, type1[level - 1]);
				playing = NFCombat(&al, type2[level - 1]);

				//if the player survives he gets the key to the boss
				if (playing)
				{
					keyFound = true;
				}
				//makes the tower no longer enterable
				allow[y][x] = 0;
			}
			//triggers if the player finds a gatorade machine
			else if (place.compare("G") == 0)
			{
				//find gatorade
				al.FindGatorade();
				message = "You found a Gatorade machine! Your Gatorade has increased!";
				allow[y][x] = 0;
			}
			//triggers if the player enters barracks
			else if (place.compare("M") == 0)
			{
				//step on landmine
				if (random <= 10)
				{
					message = "You stepped on a landmine";
					al.ChangeHealth(-20);
				}
				//find extra food
				if (random > 10 && random <= 30)
				{
					message = "You found some army rations!";
					al.FindFood();
					al.FindFood();
				}
				//fight two strong enemies
				if (random > 30 && random <= 50)
				{
					playing = NFCombat(&al, type2[level - 1]);
					playing = NFCombat(&al, type2[level - 1]);
				}
				//fight a strong and weak enemy
				if (random > 50 && random <= 65)
				{
					playing = NFCombat(&al, type1[level - 1]);
					playing = NFCombat(&al, type2[level - 1]);
				}
				//caught in a booby trap and lose health
				if (random > 65 && random <= 75)
				{
					message = "You got caught in a booby trap, oops!";
					al.ChangeHealth(-5);
				}
				//find scale and gain stamina
				if (random > 75 && random <= 97)
				{
					message = "You found one of Alberta's scales! Your stamina returns!";
					al.ChangeStamina(10);
				}
				//fight 3 monsters
				if (random > 97)
				{
					playing = NFCombat(&al, type2[level - 1]);
					playing = NFCombat(&al, type1[level - 1]);
					playing = NFCombat(&al, type2[level - 1]);
				}
				//makes the barracks no longer enterable
				allow[y][x] = 0;
			}
			//level boss
			else if (place.compare("B") == 0)
			{
				//key used to fight boss
				if (keyFound)
				{
					//first two bosses
					if (level < 3)
					{
						bossBeaten = NFCombat(&al, bosses[level - 1]);
						playing = bossBeaten;
					}
					//final boss
					if (level == 3)
					{
						bossBeaten = FinalBossCombat(&al, &s);
						playing = true;
					}

					if (bossBeaten)
					{
						//beat game
						if (level == 3)
						{
							BeatGameScrn();
						}
						//move to next level
						else
						{
							loadNextLevel();
						}
					}
				}
				else
				{
					message = "You must find the key before you can battle the boss!";
				}
			}
			else //if place="//"
			{
				if (random <= 17)
				{
					//chooses randomly type 1 or type 2 enemy for level
					random = dist(gen);
					if (random <= 62)
					{
						playing = Combat(&al, type1[level - 1]);
					}
					else
					{
						playing = Combat(&al, type2[level - 1]);
					}
				}
			}
		}

		//check to see if player is dead or quit
		if (al.GetHealth() == 0 || (!playing && !bossBeaten))
		{
			GameOverScrn();
		}

		//cleans the game if you are no longer playing
		if (playing == false)
		{
			Clean(bosses, type1, type2);
		}

		//removes old enemies so that new enemies can be initialized at the beginning of the loop
		for (int i = 0; i < 3; i++)
		{
			delete type1[i];
			delete type2[i];
		}
	}
}

//loads the next level
void Game::loadNextLevel()
{
	level++;
	map.loadNext();
	mapData = map.getMapData();
	initializeAllowableArea();
	setHorizontalPadding();
	playLevel();
}

/*
 * Initializes the int representeted boolean vector with all ones
 * All of the map is allowable at the beginning of the level
 */
void Game::initializeAllowableArea()
{
	//clears the previous allowable area
	allow.clear();

	//initializes the new allowable area of the map
	for (int i = 0; i < map.getRows(); i++)
	{
		vector<int> rowVec;
		for (int j = 0; j < map.getColumns(); j++)
		{
			rowVec.push_back(1);
		}
		allow.push_back(rowVec);
		rowVec.clear();
	}
}

//prints the map
void Game::printMap(int playerX, int playerY)
{
	for (int i = 0; i < map.getRows(); i++)
	{
		cout << "|";
		for (int p = 0; p <= horizontalPadding; p++)
		{
			std::cout << " ";
		}
		for (int j = 0; j < map.getColumns(); j++)
		{
			if (allow[i][j] == 1)
			{
				if (i == playerY && j == playerX)
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
				if (i == playerY && j == playerX)
				{
					std::cout << "@" << " ";
				}
				else
				{
					std::cout << "X" << " ";
				}
			}
		}
		for (int p = 0; p < horizontalPadding; p++)
		{
			std::cout << " ";
		}
		cout << "|\n";
	}
}

//prints the overall map screen
void Game::update()
{
	ClearScrn();

	int verticalPadding = (20 - map.getRows()) / 2;

	//prints screen
	cout << " ======================================================================= \n";
	cout << "|" << al.PrintMapStats() << string(71 - (al.PrintMapStats().size()), ' ') << "|\n";
	cout << "|-----------------------------------------------------------------------|\n";
	for (int i = 0; i < verticalPadding; i++)
	{
		cout << "|                                                                       |\n";
	}

	printMap(al.GetxLocation(), al.GetyLocation());

	for (int i = 0; i < verticalPadding; i++)
	{
		cout << "|                                                                       |\n";
	}
	cout << "|-----------------------------------------------------------------------|\n";
	cout << "|  Messages: " << message << string(58 - message.size(), ' ') << " |\n";
	cout << "|                                                                       |\n";
	cout << "|  Controls: wasd - move, 3. Eat 4. Drink             q - quit          |\n";
	cout << "|                                                                       |\n";
	cout << " ======================================================================= \n";

}

//prints the outline of max screen for the player to resize their console
void Game::ResizeScrn()
{
	ClearScrn();

	for (int i = 0; i < 31; i++)
	{
		if (i == 0 || i == 29)
		{
			cout << "|================================================================================|";
			if (i == 0)
			{
				cout << endl;
			}
		}
		if (i == 14)
		{
			cout << "|         Please resize the console so that the square fills the console.        |\n";
		}
		if (i == 15)
		{
			cout << "|                          (Press any key to continue)                           |\n";
		}
		if ((i > 0 && i < 14) || (15 > 13 && i < 29))
		{
			cout << "|                                                                                |\n";
		}
	}

	getch();
}

//prints the start screen
void Game::StartScrn()
{
	ClearScrn();

	/*|================================================================================|
	 |                .^^^\ ../~/\        .==...==.                                   |
	 |              .^\ /\  \    --------- O    O,                                    |
	 |             / \  \/    ---         ,..-----,                                   |
	 |            / \_\-          _,v.v^V^ ,/\^^^/                                    |
	 |           | \/       /^v^V^   _,.-^^  .,,/                                     |
	 |            \-\   (   \..,^^--^   .---^                                         |
	 |             \--.__________.---'^^                  Saving Alberta              |
	 |          .-----.__________.-------,._                                          |
	 |      _,=^\                            ".                                       |
	 |    .^             |||||||||||           '                                      |
	 |   /  \             ||      ||   )   /    \                                     |
	 |  | -      /        ||           )''\,... |                                     |
	 |  | ,,../^^\        ||||||       /  /     \                                     |
	 |  |^     \  \       ||          /  (      )                                     |
	 |  (     \/  /\      ||         /    \/_/_/                                      |
	 |   \_\_\/  |(______||||_______)|                                                |
	 |                                                                                |
	 |                                                                                |
	 |                                                                                |
	 |                                                                                |
	 |                Prepare for danger as you search for Alberta and                |
	 |                her kidnapers in this Gator approved adventure.                 |
	 |                            (Enter any key to start)                            |
	 |                                                                                |
	 |                                                                                |
	 |                                                                                |
	 |                                                                                |
	 |                                                                                |
	 |                                                                                |
	 |================================================================================|*/
	cout
			<< "|================================================================================|\n|               .^^^\\ ../~/\\        .==...==.                                    |\n|             .^\\ /\\  \\    --------- O    O,                                     |\n|            / \\  \\/    ---         ,..-----,                                    |\n|           / \\_\\-          _,v.v^V^ ,/\\^^^/                                     |\n|          | \\/       /^v^V^   _,.-^^  .,,/                                      |\n|           \\-\\   (   \\..,^^--^   .---^                                          |\n|            \\--.__________.---\'^^                  Saving Alberta               |\n|         .-----.__________.-------,._                                           |\n|     _,=^\\                            \".                                        |\n|   .^             |||||||||||           \'                                       |\n|  /  \\             ||      ||   )   /    \\                                      |\n| | -      /        ||           )\'\'\\,... |                                      |\n| | ,,../^^\\        ||||||       /  /     \\                                      |\n| |^     \\  \\       ||          /  (      )                                      |\n| (     \\/  /\\      ||         /    \\/_/_/                                       |\n|  \\_\\_\\/  |(______||||_______)|                                                 |\n|                                                                                |\n|                                                                                |\n|                                                                                |\n|                                                                                |\n|                Prepare for danger as you search for Alberta and                |\n|                her kidnapers in this Gator approved adventure.                 |\n|                            (Enter any key to start)                            |\n|                                                                                |\n|                                                                                |\n|                                                                                |\n|                                                                                |\n|                                                                                |\n|================================================================================|";

	getch();
}

//prints the level one intro screen
void Game::Level1IntroScrn()
{
	ClearScrn();

	for (int i = -2; i < 28; i++)
	{
		if (i == -2 || i == 27)
		{
			cout << "|================================================================================|";
			if (i == -2)
			{
				cout << endl;
			}
		}
		if (i < 0)
		{
			cout << "|                                                                                |\n";
		}
		if (i == 6)
		{
			cout << "|                                   Chapter 1                                    |\n";
		}
		if (i == 8)
		{
			cout << "|           As the sun started to rise over the swamp, Albert the Gator          |\n";
		}
		if (i == 9)
		{
			cout << "|           awoke face down in the mud. A large bump was visible on his          |\n";
		}
		if (i == 10)
		{
			cout << "|           head, but he couldn't remember what had happened the night           |\n";
		}
		if (i == 11)
		{
			cout << "|           before (like most college kids). He looked around for a              |\n";
		}
		if (i == 12)
		{
			cout << "|           moment and realized that Princess Alberta was nowhere to             |\n";
		}
		if (i == 13)
		{
			cout << "|           be found. In her place he found a note saying \"Chomp on              |\n";
		}
		if (i == 14)
		{
			cout << "|           that\". Determined and Angry, Albert departed the swamp.              |\n";
		}
		if (i == 15)
		{
			cout << "|           He knew exactly where to start looking.                              |\n";
		}
		if (i == 16)
		{
			cout << "|                          (Press any key to continue)                           |\n";
		}
		if ((i > 0 && i < 6) || i == 7 || (i > 16 && i < 27))
		{
			cout << "|                                                                                |\n";
		}
	}

	getch();
}

//prints the level 2 intro screen
void Game::Level2IntroScrn()
{
	ClearScrn();

	for (int i = -2; i < 28; i++)
	{
		if (i == -2 || i == 27)
		{
			cout << "|================================================================================|";
			if (i == -2)
			{
				cout << endl;
			}
		}
		if (i == 7)
		{
			cout << "|                                   Chapter 2                                    |\n";
		}
		if (i == 9)
		{
			cout << "|           As the Dragon fell to its side it called out, \"Your dear             |\n";
		}
		if (i == 10)
		{
			cout << "|           princess isn't here. If you wish to find her you must                |\n";
		}
		if (i == 11)
		{
			cout << "|           venture into the jungle, it is only there where you will             |\n";
		}
		if (i == 12)
		{
			cout << "|           discover her fate!\" The dragon then disappeared into a               |\n";
		}
		if (i == 13)
		{
			cout << "|           cloud of smoke and Albert continued on his journey,                  |\n";
		}
		if (i == 14)
		{
			cout << "|                           this time into the jungle.                           |\n";
		}
		if (i == 15)
		{
			cout << "|                          (Press any key to continue)                           |\n";
		}
		if ((i > -2 && i < 7) || i == 8 || (i > 15 && i < 27))
		{
			cout << "|                                                                                |\n";
		}
	}

	getch();
}

//prints the level 3 intro screen
void Game::Level3IntroScrn()
{
	ClearScrn();

	for (int i = -2; i < 28; i++)
	{
		if (i == -2 || i == 27)
		{
			cout << "|================================================================================|";
			if (i == -2)
			{
				cout << endl;
			}
		}
		if (i == 7)
		{
			cout << "|                                    Chapter 3                                   |\n";
		}
		if (i == 9)
		{
			cout << "|           Bubbles jumped back and yelled, \"Oh no, Bubbles don't get            |\n";
		}
		if (i == 10)
		{
			cout << "|           payed enough for this, baby. The guy who took your girl              |\n";
		}
		if (i == 11)
		{
			cout << "|           went through that portal. I'm out of here!\" Then Bubbles             |\n";
		}
		if (i == 12)
		{
			cout << "|           vanished out the window and Albert was one step closer to            |\n";
		}
		if (i == 13)
		{
			cout << "|           Alberta. He stepped through the portal and into a strange            |\n";
		}
		if (i == 14)
		{
			cout << "|           land where he hoped to find his precious princess.                   |\n";
		}
		if (i == 15)
		{
			cout << "|                          (Press any key to continue)                           |\n";
		}
		if ((i > -2 && i < 7) || i == 8 || (i > 15 && i < 27))
		{
			cout << "|                                                                                |\n";
		}
	}

	getch();
}

//prints the beat the game screen
void Game::BeatGameScrn()
{
	ClearScrn();

	for (int i = -2; i < 28; i++)
	{
		if (i == -2 || i == 27)
		{
			cout << "|================================================================================|";
			if (i == -2)
			{
				cout << endl;
			}
		}
		if (i == 8)
		{
			cout << "|                                Congratulations!                                |\n";
		}
		if (i == 10)
		{
			cout << "|           With the Seminole King defeated, Princess Alberta                    |\n";
		}
		if (i == 11)
		{
			cout << "|           was finally safe and the swamp returned to its once                  |\n";
		}
		if (i == 12)
		{
			cout << "|           peaceful self. The two Gators could at last return                   |\n";
		}
		if (i == 13)
		{
			cout << "|           home and live happily ever after.                                    |\n";
		}
		if (i == 15)
		{
			cout << "|                                    THE END!                                    |\n";
		}
		if ((i > -2 && i < 8) || i == 9 || i == 14 || (i > 15 && i < 27))
		{
			cout << "|                                                                                |\n";
		}
	}

	playing = false;
}

//prints 35 blank lines to clear screen
void Game::ClearScrn()
{
	for (int i = 0; i < 35; i++)
	{
		cout << endl;
	}
}

//prints the level up screen
void Game::LevelUpScrn()
{
	ClearScrn();

	for (int i = -2; i < 28; i++)
	{
		if (i == -2 || i == 27)
		{
			cout << "|================================================================================|";
			if (i == -2)
			{
				cout << endl;
			}
		}
		if (i == 11)
		{
			cout << "|                                Congratulations!                                |\n";
		}
		if (i == 13)
		{
			cout << "|                               You've leveled up!                               |\n";
		}
		if (i == 14)
		{
			cout << "|                          (Press any key to continue)                           |\n";
		}
		if ((i > -2 && i < 11) || i == 12 || (i > 14 && i < 27))
		{
			cout << "|                                                                                |\n";
		}
	}

	getch();
}

//prints the game over screen
void Game::GameOverScrn()
{
	//sets playing back equal to true and gives the player a chance to try again
	playing=true;

	ClearScrn();
	while (playing == true)
	{
		for (int i = -2; i < 28; i++)
		{
			if (i == -2 || i == 27)
			{
				cout << "|================================================================================|";
				if (i == -2)
				{
					cout << endl;
				}
			}
			if (i == 10)
			{
				cout << "|                                   Game Over!                                   |\n";
			}
			if (i == 12)
			{
				cout << "|                                Sorry, you died.                                |\n";
			}
			if (i == 13)
			{
				cout << "|                          Would you like to try again?                          |\n";
			}
			if (i == 14)
			{
				cout << "|                                (1.Yes / 2. No)                                 |\n";
			}
			if ((i > -2 && i < 10) || i == 11 || (i > 14 && i < 27))
			{
				cout << "|                                                                                |\n";
			}
		}
		char input;
		input = '0';

		while (input != '1' && input != '2')
		{
			input = getch();
		}

		//continue option which reverts stats and map to what they were at the start of the level
		if (input == '1')
		{
			initializeAllowableArea();
			al.RevertStats();
			keyFound = false;
			return;
		}
		//quit option which ends the program
		if (input == '2')
		{
			QuitScrn();
		}
	}
}

//the quit screen
void Game::QuitScrn()
{
	ClearScrn();

	for (int i = -2; i < 28; i++)
	{
		if (i == -2 || i == 27)
		{
			cout << "|================================================================================|";
			if (i == -2)
			{
				cout << endl;
			}
		}
		if (i == 10)
		{
			cout << "|                                    Quit?                                       |\n";
		}
		if (i == 12)
		{
			cout << "|                                 Are you sure?                                  |\n";
		}
		if (i == 13)
		{
			cout << "|                                (1.Yes / 2. No)                                 |\n";
		}
		if ((i > -2 && i < 10) || i == 11 || (i > 14 && i < 27))
		{
			cout << "|                                                                                |\n";
		}
	}

	char input;
	input = '0';

	while (input != '1' && input != '2')
	{
		input = getch();
	}

	//continue option which reverts stats and map to what they were at the start of the level
	if (input == '1')
	{
		playing = false;
	}
	//quit option which ends the program
	if (input == '2')
	{
		playing = true;
	}
}

//the normal combat loop
bool Game::Combat(Player *p, Enemy *e)
{
	ClearScrn();
	string pAction;
	string eAttack;
	char n;

	//beginning of combat
	vector<string> vert;
	vert.push_back("|");
	cout << "======================================================================" << endl;

	//measure string length, output | then required number of spaces then text then spaces and |
	cout << vert[0];
	int spc = 68 - p->PrintCombatStats().length();
	int spc2 = spc / 2;
	if (spc % 2 == 0)
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << p->PrintCombatStats();
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}
	else
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << p->PrintCombatStats();
		for (int i = -1; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}

	cout << endl;

	cout << vert[0];
	spc = 68 - e->PrintEnemyStats().length();
	spc2 = spc / 2;
	if (spc % 2 == 0)
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << e->PrintEnemyStats();
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}
	else
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << e->PrintEnemyStats();
		for (int i = -1; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}
	cout << endl;
	e->PrintAscii();
	cout << vert[0] << "                                                                    " << vert[0] << endl;
	cout << vert[0] << "                                                                    " << vert[0] << endl;
	cout << vert[0] << "                     1. Attack  2. Eat  3. Flee                     " << vert[0] << endl;
	cout << "======================================================================" << endl;

	//enter loop for combat
	while (true)
	{
		n = '0';

		while (n != '1' && n != '2' && n != '3')
		{
			n = getch();
		}

		ClearScrn();
		cout << endl << endl << endl << endl;

		//option 1. Attack
		if (n == '1')
		{
			pAction = p->Attack(e);
			eAttack = e->Attack(p);
		}
		//option 2. Eat
		if (n == '2')
		{
			pAction = p->Eat();
			eAttack = e->Attack(p);
		}
		//option 3. Flee
		if (n == '3')
		{
			return true;
		}

		//checks to see if player or enemy is dead
		if (p->GetHealth() <= 0)
		{
			return false;
		}
		if (e->GetHealth() <= 0)
		{
			p->GainExperience(e);
			return true;
		}

		cout << "======================================================================" << endl;

		//measure string length, output | then required number of spaces then text then spaces and |
		cout << vert[0];
		int spc = 68 - p->PrintCombatStats().length();
		int spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << p->PrintCombatStats();
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << p->PrintCombatStats();
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}

		cout << endl;

		cout << vert[0];
		spc = 68 - e->PrintEnemyStats().length();
		spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << e->PrintEnemyStats();
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << e->PrintEnemyStats();
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		cout << endl;
		e->PrintAscii();

		//print pAction
		cout << vert[0];
		spc = 68 - pAction.length();
		spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << pAction;
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << pAction;
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		cout << endl;

		//print eAttack
		cout << vert[0];
		spc = 68 - eAttack.length();
		spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << eAttack;
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << eAttack;
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		cout << endl;

		cout << vert[0] << "                     1. Attack  2. Eat  3. Flee                     " << vert[0] << endl;
		cout << "======================================================================" << endl;
	}
}

//combat method where you cannot flee
bool Game::NFCombat(Player *p, Enemy *e)
{
	ClearScrn();
	string pAction;
	string eAttack;
	char n;

	//beginning of combat
	vector<string> vert;
	vert.push_back("|");
	cout << "======================================================================" << endl;

	//measure string length, output | then required number of spaces then text then spaces and |
	cout << vert[0];
	int spc = 68 - p->PrintCombatStats().length();
	int spc2 = spc / 2;
	if (spc % 2 == 0)
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << p->PrintCombatStats();
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}
	else
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << p->PrintCombatStats();
		for (int i = -1; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}

	cout << endl;

	cout << vert[0];
	spc = 68 - e->PrintEnemyStats().length();
	spc2 = spc / 2;
	if (spc % 2 == 0)
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << e->PrintEnemyStats();
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}
	else
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << e->PrintEnemyStats();
		for (int i = -1; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}
	cout << endl;
	e->PrintAscii();
	cout << vert[0] << "                                                                    " << vert[0] << endl;
	cout << vert[0] << "                                                                    " << vert[0] << endl;
	cout << vert[0] << "                        1. Attack  2. Eat                           " << vert[0] << endl;
	cout << "======================================================================" << endl;

	//enter loop for combat
	while (true)
	{
		n = '0';

		while (n != '1' && n != '2')
		{
			n = getch();
		}

		ClearScrn();
		cout << endl << endl << endl << endl;

		//option 1. Attack
		if (n == '1')
		{
			pAction = p->Attack(e);
			eAttack = e->Attack(p);
		}
		//option 2. Eat
		if (n == '2')
		{
			pAction = p->Eat();
			eAttack = e->Attack(p);
		}

		//checks to see if player or enemy is dead
		if (p->GetHealth() <= 0)
		{
			return false;
		}
		if (e->GetHealth() <= 0)
		{
			p->GainExperience(e);
			return true;
		}

		cout << "======================================================================" << endl;

		//measure string length, output | then required number of spaces then text then spaces and |
		cout << vert[0];
		int spc = 68 - p->PrintCombatStats().length();
		int spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << p->PrintCombatStats();
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << p->PrintCombatStats();
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}

		cout << endl;

		cout << vert[0];
		spc = 68 - e->PrintEnemyStats().length();
		spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << e->PrintEnemyStats();
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << e->PrintEnemyStats();
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		cout << endl;
		e->PrintAscii();

		//print pAction
		cout << vert[0];
		spc = 68 - pAction.length();
		spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << pAction;
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << pAction;
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		cout << endl;

		//print eAttack
		cout << vert[0];
		spc = 68 - eAttack.length();
		spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << eAttack;
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << eAttack;
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		cout << endl;

		cout << vert[0] << "                        1. Attack  2. Eat                           " << vert[0] << endl;
		cout << "======================================================================" << endl;
	}
}

//a special combat loop for the final boss that allows him to drink haterade
bool Game::FinalBossCombat(Player *p, Seminole *e)
{
	ClearScrn();
	string pAction;
	string eAction;
	char n;

	//beginning of combat
	vector<string> vert;
	vert.push_back("|");
	cout << "======================================================================" << endl;

	//measure string length, output | then required number of spaces then text then spaces and |
	cout << vert[0];
	int spc = 68 - p->PrintCombatStats().length();
	int spc2 = spc / 2;
	if (spc % 2 == 0)
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << p->PrintCombatStats();
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}
	else
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << p->PrintCombatStats();
		for (int i = -1; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}

	cout << endl;

	cout << vert[0];
	spc = 68 - e->PrintEnemyStats().length();
	spc2 = spc / 2;
	if (spc % 2 == 0)
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << e->PrintEnemyStats();
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}
	else
	{
		for (int i = 0; i < spc2; i++)
		{
			cout << " ";
		}
		cout << e->PrintEnemyStats();
		for (int i = -1; i < spc2; i++)
		{
			cout << " ";
		}
		cout << vert[0];
	}
	cout << endl;
	e->PrintAscii();
	cout << vert[0] << "                                                                    " << vert[0] << endl;
	cout << vert[0] << "                                                                    " << vert[0] << endl;
	cout << vert[0] << "                        1. Attack  2. Eat                           " << vert[0] << endl;
	cout << "======================================================================" << endl;

	//enter loop for combat
	while (true)
	{
		n = '0';

		while (n != '1' && n != '2')
		{
			n = getch();
		}

		ClearScrn();
		cout << endl << endl << endl << endl;

		//option 1. Attack
		if (n == '1')
		{
			pAction = p->Attack(e);
			eAction = e->Attack(p);
		}
		//option 2. Eat
		if (n == '2')
		{
			pAction = p->Eat();
			eAction = e->Attack(p);
		}

		//checks to see if player or enemy is dead
		if (p->GetHealth() <= 0)
		{
			return false;
		}
		if (e->GetHealth() <= 0)
		{
			if (e->GetHaterade() > 0)
			{
				e->DrinkHaterade();
				eAction = "The Nole King drank some Haterade and became stronger!";
			}
			else
			{
				p->GainExperience(e);
				return true;
			}
		}

		cout << "======================================================================" << endl;

		//measure string length, output | then required number of spaces then text then spaces and |
		cout << vert[0];
		int spc = 68 - p->PrintCombatStats().length();
		int spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << p->PrintCombatStats();
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << p->PrintCombatStats();
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}

		cout << endl;

		cout << vert[0];
		spc = 68 - e->PrintEnemyStats().length();
		spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << e->PrintEnemyStats();
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << e->PrintEnemyStats();
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		cout << endl;
		e->PrintAscii();

		//print pAction
		cout << vert[0];
		spc = 68 - pAction.length();
		spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << pAction;
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << pAction;
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		cout << endl;

		//print eAction
		cout << vert[0];
		spc = 68 - eAction.length();
		spc2 = spc / 2;
		if (spc % 2 == 0)
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << eAction;
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		else
		{
			for (int i = 0; i < spc2; i++)
			{
				cout << " ";
			}
			cout << eAction;
			for (int i = -1; i < spc2; i++)
			{
				cout << " ";
			}
			cout << vert[0];
		}
		cout << endl;

		cout << vert[0] << "                        1. Attack  2. Eat                           " << vert[0] << endl;
		cout << "======================================================================" << endl;
	}
}

/*
 * Destroy all of the objects on the heap
 */
void Game::Clean(Enemy** bosses, Enemy** type1, Enemy** type2)
{
	delete[] bosses;
	delete[] type1;
	delete[] type2;
}
