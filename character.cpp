/*
 * character.cpp
 *
 *  Created on: Nov 23, 2015
 *      Author: Kyle
 */

#include "character.h"

//returns the character's experience
int Character::GetExperience(){
	return Experience;
}

//returns the character's max health
int Character::GetMaxHealth(){
	return MaxHealth;
}

//returns the character's health
int Character::GetHealth(){
	return Health;
}

//returns the character's level
int Character::GetLevel(){
	return Level;
}

//returns the character's defense power
int Character::GetDefPower(){
	return DefPower;
}

//returns the character's name
string Character::GetName(){
	return Name;
}

//changes a character's health
void Character::ChangeHealth(int h){
	Health+=h;
	if(Health<0){
		Health=0;
	}
	if(Health>MaxHealth){
		Health=MaxHealth;
	}
}

//determines how much damage an attack does and whether it misses
string Character::Attack(Character c){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1,10);
	int random=dis(gen);
	int damage;
	char dam;
	string s;

	//attack misses
	if(random==1){
		damage=0;
		s=Name + " missed!";
	}
	//critical hit
	if(random==10){
		if((AttPower-c.GetDefPower())<=0){
			damage=2;
		}
		else{
			damage=2*(AttPower-c.GetDefPower());
		}
		dam = damage+'0';
		s="It's a critical hit! " + Name + " did " + dam + " damage.";
	}
	//normal attack
	if(random>1&&random<10){
		if((AttPower-c.GetDefPower())<=0){
			damage=1;
		}
		else{
			damage=1*(AttPower-c.GetDefPower());
		}
		dam = damage+'0';
		s=Name + " did " + dam + " damage.";
	}
	c.ChangeHealth(-damage);
	return s;
}
//*************************************

//constructs the initial player
Player::Player(){
	Name="Albert";
	Food=5;
	Gatorade=10;
	MaxStamina=50;
	Stamina=50;
	MaxHealth=75;
	Health=75;
	AttPower=5;
	DefPower=3;
	Level=1;
	Experience=0;
	LevelUpEXP=100;
	xLocation=1;
	yLocation=1;
	PlayerSymbol='@';
}

//changes the player's stamina
void Player::ChangeStamina(int s){
	Stamina+=s;
	if(Stamina<0){
		Stamina=0;
	}
	if(Stamina>MaxStamina){
		Stamina=MaxStamina;
	}
}

//uses food to heal the player
void Player::Eat(){
	if(Food==0){
		cout << "You're out of Food!";
	}
	else{
		Food--;
		ChangeHealth(20);
	}
}

//uses Gatorade to restore the player's stamina
void Player::Drink(){
	if(Gatorade==0){
		cout << "You're out of Gatorade!";
	}
	else{
		Gatorade--;
		ChangeStamina(15);
	}
}

//levels the player up and changes his stats
void Player::LevelUp(){
	Level+=1;
	MaxHealth+=5;
	Health=MaxHealth;
	Stamina=MaxStamina;
	AttPower+=1;
	DefPower+=1;
	LevelUpEXP+=50;
	Experience=0;
}

//moves the player right and changes his stamina
void Player::MoveRight(){
	if(Stamina>0){
		ChangeStamina(-1);
	}
	else{
		ChangeHealth(-2);
	}
	xLocation++;
}

//moves the player left and changes his stamina
void Player::MoveLeft(){
	if(Stamina>0){
		ChangeStamina(-1);
	}
	else{
		ChangeHealth(-2);
	}
	xLocation--;
}

//moves the player up and changes his stamina
void Player::MoveUp(){
	if(Stamina>0){
		ChangeStamina(-1);
	}
	else{
		ChangeHealth(-2);
	}
	yLocation--;
}

//moves the player down and changes his stamina
void Player::MoveDown(){
	if(Stamina>0){
		ChangeStamina(-1);
	}
	else{
		ChangeHealth(-2);
	}
	yLocation++;
}

//changes the player's x and y location to the start of the second map
void Player::MoveToSecondMap(){
	xLocation=1;
	yLocation=1;
}

//changes the player's x and y location to the start of the third map
void Player::MoveToThirdMap(){
	xLocation=1;
	yLocation=1;
}

//gives a defeated enemy's experience to the player
void Player::GainExperience(Character c){
	Experience+=c.GetExperience();
}

//adds a random amount of Food to the player's inventory
void Player::FindFood(){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1,4);
	int random=dis(gen);
	Food+=random;
}

//adds a random amount of Gatorade to the player's inventory
void Player::FindGatorade(){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1,4);
	int random=dis(gen);
	Gatorade+=random;
}

//returns the player's amount of food
int Player::GetFood(){
	return Food;
}

//returns the player's amount of Gatorade
int Player::GetGatorade(){
	return Gatorade;
}

//returns the player's max stamina
int Player::GetMaxStamina(){
	return MaxStamina;
}

//returns the player's stamina
int Player::GetStamina(){
	return Stamina;
}

//returns the player's x location
int Player::GetxLocation(){
	return xLocation;
}

//returns the player's y location
int Player::GetyLocation(){
	return yLocation;
}

//prints out the player's stats on the map
void Player::PrintMapStats(){
	cout << "Level[" << Level << "], EXP[" << Experience << "/" << LevelUpEXP << "], Health[" << Health << "/" << MaxHealth << "], Stamina[" << Stamina << "/" << MaxStamina << "], Food[" << Food << "], Gatorade[" << Gatorade << "]\n";
}

//prints out the player's stats during combat
void Player::PrintCombatStats(){
	cout << "Albert: " << "Level[" << Level << "], Health[" << Health << "/" << MaxHealth << "], Food[" << Food << "]\n";
}
//*************************************

//randomizes an enemy's level
int Enemy::RandomizeLevel(int low, int high){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(low,high);
	int level=dis(gen);
	return level;
}

//prints out the enemy's stats during combat
void Enemy::PrintEnemyStats(){
	cout << Name << ": " << "Level[" << Level << "], Health[" << Health << "/" << MaxHealth << "]\n";
}

//prints out the ascii representation of the monster
void Enemy::PrintAscii(){
	cout << Ascii;
}

//creates a Bat of a random level between 1-2
Bat::Bat(){
	Name="Bat";
	Boss=false;
	Level=RandomizeLevel(1,2);
	MaxHealth=10+5*Level;
	Health=MaxHealth;
	AttPower=4+Level;
	DefPower=1+Level;
	Experience=10*Level;
	Ascii="                  _-.                       .-_\n               _..-\'(                       )`-.._\n            ./\'. \'||\\\\.       (\\_/)       .//||` .`\\.\n         ./\'.|\'.\'||||\\\\|..    )-.-(    ..|//||||`.`|.`\\.\n      ./\'..|\'.|| |||||\\```````  \"  \'\'\'\'\'\'\'/||||| ||.`|..`\\.\n    ./\'.||\'.|||| ||||||||||||.     .|||||||||||| ||||.`||.`\\.\n   /\'|||\'.|||||| ||||||||||||{     }|||||||||||| ||||||.`|||`\\\n  \'.|||\'.||||||| ||||||||||||{     }|||||||||||| |||||||.`|||.`\n \'.||| ||||||||| |/\'   ``\\||/`     \'\\||/\'\'   `\\| ||||||||| |||.`\n |/\' \\./\'     `\\./          |/\\   /\\|          \\./\'     `\\./ `\\|\n V    V         V          }\' `\\ /\' `{          V         V    V\n `    `         `               U               \'         \'    \'\n";
}

//creates a Scorpion of a random level between 3-4
Scorpion::Scorpion(){
	Name="Bat";
	Boss=false;
	Level=RandomizeLevel(3,4);
	MaxHealth=10+5*Level;
	Health=MaxHealth;
	AttPower=4+Level;
	DefPower=1+Level;
	Experience=10*Level;
	Ascii="     ___ __ \n   _{___{__}\\\n  {_}      `\\)            \n {_}         ;           _.-\'\'\'\'--.._\n {_}                    //\'.--.  \\___`.\n  { }__,_.--~~~-~~~-~~-::.---. `-.\\  `.)\n   `-.{_{_{_{_{_{_{_{_//  -- 8;=- `\n      `-:,_.:,_:,_:,.`\\\\._ ..\'=- , \n          // // // //`-.`\\`   .-\'/\n         << << << <<    \\ `--\'  /----)\n          ^  ^  ^  ^     `-.....--\'\'\'\n";
}

//creates the Dragon boss
Dragon::Dragon(){
	Name="Midterm Dragon";
	Boss=true;
	Level=5;
	MaxHealth=80;
	Health=MaxHealth;
	AttPower=12;
	DefPower=6;
	Experience=350;
	Ascii="           /|                                           |\\\n          /||             ^               ^             ||\\\n         / \\\\__          //               \\\\          __// \\\n        /  |_  \\         | \\   /     \\   / |         /  _|  \\\n       /  /  \\  \\         \\  \\/ \\---/ \\/  /         /  /     \\\n      /  /    |  \\         \\  \\/\\   /\\/  /         /  |       \\\n     /  /     \\   \\__       \\ ( 0\\ /0 ) /       __/   /        \\\n    /  /       \\     \\___    \\ \\_/|\\_/ /    ___/     /\\         \\\n   /  /         \\_)      \\___ \\/-\\|/-\\/ ___/      (_/\\ \\      `  \\\n  /  /           /\\__)       \\/  oVo  \\/       (__/   ` \\      `  \\\n /  /           /,   \\__)    (_/\\ _ /\\_)    (__/         `      \\  \\\n/  \'           //       \\__)  (__V_V__)  (__/                    \\  \\\n  \'  \'        /\'           \\   |{___}|   /         .              \\  \n \'  /        /              \\/ |{___}| \\/\\          `              \\  \n   /        \'       .        \\/{_____}\\/  \\          \\    `         \\  \n  /                ,         /{_______}\\   \\          \\    \\        \n                  /         /{___/_\\___}\\   `          \\    `\n";
}

//creates a Rhino of a random level between 4-5
Rhino::Rhino(){
	Name="Rhino";
	Boss=false;
	Level=RandomizeLevel(4,5);
	MaxHealth=20+5*Level;
	Health=MaxHealth;
	AttPower=4+Level;
	DefPower=4+Level;
	Experience=10*Level;
	Ascii="                     ,-.             __\n                   ,\'   `---.___.---\'  `.\n                 ,\'   ,-                 `-._\n               ,\'    /                       \\\n            ,\\/     /                        \\\\\n        )`._)>)     |                         \\\\\n        `>,\'    _   \\                  /       |\\\n          )      \\   |   |            |        |\\\\\n .   ,   /        \\  |    `.          |        | ))\n \\`. \\`-\'          )-|      `.        |        /((\n  \\ `-`   o`     _/ ;\\ _     )`-.___.--\\      /  `\'\n   `._         ,\'    \\`j`.__/        \\  `.    \\\n     / ,    ,\'       _)\\   /`        _) ( \\   /\n     \\__   /        /___) (         /____\\_) (\n       `--\'           /____\\             /____\\\n";
}

//creates a Tiger of a random level between 6-7
Tiger::Tiger(){
	Name="Tiger";
	Boss=false;
	Level=RandomizeLevel(6,7);
	MaxHealth=10+5*Level;
	Health=MaxHealth;
	AttPower=5+Level;
	DefPower=3+Level;
	Experience=10*Level;
	Ascii="   _\n  ( \\                ..-----..__\n   \\.\'.        _.--\'`  \'   \'  \' ```\'-._\n    `. `\'-..-\'\' `    \'  \'      . ;   ; `-\'\'\'-.,__/|/|\n      `\'-.;..-\'\'`|\'  `.  \'.    ;     \'  `    \'   `\'  `,\n                 \\ \'   .    \' .     \'   ;   .`   . \' o \\\n                  \'.\' . \' -.\\     .`   .`  .   .\\     `Y\n                    \'-.\' .   |\\  \'   ,    \'    /\'`--;;\'\n                      /\\   \'.| \'-._ /    \' _.-\'\n                      \\\'\\  \' / (`-.\'.\'  .\"/\n                       \\ )` /   .\'   .-\'./\n                        \'\\  \\).\'  .-\'--\"\n                          \'. `,_\'`\n                            `.__)\n";
}

//creates the Gorilla boss
Gorilla::Gorilla(){
	Name="Professor Bubbles";
	Boss=true;
	Level=10;
	MaxHealth=100;
	Health=MaxHealth;
	AttPower=18;
	DefPower=10;
	Experience=700;
	Ascii="                     ,.-\"\"\"-.,\n                    /   ===   \\\n                   /  =======  \\\n                __|  (O)   (O)  |__      \n               / _|    .---.    |_ \\         \n              | /.----/ O O \\----.\\ |       \n               \\/     |     |     \\/        \n               |                   |                      \n               |       _____       |          \n               _\\     /_____\\     /_         \n           ,.-\"  \"-.,_________,.-\"  \"-.,\n          /          |       |          \\  \n         |           \\       /           | \n         \\            |     |            /             \n       ,/ |           \\     /           | \\,     \n     ,/   \\            |   |            /   \\,    \n    /      |           |   |           |      \\  \n   /        |          |---|          |        \\\n  /\"-.,_,.-\"/\"-.,__,.-\"\\   /\"-.,__,.-\"\\\"-.,_,.-\"\\\n |         |            \\ /            |         |\n  \\__|__|_/ \\__|__|__|__/ \\__|__|__|__/ \\_|__|__/\n";
}

//creates a Centaur of a random level between 9-10
Centaur::Centaur(){
	Name="Centaur";
	Boss=false;
	Level=RandomizeLevel(9,10);
	MaxHealth=10+5*Level;
	Health=MaxHealth;
	AttPower=7+Level;
	DefPower=3+Level;
	Experience=10*Level;
	Ascii="                  ___,       /\\\n                 /,===      |  |\n              ,==( \"|\"      |  |\n             ,===\'\\_-/       \\/\n              ,---\'  \\---.   ||\n             (     - -    )  |:\n             |  \\_. \'  _./\\ ,\'/\\\n             |  )       / ,-||\\/\n   ___       ( < \\     (\\___/||\n  /   \\,----._\\ \\(   \'  )    --\n (   /         \\|\'\',, ,\'\\\n )   |          )\\   \'   |\n (  (|     ,    \\_)      |\n  )  )\\     \\-.__\\   |_, /\n  ( (  \\    )  )  ]  |  (\n   ) ) _) _/ _/   /, )) /\n   (/  \\  \\ \\      \\ |\\ |\n    )  _) \\__\\     ) | )(\n       )_,\\ )_\\    )| <_\\\n         )_\\      /_(  |_\\\n                   )_\\";
}

//creates a Griffin of a random level between 11-12
Griffin::Griffin(){
	Name="Griffin";
	Boss=false;
	Level=RandomizeLevel(11,12);
	MaxHealth=10+5*Level;
	Health=MaxHealth;
	AttPower=7+Level;
	DefPower=3+Level;
	Experience=10*Level;
	Ascii="              //           //\n             ///          ///\n            ////         ////\n            |////       /////\n            |))//;     /)))//;\n           /)))))/;   /)))))/;\n       .---`,))))/;  /)))))))/;\n   __--\\/o-  \\`))/; |)))))))/;\n  (----/    \\\\\\``;  |))))))/;\n     ~/-\\  \\\\\\\\\\``   \\))))))/;\n         \\\\\\\\\\\\\\\\`    |)))))/;\n         |\\\\\\\\\\\\\\\\___/))))))/;__-------.\n         //////|  ////))))))/;           \\___,\n        |||||||\\   \\\\|||||;:              \\_. \\\n        |\\\\\\\\\\\\\\\\\\                        |  | |\n         \\\\\\\\\\\\\\                          |  | |\n          |\\\\\\\\               __|        /   / /\n          | \\\\__\\     \\___----  |       |   / /\n          |    / |     >     \\   \\      \\  / /\n          |   /  |    /       \\   \\      >/ /  ,,\n          |   |  |   |         |   |    // /  //,\n          |   |  |   |         |   |   /| |   |\\\\,\n       _--\'   _--\'   |     _---_---\'  |  \\ \\__/\\|/\n      (-(-===(-(-(===/    (-(-=(-(-(==/   \\____/\n";
}

//creates the Seminole boss
Seminole::Seminole(){
	Haterade=1;
	Name="Nole King";
	Boss=true;
	Level=15;
	MaxHealth=120;
	Health=MaxHealth;
	AttPower=25;
	DefPower=15;
	Experience=0;
	Ascii="          / \\  \n       -..\\|/.-  \n       `-.\\|/.-\'     \n  \'.--.`\\ \\|/ /\'.--.\'\n  \\ o \' ======= \' o /\n   \\_`-=========-\'_/    ~   ~   ~\n  .--./,\'o.-.o`,\\.--.     ~   ~   ~\n \\_`- \\= (___) =/-\'_/\n  .--.`\\ -___- /\'.--.\n  \\.----\\_____/---./ \n  ~|/     FSU     \\|~\n  ~|  |=========|  |~\n  ~|  |  /)_    |  |~\n  ~|__|=/| /====|__|~\n   _||_//|/     |||_\n  (  /(/_______/ _  \\\n   \\\\\\;;;;;;;;;\\) )))\n   // |-   _   -|\n      |___/ \\___|\n     (___)   (___)\n";
}

//used to heal Seminole whenever health hits zero
void Seminole::DrinkHaterade(){
	if(Haterade>0){
		Haterade--;
		Health+=50;
		AttPower+=4;
	}
}

//**xLocations and yLocations need int values based on maps**//
//**Randomization needs to be checked**//
//**Enemy AttPower/Defense might need to be adjusted & Attack method isn't quite working**//

int main(){
	Player p;
	Rhino b;

	p.PrintCombatStats();
	b.PrintEnemyStats();
	b.PrintAscii();
	cout << "1. Attack  2. Eat  3. Flee" << endl << endl;

	string pAttack=p.Attack(b);
	string eAttack=b.Attack(p);

	p.PrintCombatStats();
	b.PrintEnemyStats();
	b.PrintAscii();
	cout << "1. Attack  2. Eat  3. Flee" << endl;
	cout << pAttack << endl;
	cout << eAttack;
}
