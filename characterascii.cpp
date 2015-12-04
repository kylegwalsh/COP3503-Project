/*
 * character.cpp
 *
 *  Created on: Nov 23, 2015
 *      Author: Kyle
 */

#include "character.h"

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
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 10);
	int random = dis(gen);
	int damage;
	string dam;
	ostringstream convert;
	string s;

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
		dam = convert.str();
		s = "It's a critical hit! " + Name + " did " + dam + " damage.";
	}
	//normal attack
	if (random > 1 && random < 10)
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
		dam = convert.str();
		s = Name + " did " + dam + " damage.";
	}
	c->ChangeHealth(-damage);
	return s;
}
//*************************************

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
	xLocation = 1;
	yLocation = 1;
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

//changes the player's x and y location to the start of the second map
void Player::MoveToSecondMap()
{
	xLocation = 1;
	yLocation = 1;
}

//changes the player's x and y location to the start of the third map
void Player::MoveToThirdMap()
{
	xLocation = 1;
	yLocation = 1;
}

//gives a defeated enemy's experience to the player
void Player::GainExperience(Character c)
{
	Experience += c.GetExperience();
}

//adds a random amount of Food to the player's inventory
void Player::FindFood()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 4);
	int random = dis(gen);
	Food += random;
}

//adds a random amount of Gatorade to the player's inventory
void Player::FindGatorade()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 4);
	int random = dis(gen);
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

//prints out the player's stats on the map
void Player::PrintMapStats()
{
	cout << "Level[" << Level << "], EXP[" << Experience << "/" << LevelUpEXP
			<< "], Health[" << Health << "/" << MaxHealth << "], Stamina["
			<< Stamina << "/" << MaxStamina << "], Food[" << Food
			<< "], Gatorade[" << Gatorade << "]\n";
}

//prints out the player's stats during combat
void Player::PrintCombatStats()
{
	cout << "Albert: " << "Level[" << Level << "], Health[" << Health << "/"
			<< MaxHealth << "], Food[" << Food << "]\n";
}

void SetSaveStats() const
{

}
//*************************************

//randomizes an enemy's level
int Enemy::RandomizeLevel(int low, int high)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(low, high);
	int level = dis(gen);
	return level;
}

//prints out the enemy's stats during combat
void Enemy::PrintEnemyStats()
{
	cout << Name << ": " << "Level[" << Level << "], Health[" << Health << "/"
			<< MaxHealth << "]\n";
}

//prints out the ascii representation of the monster
void Enemy::PrintAscii()
{
	for(int i = 0; i < 25; i++)
	{
		cout << asciivector[i] << "\n";
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
	asciivector.push_back("======================================================================"); 
	asciivector.push_back("|                                                                    |"); 
	asciivector.push_back("|                                                                    |"); 	
	asciivector.push_back("|                    _-.                       .-                    |");
	asciivector.push_back("|                 _..-'(                       )`-.._                |");
	asciivector.push_back("|              ./'. '||\\.       (\\_/)       .//||` .`\\.              |");
	asciivector.push_back("|           ./'.|'.'||||\\|..    )-.-(    ..|//||||`.`|.`\\.           |");
	asciivector.push_back("|       ./'..|'.|| |||||\\```````  \"  '''''''/||||| ||.`|..`\\.        |");
	asciivector.push_back("|     ./'.||'.|||| ||||||||||||.     .|||||||||||| ||||.`||.`\\.      |");
	asciivector.push_back("|    /'|||'.|||||| ||||||||||||{     }|||||||||||| ||||||.`|||`\\     |");
	asciivector.push_back("|   '.|||'.||||||| ||||||||||||{     }|||||||||||| |||||||.`|||.`    |");
	asciivector.push_back("|  '.||| ||||||||| |/'   ``\\||/`     '\\||/''   `\\| ||||||||| |||.`   |");
	asciivector.push_back("|  |/' \\./'     `\\./          |/\\   /\\|          \\./'     `\\./ `\\|   |");
	asciivector.push_back("|  V    V         V          }' `\\ /' `{          V         V    V   |");
	asciivector.push_back("|  `    `         `               U               '         '    '   |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("----------------------------------------------------------------------");


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
	asciivector.push_back("======================================================================"); 
	asciivector.push_back("|                                                                    |"); 
	asciivector.push_back("|                                                                    |"); 	
	asciivector.push_back("|                   ___ __                                           |");
	asciivector.push_back("|                 _{___{__}\\                                         |");
	asciivector.push_back("|                {_}      `\\)                                        |");
	asciivector.push_back("|               {_}         ;           _.-''''--.._                 |");
	asciivector.push_back("|               {_}                    //'.--.  \\___`.               |");
	asciivector.push_back("|                { }__,_.--~~~-~~~-~~-::.---. `-.\\  `.)              |");
	asciivector.push_back("|                 `-.{_{_{_{_{_{_{_{_//  -- 8;=- `                   |");
	asciivector.push_back("|                    `-:,_.:,_:,_:,.`\\._ ..'=- ,                     |");
	asciivector.push_back("|                        // // // //`-.`\\`   .-'/                    |");
	asciivector.push_back("|                       << << << <<    \\ `--'  /----)                |");	
	asciivector.push_back("|                        ^  ^  ^  ^     `-.....--'''                 |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("----------------------------------------------------------------------");

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
	asciivector.push_back("======================================================================"); 
	asciivector.push_back("|                                                                    |"); 
	asciivector.push_back("|                                                                    |"); 	
	asciivector.push_back("|           /|                                           |\\          |");
	asciivector.push_back("|          /||             ^               ^             ||\\         |");
	asciivector.push_back("|         / \\__           //               \\\\          __// \\        |");
	asciivector.push_back("|        /  |_  \\         | \\   /     \\   / |         /  _|  \\       |");
	asciivector.push_back("|       /  /  \\  \\         \\  \\/ \\---/ \\/  /         /  /     \\      |");
	asciivector.push_back("|      /  /    |  \\         \\  \\/\\   /\\/  /         /  |       \\     |");
	asciivector.push_back("|     /  /     \\   \\__       \\ ( 0\\ /0 ) /       __/   /        \\    |");
	asciivector.push_back("|    /  /       \\     \\___    \\ \\_/|\\_/ /    ___/     /\\         \\   |");
	asciivector.push_back("|   /  /         \\_)      \\___ \\/-\\|/-\\/ ___/      (_/\\ \\      `  \\  |");
	asciivector.push_back("|  /  /           /\\__)       \\/  oVo  \\/       (__/   ` \\      `  \\ |");	
	asciivector.push_back("| /  /           /,   \\__)    (_/\\ _ /\\_)    (__/         `      \\  \\|");
	asciivector.push_back("|/  '           //       \\__)  (__V_V__)  (__/                    \\  |");
	asciivector.push_back("|  '  '        /'           \\   |{___}|   /         .              \\ |");
	asciivector.push_back("| '  /        /              \\/ |{___}| \\/\\          `              \\|");
	asciivector.push_back("|   /        '       .        \\/{_____}\\/  \\          \\    `         |");
	asciivector.push_back("|  /                ,         /{_______}\\   \\          \\    \\        |");
	asciivector.push_back("|                  /         /{___/_\\___}\\   `          \\    `       |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("----------------------------------------------------------------------");

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
	asciivector.push_back("======================================================================"); 
	asciivector.push_back("|                                                                    |"); 
	asciivector.push_back("|                                                                    |"); 	
	asciivector.push_back("|                             ,-.             __                     |");
	asciivector.push_back("|                           ,'   `---.___.---'  `.                   |");
	asciivector.push_back("|                         ,'   ,-                 `-._               |");
	asciivector.push_back("|                       ,'    /                       \\              |");
	asciivector.push_back("|                    ,\\/     /                        \\\\             |");
	asciivector.push_back("|                )`._)>)     |                         \\\\            |");
	asciivector.push_back("|                `>,'    _   \\                  /       |\\           |");
	asciivector.push_back("|                  )      \\   |   |            |        |\\\\          |");
	asciivector.push_back("|         .   ,   /        \\  |    `.          |        | ))         |");
	asciivector.push_back("|         \\`. \\`-'          )-|      `.        |        /((          |");	
	asciivector.push_back("|          \\ `-`   o`     _/ ;\\ _     )`-.___.--\\      /  `'         |");
	asciivector.push_back("|           `._         ,'    \\`j`.__/        \\  `.    \\             |");
	asciivector.push_back("|             / ,    ,'       _)\\   /`        _) ( \\   /             |");
	asciivector.push_back("|             \\__   /        /___) (         /____\\_) (              |");
	asciivector.push_back("|               `--'           /____\\             /____\\             |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("----------------------------------------------------------------------");

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
	asciivector.push_back("======================================================================"); 
	asciivector.push_back("|                                                                    |"); 
	asciivector.push_back("|                                                                    |"); 	
	asciivector.push_back("|         _                                                          |");
	asciivector.push_back("|        ( \\                ..-----..__                              |");
	asciivector.push_back("|         \\.'.        _.--'`  '   '  ' ```'-._                       |");
	asciivector.push_back("|          `. `'-..-'' `    '  '      . ;   ; `-'''-.,__/|/|         |");
	asciivector.push_back("|            `'-.;..-''`|'  `.  '.    ;     '  `    '   `'  `,       |");
	asciivector.push_back("|                       \\ '   .    ' .     '   ;   .`   . ' o \\      |");
	asciivector.push_back("|                        '.' . ' -.\\     .`   .`  .   .\\     `Y      |");
	asciivector.push_back("|                          '-.' .   |\\  '   ,    '    /'`--;;'       |");
	asciivector.push_back("|                            /\\   '.| '-._ /    ' _.-'               |");
	asciivector.push_back("|                            \\'\\  ' / (`-.'.'  .\"/                   |");	
	asciivector.push_back("|                             \\ )` /   .'   .-'./                    |");
	asciivector.push_back("|                              '\\  \\).'  .-'--\"                      |");
	asciivector.push_back("|                                '. `,_'`                            |");
	asciivector.push_back("|                                  `.__)                             |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("----------------------------------------------------------------------");

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
	asciivector.push_back("======================================================================"); 
	asciivector.push_back("|                                                                    |"); 
	asciivector.push_back("|                                                                    |"); 	
	asciivector.push_back("|                              ,.-\"\"\"-.,                             |");
	asciivector.push_back("|                             /   ===   \\                            |");
	asciivector.push_back("|                            /  =======  \\                           |");
	asciivector.push_back("|                         __|  (O)   (O)  |__                        |");
	asciivector.push_back("|                        / _|    .---.    |_ \\                       |");
	asciivector.push_back("|                       | /.----/ O O \\----.\\ |                      |");
	asciivector.push_back("|                        \\/     |     |     \\/                       |");
	asciivector.push_back("|                        |                   |                       |");
	asciivector.push_back("|                        |       _____       |                       |");
	asciivector.push_back("|                        _\\     /_____\\     /_                       |");	
	asciivector.push_back("|                    ,.-\"  \"-.,_________,.-\"  \"-.,                   |");
	asciivector.push_back("|                   /          |       |          \\                  |");
	asciivector.push_back("|                  |           \\       /           |                 |");
	asciivector.push_back("|                  \\            |     |            /                 |");
	asciivector.push_back("|                ,/ |           \\     /           | \\,               |");
	asciivector.push_back("|              ,/   \\            |   |            /   \\,             |");
	asciivector.push_back("|             /      |           |   |           |      \\            |");
	asciivector.push_back("|            /        |          |---|          |        \\           |");
	asciivector.push_back("|           /\"-.,_,.-\"/\"-.,__,.-\"\\   /\"-.,__,.-\"\\\"-.,_,.-\"\\          |");
	asciivector.push_back("|          |         |            \\ /            |         |         |");
	asciivector.push_back("|           \\__|__|_/ \\__|__|__|__/ \\__|__|__|__/ \\_|__|__/          |");
	asciivector.push_back("----------------------------------------------------------------------");

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
	asciivector.push_back("======================================================================"); 
	asciivector.push_back("|                                                                    |"); 
	asciivector.push_back("|                                                                    |"); 
	asciivector.push_back("|                                    ___,       /\\                   |");
	asciivector.push_back("|                                   /,===      |  |                  |");
	asciivector.push_back("|                                ,==( \"|\"      |  |                  |");
	asciivector.push_back("|                               ,==='\\_-/       \\/                   |");
	asciivector.push_back("|                                ,---'  \\---.   ||                   |");
	asciivector.push_back("|                               (     - -    )  |:                   |");
	asciivector.push_back("|                               |  \\_. '  _./\\ ,'/\\                  |");
	asciivector.push_back("|                               |  )       / ,-||\\/                  |");
	asciivector.push_back("|                     ___       ( < \\     (\\___/||                   |");
	asciivector.push_back("|                    /   \\,----._\\ \\(   '  )    --                   |");	
	asciivector.push_back("|                   (   /         \\|'',, ,'\\                         |");
	asciivector.push_back("|                   )   |          )\\   '   |                        |");
	asciivector.push_back("|                   (  (|     ,    \\_)      |                        |");
	asciivector.push_back("|                    )  )\\     \\-.__\\   |_, /                        |");
	asciivector.push_back("|                    ( (  \\    )  )  ]  |  (                         |");
	asciivector.push_back("|                     ) ) _) _/ _/   /, )) /                         |");
	asciivector.push_back("|                     (/  \\  \\ \\      \\ |\\ |                         |");
	asciivector.push_back("|                      )  _) \\__\\     ) | )(                         |");
	asciivector.push_back("|                         )_,\\ )_\\    )| <_\\                         |");
	asciivector.push_back("|                           )_\\      /_(  |_\\                        |");
	asciivector.push_back("|                                     )_\\                            |");
	asciivector.push_back("----------------------------------------------------------------------");

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
	asciivector.push_back("======================================================================"); 
	asciivector.push_back("|                      ///          ///                              |");
	asciivector.push_back("|                     ////         ////                              |");
	asciivector.push_back("|                     |////       /////                              |");
	asciivector.push_back("|                     |))//;     /)))//;                             |");
	asciivector.push_back("|                    /)))))/;   /)))))/;                             |");
	asciivector.push_back("|                .---`,))))/;  /)))))))/;                            |");
	asciivector.push_back("|            __--\\/o-  \\`))/; |)))))))/;                             |");
	asciivector.push_back("|           (----/    \\\\\\``;  |))))))/;                              |");
	asciivector.push_back("|              ~/-\\  \\\\\\\\\\``   \\))))))/;                             |");	
	asciivector.push_back("|                  \\\\\\\\\\\\\\\\`    |)))))/;                             |");
	asciivector.push_back("|                  |\\\\\\\\\\\\\\\\___/))))))/;__-------.                   |");
	asciivector.push_back("|                  //////|  ////))))))/;           \\___,             |");
	asciivector.push_back("|                 |||||||\\   \\\\|||||;:              \\_. \\            |");
	asciivector.push_back("|                 |\\\\\\\\\\\\\\\\\\                        |  | |           |");
	asciivector.push_back("|                  \\\\\\\\\\\\\\                          |  | |           |");
	asciivector.push_back("|                   |\\\\\\\\               __|        /   / /           |");
	asciivector.push_back("|                   | \\\\__\\     \\___----  |       |   / /            |");
	asciivector.push_back("|                   |    / |     >     \\   \\      \\  / /             |");
	asciivector.push_back("|                   |   /  |    /       \\   \\      >/ /  ,,          |");
	asciivector.push_back("|                   |   |  |   |         |   |    // /  //,          |");
	asciivector.push_back("|                   |   |  |   |         |   |   /| |   |\\\\,         |");	
	asciivector.push_back("|                _--'   _--'   |     _---_---'  |  \\ \\__/\\|/         |");
	asciivector.push_back("|               (-(-===(-(-(===/    (-(-=(-(-(==/   \\____/           |");				
	asciivector.push_back("----------------------------------------------------------------------");

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
	asciivector.push_back("======================================================================"); 
	asciivector.push_back("|                                                                    |"); 
	asciivector.push_back("|                                                                    |"); 	
	asciivector.push_back("|                          / \\                                       |");
	asciivector.push_back("|                       -..\\|/.-                                     |");
	asciivector.push_back("|                       `-.\\|/.-'                                    |");
	asciivector.push_back("|                  '.--.`\\ \\|/ /'.--.'                               |");
	asciivector.push_back("|                  \\ o ' ======= ' o /                               |");
	asciivector.push_back("|                   \\_`-=========-'_/    ~   ~   ~                   |");
	asciivector.push_back("|                  .--./,'o.-.o`,\\.--.     ~   ~   ~                 |");
	asciivector.push_back("|                 \\_`- \\= (___) =/-'_/                               |");
	asciivector.push_back("|                  .--.`\\ -___- /'.--.                               |");
	asciivector.push_back("|                  \\.----\\_____/---./                                |");	
	asciivector.push_back("|                  ~|/     FSU     \\|~                               |");
	asciivector.push_back("|                  ~|  |=========|  |~                               |");
	asciivector.push_back("|                  ~|  |  /)_    |  |~                               |");
	asciivector.push_back("|                  ~|__|=/| /====|__|~                               |");
	asciivector.push_back("|                   _||_//|/     |||_                                |");
	asciivector.push_back("|                  (  /(/_______/ _  \\                               |");
	asciivector.push_back("|                   \\\\\\;;;;;;;;;\\) )))                               |");
	asciivector.push_back("|                   // |-   _   -|                                   |");
	asciivector.push_back("|                      |___/ \\___|                                   |");
	asciivector.push_back("|                     (___)   (___)                                  |");
	asciivector.push_back("|                                                                    |");
	asciivector.push_back("----------------------------------------------------------------------");

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

//**xLocations and yLocations need int values based on maps**//
//**Randomization needs to be checked**//
//**Enemy AttPower/Defense might need to be adjusted & Attack method isn't quite working**//

//example combat loop
int main()
{
	Player p;
	Bat e;
	string pAction;
	string eAttack;
	int n;

	p.PrintCombatStats();
	e.PrintEnemyStats();
	e.PrintAscii();
	cout << "1. Attack  2. Eat  3. Flee" << endl;

	while(true)
	{
		cin >> n;

		//checks for good input
		while(cin.fail() || n<1 || n>3)
		{
			while(cin.fail())
			{
				cout << "Error! Number not entered\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> n;
			}
			while(n<1 || n>3)
			{
				cout << "Error! Number is not one of the options\n";
				cin >> n;
				if(cin.fail())
				{
					break;
				}
			}
		};

		//clears previous screen
		cout << endl << endl << endl << endl << endl << endl << endl << endl;

		//option 1. Attack
		if(n==1)
		{
			pAction=p.Attack(&e);
			eAttack=e.Attack(&p);
		}
		//option 2. Eat
		if(n==2)
		{
			pAction=p.Eat();
			eAttack=e.Attack(&p);
		}
		//option 3. Flee
		if(n==3)
		{
			break;
		}

		//checks to see if player or enemy is dead
		if(p.GetHealth()==0)
		{
			return false;
		}
		if(e.GetHealth()==0)
		{
			p.GainExperience(e);
			return true;
		}

		p.PrintCombatStats();
		e.PrintEnemyStats();
		e.PrintAscii();
		cout << "1. Attack  2. Eat  3. Flee" << endl;

		cout << pAction << endl;
		cout << eAttack << endl;
	}
}