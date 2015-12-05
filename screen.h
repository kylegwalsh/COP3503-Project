/*
 * screen.h
 *
 *  Created on: Nov 28, 2015
 *      Author: Kyle
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "map.h"
#include "character.h"
#include "game.h"
using namespace std;

void ResizeScrn();
void StartScrn();
void Level1IntroScrn();
void Level2IntroScrn();
void Level3IntroScrn();
void BeatGameScrn();
void ClearScrn();
void LevelUpScrn();
void GameOverScrn();
void QuitScrn();

#endif /* SCREEN_H_ */
