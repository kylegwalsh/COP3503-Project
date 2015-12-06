/*
 * game.cpp
 *
 *  Created on: Dec 5, 2015
 *      Author: Kyle
 */

#include "game.h"

Game::Game()
{
	ResizeScrn();
	StartScrn();
	map = Map();
	setHorizontalPadding();
}

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
	horizontalPadding = (70 - map.getColumns()) / 2;
}

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

	//creates and stores the first 2 bosses
	Enemy** bosses = new Enemy*[2];
	bosses[0] = new Dragon();
	bosses[1] = new Gorilla();

	//creates the final boss
	Seminole s;

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
	x = map.getColumns() / 2;
	y = map.getRows();

	al.SetLocation(x, y);

	update();

	uniform_int_distribution < mt19337::result_type > dist(1, 100);
	int random;

	while (!bossBeaten)
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

		switch (dir)
		{
		case 'w':
			//if possible, move up
			if (allow[y - 1][x] == 1)
			{
				al.MoveUp();
				moved = true;
			}
			break;
		case 's':
			//if possible, move down
			if (allow[y + 1][x] == 1)
			{
				al.MoveDown();
				moved = true;
			}
			break;
		case 'a':
			//if possible, move left
			if (allow[y][x - 1] == 1)
			{
				al.MoveLeft();
				moved = true;
			}
			break;
		case 'd':
			//if possible, move right
			if (allow[y][x + 1] == 1)
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
				if (random <= 40)
				{
					al.FindFood();
				}
				if (random>40 && random<=80)
				{
					alive = Combat(&al, type1[level - 1]);
				}
				if (random>80 && random<=90)
				{
					message = "You found a nice comfy little bed to sit your butt on! Gained health && stamina!";
					al.Sleep();
				}
				if (random > 90)
				{
					message = "You stubbed your toe! You lost 5 health!";
					al.ChangeHealth(-5);
				}
				allow[y][x] = 0;
			}
			//tower
			else if (place.compare("T") == 0)
			{
				alive = Combat(&al, type1[level - 1]);
				alive = Combat(&al, type2[level - 1]);
				if (alive)
				{
					keyFound = true;
				}
				allow[y][x] = 0;
			}
			else if (place.compare("G") == 0)
			{
				al.FindGatorade();
				message = "You found a Gatorade machine! Your Gatorade has increased!";
				allow[y][x] = 0;
			}
			//barracks
			else if (place.compare("M") == 0)
			{
				if (random <= 10)
				{
					message = "You stepped on a landmine";
					al.ChangeHealth(-25);
				}
				if (random > 10 && random <= 20)
				{
					message = "You found some good eats";
					al.FindFood();
					al.FindFood();
				}
				if (random > 20 && random <= 50)
				{
					alive = Combat(&al, type2[level - 1]);
					alive = Combat(&al, type2[level - 1]);
				}
				if (random > 50 && random <= 65)
				{
					alive = Combat(&al, type1[level - 1]);
					alive = Combat(&al, type2[level - 1]);
				}
				if (random > 65 && random <= 75)
				{
					message = "You got caught in a booby trap, and got a little banged up";
					al.ChangeHealth(-15);
				}
				if (random > 75 && random <= 97)
				{
					message = "You found one of Alberta's scales! Now you're motivated";
					al.ChangeStamina(10);
				}
				if (random > 97)
				{
					alive = Combat(&al, type2[level - 1]);
					alive = Combat(&al, type1[level - 1]);
					alive = Combat(&al, type2[level - 1]);
				}
			}
			//level boss
			else if (place.compare("B") == 0)
			{
				if (keyFound)
				{
					if(level<3)
					{
						bossBeaten = Combat(&al, bosses[level - 1]);
						alive = bossBeaten;
					}
					if(level==3)
					{
						bossBeaten = FinalBossCombat(&al, &s);
					}

					if (bossBeaten)
					{
						if (level == 3)
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
					message = "You must find the key before you can battle the boss!";
				}
			}
			else //if place=/
			{
				if (random <= 10)
				{
					//chooses randomly type 1 or type 2 enemy for level
					random = dist(al.gen);
					if (random <= 62)
					{
						alive = Combat(&al, type1[level - 1]);
					}
					else
					{
						alive = Combat(&al, type2[level - 1]);
					}
				}
			}
		}

		//check stats
		if (al.GetHealth() <= 0 || !alive)
		{
			GameOverScrn();
		}
		update();
	}
}

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

	for (int i = 0; i < map.getRows(); i++)
	{
		for (int p = 0; p < horizontalPadding; p++)
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
				std::cout << "X" << " ";
			}
		}
	}
}

void Game::update()
{
	int verticalPadding = (20 - map.getRows()) / 2;

	//prints screen
	cout << " ======================================================================= \n";
	cout << "| " << al.PrintMapStats() << std::string(69 - (al.PrintMapStats().size()), ' ') << "|\n";
	cout << "|-----------------------------------------------------------------------|\n";
	for (int i = 0; i < verticalPadding; i++)
	{
		cout << "|                                                                       |\n";
	}

	for (int i = 0; i < verticalPadding; i++)
	{
		cout << "|                                                                       |\n";
	}
	cout << "|-----------------------------------------------------------------------|\n";
	cout << "|  Messages: " << message << string(58 - message.size(), ' ') << "|\n";
	cout << "|                                                                       |\n";
	cout << "|  Controls: wasd - move		q - quit	other controls?                |\n";
	cout << "|                                                                       |\n";
	cout << " ======================================================================= \n";

}

//prints the outline of max screen for the player to resize their console
void ResizeScrn()
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
void StartScrn()
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
void Level1IntroScrn()
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
void Level2IntroScrn()
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
void Level3IntroScrn()
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
			cout << "|                                    Chapter 3                                    |\n";
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
void BeatGameScrn()
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

	exit(1);
}

//prints 35 blank lines to clear screen
void ClearScrn()
{
	for (int i = 0; i < 35; i++)
	{
		cout << endl;
	}
}

//prints the level up screen
void LevelUpScrn()
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
	ClearScrn();
	while (true)
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
		if (input == 1)
		{
			map.reset();
			al.RevertStats();
			keyFound = false;
			return;
		}
		//quit option which ends the program
		if (input == 2)
		{
			QuitScrn();
		}
	}
}

void QuitScrn()
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
		exit(1);
	}
	//quit option which ends the program
	if (input == '2')
	{
		break;
	}
}

bool Combat(Player *p, Enemy *e)
{
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
		if (p->GetHealth() == 0)
		{
			return false;
		}
		if (e->GetHealth() == 0)
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

//a special combat loop for the final boss that allows him to drink haterade
bool FinalBossCombat(Player *p, Seminole *e)
{
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
			eAction = e->Attack(p);
		}
		//option 2. Eat
		if (n == '2')
		{
			pAction = p->Eat();
			eAction = e->Attack(p);
		}
		//option 3. Flee
		if (n == '3')
		{
			return true;
		}

		//checks to see if player or enemy is dead
		if (p->GetHealth() == 0)
		{
			return false;
		}
		if (e->GetHealth() == 0)
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

		//print eAttack
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

		cout << vert[0] << "                     1. Attack  2. Eat  3. Flee                     " << vert[0] << endl;
		cout << "======================================================================" << endl;
	}
}

/*
* Destroy all of the objects on the heap
*/
void Game::Clean()
{
	delete bosses[0];
	delete bosses[1];
	delete bosses;
	for (int i=0; i<3; i++)
	{
		delete type1[i];
		delete type2[i];
	}
	delete type1;
	delete type2;
}
