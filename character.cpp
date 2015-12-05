/*
 * character.cpp
 *
 *  Created on: Nov 23, 2015
 *      Author: Kyle
 */

#include "character.h"

//initializes each character with a random number seed
Character::Character()
{
	gen.seed(random_device()());
}

//returns the character's experience
int Character::GetExperience()
{
	return Experience;
}

//returns the character's max health
int Character::GetMaxHealth()
{
	return MaxHealth;
}

//returns the character's health
int Character::GetHealth()
{
	return Health;
}

//returns the character's level
int Character::GetLevel()
{
	return Level;
}

//returns the character's defense power
int Character::GetDefPower()
{
	return DefPower;
}

//returns the character's name
string Character::GetName()
{
	return Name;
}

//changes a character's health
void Character::ChangeHealth(int h)
{
	Health += h;
	if (Health < 0)
	{
		Health = 0;
	}
	if (Health > MaxHealth)
	{
		Health = MaxHealth;
	}
}

//determines how much damage an attack does and whether it misses
string Character::Attack(Character *c)
{
	uniform_int_distribution<mt19937::result_type> dist(1,10);
	int random = dist(gen);
	int damage;
	stringstream convert;
	string dam;
	string s;

	//attack possibilities for Albert
	if(Name=="Albert")
	{
		//attack misses
		if (random == 1)
		{
			damage = 0;
			s = Name + " missed!";
		}
		//critical hit
		if (random == 10)
		{
			if ((AttPower - c->GetDefPower()) <= 0)
			{
				damage = 2;
			}
			else
			{
				damage = 2 * (AttPower - c->GetDefPower());
			}
			convert << damage;
			dam=convert.str();
			s = "It's a critical hit! " + Name + " did " + dam + " damage.";
		}
		//normal attack
		if (random!=1&&random!=10)
		{
			if ((AttPower - c->GetDefPower()) <= 0)
			{
				damage = 1;
			}
			else
			{
				damage = 1 * (AttPower - c->GetDefPower());
			}
			convert << damage;
			dam=convert.str();
			s = Name + " did " + dam + " damage.";
		}
	}
	//attack possibilities for enemies
	else
	{
		//attack misses
		if (random == 7)
		{
			damage = 0;
			s = Name + " missed!";
		}
		//critical hit
		if (random == 4)
		{
			if ((AttPower - c->GetDefPower()) <= 0)
			{
				damage = 2;
			}
			else
			{
				damage = 2 * (AttPower - c->GetDefPower());
			}
			convert << damage;
			dam=convert.str();
			s = "It's a critical hit! " + Name + " did " + dam + " damage.";
		}
		//normal attack
		if (random!=7&&random!=4)
		{
			if ((AttPower - c->GetDefPower()) <= 0)
			{
				damage = 1;
			}
			else
			{
				damage = 1 * (AttPower - c->GetDefPower());
			}
			convert << damage;
			dam=convert.str();
			s = Name + " did " + dam + " damage.";
		}
	}
	c->ChangeHealth(-damage);
	return s;
}
//****************************************************

//constructs the initial player
Player::Player()
{
	Name = "Albert";
	Food = 5;
	Gatorade = 10;
	MaxStamina = 50;
	Stamina = 50;
	MaxHealth = 75;
	Health = 75;
	AttPower = 5;
	DefPower = 3;
	Level = 1;
	Experience = 0;
	LevelUpEXP = 100;
	xLocation = 10;
	yLocation = 7;
}

//changes the player's stamina
void Player::ChangeStamina(int s)
{
	Stamina += s;
	if (Stamina < 0)
	{
		Stamina = 0;
	}
	if (Stamina > MaxStamina)
	{
		Stamina = MaxStamina;
	}
}

//uses food to heal the player
string Player::Eat()
{
	if (Food == 0)
	{
		return "You're out of Food!";
	}
	else
	{
		Food--;
		ChangeHealth(20);
		return "Your health has been restored!";
	}
}

//uses Gatorade to restore the player's stamina
string Player::Drink()
{
	if (Gatorade == 0)
	{
		return "You're out of Gatorade!";
	}
	else
	{
		Gatorade--;
		ChangeStamina(15);
		return "Your stamina has been restored!";
	}
}

//levels the player up and changes his stats
void Player::LevelUp()
{
	Level += 1;
	MaxHealth += 5;
	Health = MaxHealth;
	Stamina = MaxStamina;
	AttPower += 1;
	DefPower += 1;
	LevelUpEXP += 50;
	Experience = 0;
}

//moves the player right and changes his stamina
void Player::MoveRight()
{
	if (Stamina > 0)
	{
		ChangeStamina(-1);
	}
	else
	{
		ChangeHealth(-2);
	}
	xLocation++;
}

//moves the player left and changes his stamina
void Player::MoveLeft()
{
	if (Stamina > 0)
	{
		ChangeStamina(-1);
	}
	else
	{
		ChangeHealth(-2);
	}
	xLocation--;
}

//moves the player up and changes his stamina
void Player::MoveUp()
{
	if (Stamina > 0)
	{
		ChangeStamina(-1);
	}
	else
	{
		ChangeHealth(-2);
	}
	yLocation--;
}

//moves the player down and changes his stamina
void Player::MoveDown()
{
	if (Stamina > 0)
	{
		ChangeStamina(-1);
	}
	else
	{
		ChangeHealth(-2);
	}
	yLocation++;
}

//changes the player's x and y location to the start of the next map
void Player::SetLocation(int x,int y)
{
	xLocation = x;
	yLocation = y;
}

//gives a defeated enemy's experience to the player
void Player::GainExperience(Character c)
{
	Experience += c.GetExperience();
}

//adds a random amount of Food to the player's inventory
void Player::FindFood()
{
	mt19937 gen;
	gen.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist(4,6);
	int random = dist(gen);
	Food += random;
}

//adds a random amount of Gatorade to the player's inventory
void Player::FindGatorade()
{
	mt19937 gen;
	gen.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist(4,6);
	int random = dist(gen);
	Gatorade += random;
}

//returns the player's amount of food
int Player::GetFood()
{
	return Food;
}

//returns the player's amount of Gatorade
int Player::GetGatorade()
{
	return Gatorade;
}

//returns the player's max stamina
int Player::GetMaxStamina()
{
	return MaxStamina;
}

//returns the player's stamina
int Player::GetStamina()
{
	return Stamina;
}

//returns the player's x location
int Player::GetxLocation()
{
	return xLocation;
}

//returns the player's y location
int Player::GetyLocation()
{
	return yLocation;
}

//returns the player's stats on the map
string Player::PrintMapStats()
{
	stringstream convert;
	convert << "Level[" << Level << "], EXP[" << Experience << "/" << LevelUpEXP << "], Health[" << Health << "/" << MaxHealth << "], Stamina[" << Stamina << "/" << MaxStamina << "], Food[" << Food << "], Gatorade[" << Gatorade << "]\n";
	string s=convert.str();
	return s;
}

//returns the player's stats during combat
string Player::PrintCombatStats()
{
	stringstream convert;
	convert << "Albert: Level[" << Level << "], Health[" << Health << "/"
			<< MaxHealth << "], Food[" << Food << "]\n";
	string s=convert.str();
	return s;
}

void Player::SaveStats()
{
	SavedStats.clear();
	SavedStats.push_back(Food);
	SavedStats.push_back(Gatorade);
	SavedStats.push_back(MaxStamina);
	SavedStats.push_back(Stamina);
	SavedStats.push_back(MaxHealth);
	SavedStats.push_back(Health);
	SavedStats.push_back(AttPower);
	SavedStats.push_back(DefPower);
	SavedStats.push_back(Level);
	SavedStats.push_back(Experience);
	SavedStats.push_back(LevelUpEXP);
	SavedStats.push_back(xLocation);
	SavedStats.push_back(yLocation);
}

void Player::RevertStats()
{
	Food=SavedStats.at(0);
	Gatorade=SavedStats.at(1);
	MaxStamina=SavedStats.at(2);
	Stamina=SavedStats.at(3);
	MaxHealth=SavedStats.at(4);
	Health=SavedStats.at(5);
	AttPower=SavedStats.at(6);
	DefPower=SavedStats.at(7);
	Level=SavedStats.at(8);
	Experience=SavedStats.at(9);
	LevelUpEXP=SavedStats.at(10);
	xLocation=SavedStats.at(11);
	yLocation=SavedStats.at(12);
}
//****************************************************

//randomizes an enemy's level
int Enemy::RandomizeLevel(int low, int high)
{
	uniform_int_distribution<mt19937::result_type> dist(low,high);
	int level = dist(gen);
	return level;
}

//returns the enemy's stats during combat
string Enemy::PrintEnemyStats()
{
	stringstream convert;
	convert << Name << ": Level[" << Level << "], Health[" << Health << "/"
			<< MaxHealth << "]\n";
	string s=convert.str();
	return s;
}

//prints out the ascii representation of the monster
void Enemy::PrintAscii()
{
	for(int i = 1; i < 25; i++)
	{
		cout << Ascii[i] << "\n";
	}
}

//creates a Bat of a random level between 1-2
Bat::Bat()
{
	Name = "Bat";
	Boss = false;
	Level = RandomizeLevel(1, 2);
	MaxHealth = 10 + 5 * Level;
	Health = MaxHealth;
	AttPower = 4 + Level;
	DefPower = 1 + Level;
	Experience = 10 * Level;
	Ascii.push_back("======================================================================");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                    _-.                       .-                    |");
	Ascii.push_back("|                 _..-'(                       )`-.._                |");
	Ascii.push_back("|              ./'. '||\\.       (\\_/)       .//||` .`\\.              |");
	Ascii.push_back("|           ./'.|'.'||||\\|..    )-.-(    ..|//||||`.`|.`\\.           |");
	Ascii.push_back("|       ./'..|'.|| |||||\\```````  \"  '''''''/||||| ||.`|..`\\.        |");
	Ascii.push_back("|     ./'.||'.|||| ||||||||||||.     .|||||||||||| ||||.`||.`\\.      |");
	Ascii.push_back("|    /'|||'.|||||| ||||||||||||{     }|||||||||||| ||||||.`|||`\\     |");
	Ascii.push_back("|   '.|||'.||||||| ||||||||||||{     }|||||||||||| |||||||.`|||.`    |");
	Ascii.push_back("|  '.||| ||||||||| |/'   ``\\||/`     '\\||/''   `\\| ||||||||| |||.`   |");
	Ascii.push_back("|  |/' \\./'     `\\./          |/\\   /\\|          \\./'     `\\./ `\\|   |");
	Ascii.push_back("|  V    V         V          }' `\\ /' `{          V         V    V   |");
	Ascii.push_back("|  `    `         `               U               '         '    '   |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("----------------------------------------------------------------------");
}

//creates a Scorpion of a random level between 3-4
Scorpion::Scorpion()
{
	Name = "Bat";
	Boss = false;
	Level = RandomizeLevel(3, 4);
	MaxHealth = 10 + 5 * Level;
	Health = MaxHealth;
	AttPower = 4 + Level;
	DefPower = 1 + Level;
	Experience = 10 * Level;
	Ascii.push_back("======================================================================");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                   ___ __                                           |");
	Ascii.push_back("|                 _{___{__}\\                                         |");
	Ascii.push_back("|                {_}      `\\)                                        |");
	Ascii.push_back("|               {_}         ;           _.-''''--.._                 |");
	Ascii.push_back("|               {_}                    //'.--.  \\___`.               |");
	Ascii.push_back("|                { }__,_.--~~~-~~~-~~-::.---. `-.\\  `.)              |");
	Ascii.push_back("|                 `-.{_{_{_{_{_{_{_{_//  -- 8;=- `                   |");
	Ascii.push_back("|                    `-:,_.:,_:,_:,.`\\._ ..'=- ,                     |");
	Ascii.push_back("|                        // // // //`-.`\\`   .-'/                    |");
	Ascii.push_back("|                       << << << <<    \\ `--'  /----)                |");
	Ascii.push_back("|                        ^  ^  ^  ^     `-.....--'''                 |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("----------------------------------------------------------------------");
}

//creates the Dragon boss
Dragon::Dragon()
{
	Name = "Midterm Dragon";
	Boss = true;
	Level = 5;
	MaxHealth = 80;
	Health = MaxHealth;
	AttPower = 12;
	DefPower = 6;
	Experience = 350;
	Ascii.push_back("======================================================================");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|           /|                                           |\\          |");
	Ascii.push_back("|          /||             ^               ^             ||\\         |");
	Ascii.push_back("|         / \\__           //               \\\\          __// \\        |");
	Ascii.push_back("|        /  |_  \\         | \\   /     \\   / |         /  _|  \\       |");
	Ascii.push_back("|       /  /  \\  \\         \\  \\/ \\---/ \\/  /         /  /     \\      |");
	Ascii.push_back("|      /  /    |  \\         \\  \\/\\   /\\/  /         /  |       \\     |");
	Ascii.push_back("|     /  /     \\   \\__       \\ ( 0\\ /0 ) /       __/   /        \\    |");
	Ascii.push_back("|    /  /       \\     \\___    \\ \\_/|\\_/ /    ___/     /\\         \\   |");
	Ascii.push_back("|   /  /         \\_)      \\___ \\/-\\|/-\\/ ___/      (_/\\ \\      `  \\  |");
	Ascii.push_back("|  /  /           /\\__)       \\/  oVo  \\/       (__/   ` \\      `  \\ |");
	Ascii.push_back("| /  /           /,   \\__)    (_/\\ _ /\\_)    (__/         `      \\  \\|");
	Ascii.push_back("|/  '           //       \\__)  (__V_V__)  (__/                    \\  |");
	Ascii.push_back("|  '  '        /'           \\   |{___}|   /         .              \\ |");
	Ascii.push_back("| '  /        /              \\/ |{___}| \\/\\          `              \\|");
	Ascii.push_back("|   /        '       .        \\/{_____}\\/  \\          \\    `         |");
	Ascii.push_back("|  /                ,         /{_______}\\   \\          \\    \\        |");
	Ascii.push_back("|                  /         /{___/_\\___}\\   `          \\    `       |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("----------------------------------------------------------------------");
}

//creates a Rhino of a random level between 4-5
Rhino::Rhino()
{
	Name = "Rhino";
	Boss = false;
	Level = RandomizeLevel(4, 5);
	MaxHealth = 20 + 5 * Level;
	Health = MaxHealth;
	AttPower = 4 + Level;
	DefPower = 4 + Level;
	Experience = 10 * Level;
	Ascii.push_back("======================================================================");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                             ,-.             __                     |");
	Ascii.push_back("|                           ,'   `---.___.---'  `.                   |");
	Ascii.push_back("|                         ,'   ,-                 `-._               |");
	Ascii.push_back("|                       ,'    /                       \\              |");
	Ascii.push_back("|                    ,\\/     /                        \\\\             |");
	Ascii.push_back("|                )`._)>)     |                         \\\\            |");
	Ascii.push_back("|                `>,'    _   \\                  /       |\\           |");
	Ascii.push_back("|                  )      \\   |   |            |        |\\\\          |");
	Ascii.push_back("|         .   ,   /        \\  |    `.          |        | ))         |");
	Ascii.push_back("|         \\`. \\`-'          )-|      `.        |        /((          |");
	Ascii.push_back("|          \\ `-`   o`     _/ ;\\ _     )`-.___.--\\      /  `'         |");
	Ascii.push_back("|           `._         ,'    \\`j`.__/        \\  `.    \\             |");
	Ascii.push_back("|             / ,    ,'       _)\\   /`        _) ( \\   /             |");
	Ascii.push_back("|             \\__   /        /___) (         /____\\_) (              |");
	Ascii.push_back("|               `--'           /____\\             /____\\             |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("----------------------------------------------------------------------");
}

//creates a Tiger of a random level between 6-7
Tiger::Tiger()
{
	Name = "Tiger";
	Boss = false;
	Level = RandomizeLevel(6, 7);
	MaxHealth = 10 + 5 * Level;
	Health = MaxHealth;
	AttPower = 5 + Level;
	DefPower = 3 + Level;
	Experience = 10 * Level;
	Ascii.push_back("======================================================================");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|         _                                                          |");
	Ascii.push_back("|        ( \\                ..-----..__                              |");
	Ascii.push_back("|         \\.'.        _.--'`  '   '  ' ```'-._                       |");
	Ascii.push_back("|          `. `'-..-'' `    '  '      . ;   ; `-'''-.,__/|/|         |");
	Ascii.push_back("|            `'-.;..-''`|'  `.  '.    ;     '  `    '   `'  `,       |");
	Ascii.push_back("|                       \\ '   .    ' .     '   ;   .`   . ' o \\      |");
	Ascii.push_back("|                        '.' . ' -.\\     .`   .`  .   .\\     `Y      |");
	Ascii.push_back("|                          '-.' .   |\\  '   ,    '    /'`--;;'       |");
	Ascii.push_back("|                            /\\   '.| '-._ /    ' _.-'               |");
	Ascii.push_back("|                            \\'\\  ' / (`-.'.'  .\"/                   |");
	Ascii.push_back("|                             \\ )` /   .'   .-'./                    |");
	Ascii.push_back("|                              '\\  \\).'  .-'--\"                      |");
	Ascii.push_back("|                                '. `,_'`                            |");
	Ascii.push_back("|                                  `.__)                             |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("----------------------------------------------------------------------");
}

//creates the Gorilla boss
Gorilla::Gorilla()
{
	Name = "Professor Bubbles";
	Boss = true;
	Level = 10;
	MaxHealth = 100;
	Health = MaxHealth;
	AttPower = 18;
	DefPower = 10;
	Experience = 700;
	Ascii.push_back("======================================================================");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                              ,.-\"\"\"-.,                             |");
	Ascii.push_back("|                             /   ===   \\                            |");
	Ascii.push_back("|                            /  =======  \\                           |");
	Ascii.push_back("|                         __|  (O)   (O)  |__                        |");
	Ascii.push_back("|                        / _|    .---.    |_ \\                       |");
	Ascii.push_back("|                       | /.----/ O O \\----.\\ |                      |");
	Ascii.push_back("|                        \\/     |     |     \\/                       |");
	Ascii.push_back("|                        |                   |                       |");
	Ascii.push_back("|                        |       _____       |                       |");
	Ascii.push_back("|                        _\\     /_____\\     /_                       |");
	Ascii.push_back("|                    ,.-\"  \"-.,_________,.-\"  \"-.,                   |");
	Ascii.push_back("|                   /          |       |          \\                  |");
	Ascii.push_back("|                  |           \\       /           |                 |");
	Ascii.push_back("|                  \\            |     |            /                 |");
	Ascii.push_back("|                ,/ |           \\     /           | \\,               |");
	Ascii.push_back("|              ,/   \\            |   |            /   \\,             |");
	Ascii.push_back("|             /      |           |   |           |      \\            |");
	Ascii.push_back("|            /        |          |---|          |        \\           |");
	Ascii.push_back("|           /\"-.,_,.-\"/\"-.,__,.-\"\\   /\"-.,__,.-\"\\\"-.,_,.-\"\\          |");
	Ascii.push_back("|          |         |            \\ /            |         |         |");
	Ascii.push_back("|           \\__|__|_/ \\__|__|__|__/ \\__|__|__|__/ \\_|__|__/          |");
	Ascii.push_back("----------------------------------------------------------------------");
}

//creates a Centaur of a random level between 9-10
Centaur::Centaur()
{
	Name = "Centaur";
	Boss = false;
	Level = RandomizeLevel(9, 10);
	MaxHealth = 10 + 5 * Level;
	Health = MaxHealth;
	AttPower = 7 + Level;
	DefPower = 3 + Level;
	Experience = 10 * Level;
	Ascii.push_back("======================================================================");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                    ___,       /\\                   |");
	Ascii.push_back("|                                   /,===      |  |                  |");
	Ascii.push_back("|                                ,==( \"|\"      |  |                  |");
	Ascii.push_back("|                               ,==='\\_-/       \\/                   |");
	Ascii.push_back("|                                ,---'  \\---.   ||                   |");
	Ascii.push_back("|                               (     - -    )  |:                   |");
	Ascii.push_back("|                               |  \\_. '  _./\\ ,'/\\                  |");
	Ascii.push_back("|                               |  )       / ,-||\\/                  |");
	Ascii.push_back("|                     ___       ( < \\     (\\___/||                   |");
	Ascii.push_back("|                    /   \\,----._\\ \\(   '  )    --                   |");
	Ascii.push_back("|                   (   /         \\|'',, ,'\\                         |");
	Ascii.push_back("|                   )   |          )\\   '   |                        |");
	Ascii.push_back("|                   (  (|     ,    \\_)      |                        |");
	Ascii.push_back("|                    )  )\\     \\-.__\\   |_, /                        |");
	Ascii.push_back("|                    ( (  \\    )  )  ]  |  (                         |");
	Ascii.push_back("|                     ) ) _) _/ _/   /, )) /                         |");
	Ascii.push_back("|                     (/  \\  \\ \\      \\ |\\ |                         |");
	Ascii.push_back("|                      )  _) \\__\\     ) | )(                         |");
	Ascii.push_back("|                         )_,\\ )_\\    )| <_\\                         |");
	Ascii.push_back("|                           )_\\      /_(  |_\\                        |");
	Ascii.push_back("|                                     )_\\                            |");
	Ascii.push_back("----------------------------------------------------------------------");
}

//creates a Griffin of a random level between 11-12
Griffin::Griffin()
{
	Name = "Griffin";
	Boss = false;
	Level = RandomizeLevel(11, 12);
	MaxHealth = 10 + 5 * Level;
	Health = MaxHealth;
	AttPower = 7 + Level;
	DefPower = 3 + Level;
	Experience = 10 * Level;
	Ascii.push_back("======================================================================");
	Ascii.push_back("|                      ///          ///                              |");
	Ascii.push_back("|                     ////         ////                              |");
	Ascii.push_back("|                     |////       /////                              |");
	Ascii.push_back("|                     |))//;     /)))//;                             |");
	Ascii.push_back("|                    /)))))/;   /)))))/;                             |");
	Ascii.push_back("|                .---`,))))/;  /)))))))/;                            |");
	Ascii.push_back("|            __--\\/o-  \\`))/; |)))))))/;                             |");
	Ascii.push_back("|           (----/    \\\\\\``;  |))))))/;                              |");
	Ascii.push_back("|              ~/-\\  \\\\\\\\\\``   \\))))))/;                             |");
	Ascii.push_back("|                  \\\\\\\\\\\\\\\\`    |)))))/;                             |");
	Ascii.push_back("|                  |\\\\\\\\\\\\\\\\___/))))))/;__-------.                   |");
	Ascii.push_back("|                  //////|  ////))))))/;           \\___,             |");
	Ascii.push_back("|                 |||||||\\   \\\\|||||;:              \\_. \\            |");
	Ascii.push_back("|                 |\\\\\\\\\\\\\\\\\\                        |  | |           |");
	Ascii.push_back("|                  \\\\\\\\\\\\\\                          |  | |           |");
	Ascii.push_back("|                   |\\\\\\\\               __|        /   / /           |");
	Ascii.push_back("|                   | \\\\__\\     \\___----  |       |   / /            |");
	Ascii.push_back("|                   |    / |     >     \\   \\      \\  / /             |");
	Ascii.push_back("|                   |   /  |    /       \\   \\      >/ /  ,,          |");
	Ascii.push_back("|                   |   |  |   |         |   |    // /  //,          |");
	Ascii.push_back("|                   |   |  |   |         |   |   /| |   |\\\\,         |");
	Ascii.push_back("|                _--'   _--'   |     _---_---'  |  \\ \\__/\\|/         |");
	Ascii.push_back("|               (-(-===(-(-(===/    (-(-=(-(-(==/   \\____/           |");
	Ascii.push_back("----------------------------------------------------------------------");
}

//creates the Seminole boss
Seminole::Seminole()
{
	Haterade = 1;
	Name = "Nole King";
	Boss = true;
	Level = 15;
	MaxHealth = 120;
	Health = MaxHealth;
	AttPower = 25;
	DefPower = 15;
	Experience = 0;
	Ascii.push_back("======================================================================");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("|                          / \\                                       |");
	Ascii.push_back("|                       -..\\|/.-                                     |");
	Ascii.push_back("|                       `-.\\|/.-'                                    |");
	Ascii.push_back("|                  '.--.`\\ \\|/ /'.--.'                               |");
	Ascii.push_back("|                  \\ o ' ======= ' o /                               |");
	Ascii.push_back("|                   \\_`-=========-'_/    ~   ~   ~                   |");
	Ascii.push_back("|                  .--./,'o.-.o`,\\.--.     ~   ~   ~                 |");
	Ascii.push_back("|                 \\_`- \\= (___) =/-'_/                               |");
	Ascii.push_back("|                  .--.`\\ -___- /'.--.                               |");
	Ascii.push_back("|                  \\.----\\_____/---./                                |");
	Ascii.push_back("|                  ~|/     FSU     \\|~                               |");
	Ascii.push_back("|                  ~|  |=========|  |~                               |");
	Ascii.push_back("|                  ~|  |  /)_    |  |~                               |");
	Ascii.push_back("|                  ~|__|=/| /====|__|~                               |");
	Ascii.push_back("|                   _||_//|/     |||_                                |");
	Ascii.push_back("|                  (  /(/_______/ _  \\                               |");
	Ascii.push_back("|                   \\\\\\;;;;;;;;;\\) )))                               |");
	Ascii.push_back("|                   // |-   _   -|                                   |");
	Ascii.push_back("|                      |___/ \\___|                                   |");
	Ascii.push_back("|                     (___)   (___)                                  |");
	Ascii.push_back("|                                                                    |");
	Ascii.push_back("----------------------------------------------------------------------");
}

//used to heal Seminole whenever health hits zero
void Seminole::DrinkHaterade()
{
	if (Haterade > 0)
	{
		Haterade--;
		Health += 50;
		AttPower += 4;
	}
}
