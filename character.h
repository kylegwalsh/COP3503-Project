/*
 * character.h
 *
 *  Created on: Nov 28, 2015
 *      Author: Kyle
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <vector>
#include <limits>
using namespace std;

//the overall character object
class Character{
protected:
	int MaxHealth;
	int Health;
	int AttPower;
	int DefPower;
	int Level;
	int Experience;
	string Name;
	mt19937 gen;

public:
	Character();
	int GetExperience();
	int GetMaxHealth();
	int GetHealth();
	int GetLevel();
	int GetDefPower();
	string GetName();
	void ChangeHealth(int h);
	string Attack(Character *c);
};

//a subclass holding the player's data
class Player: public Character{
private:
	int Food;
	int Gatorade;
	int MaxStamina;
	int Stamina;
	int LevelUpEXP;
	int xLocation;
	int yLocation;
	vector<int> SavedStats;

public:
	Player();
	void ChangeStamina(int s);
	string Eat();
	string Drink();
	void LevelUp();
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void SetLocation(int x, int y);
	void GainExperience(Character c);
	void FindFood();
	void FindGatorade();
	int GetFood();
	int GetGatorade();
	int GetMaxStamina();
	int GetStamina();
	int GetxLocation();
	int GetyLocation();
	string PrintMapStats();
	string PrintCombatStats();
	void SaveStats();
	void RevertStats();
};

//a subclass holding enemy's data
class Enemy: public Character{
protected:
	vector<string> Ascii;
	bool Boss;

public:
	int RandomizeLevel(int low, int high);
	string PrintEnemyStats();
	void PrintAscii();
};

//a specific class for a Bat enemy
class Bat: public Enemy{
public:
	Bat();
};

//a specific class for a Scorpion enemy
class Scorpion: public Enemy{
public:
	Scorpion();
};

//a specific class for the first boss (Dragon)
class Dragon: public Enemy{
public:
	Dragon();
};

//a specific class for a Rhino enemy
class Rhino: public Enemy{
public:
	Rhino();
};

//a specific class for a Tiger enemy
class Tiger: public Enemy{
public:
	Tiger();
};

//a specific class for the second Boss (Gorilla)
class Gorilla: public Enemy{
public:
	Gorilla();
};

//a specific class for a Centaur enemy
class Centaur: public Enemy{
public:
	Centaur();
};

//a specific class for a Griffin enemy
class Griffin: public Enemy{
public:
	Griffin();
};

//a specific class for the final boss (Seminole)
class Seminole: public Enemy{
private:
int Haterade;

public:
	Seminole();
	void DrinkHaterade();
};

#endif /* CHARACTER_H_ */
