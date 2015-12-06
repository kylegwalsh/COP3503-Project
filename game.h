/*
 * game.h
 *
 *  Created on: Dec 5, 2015
 *      Author: Kyle
 */

#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <string>
#include <conio.h>
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
		bool keyFound;

		void playLevel();
		void printMap(int playerX, int playerY);
		void update();
		void gameOver();
		void setHorizontalPadding();
		void loadNextLevel();


	public:
		Game();
		void start();
		void GameOverScrn();
};

void ResizeScrn();
void StartScrn();
void Level1IntroScrn();
void Level2IntroScrn();
void Level3IntroScrn();
void BeatGameScrn();
void ClearScrn();
void LevelUpScrn();
void QuitScrn();
bool Combat(Player *p, Enemy *e);
bool FinalBossCombat(Player *p, Seminole *e);

#endif /* GAME_H_ */
