#ifndef MAP_CREATOR_H
#define MAP_CREATOR_H

#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>

class MapCreator
{
private:
	int mapLevel;
	std::vector<std::string> map;
	int rows;
	int columns;
	//number of diffferent areas
	int gatoradeMachines; //Representation G
	int houseNum; //Representation H
	int barracksNum; //M
	int towerNum; //T

	void assignAreaAmounts();
	void assignHeightWidth();
	void createBasicMap();
	void addEnvironment();
	void save();
	bool isIsolated(int c, int r);

public:
	MapCreator();
	MapCreator(int level);
	void createNewLevel();
	void addLevel();
};

#endif //MAP_CREATOR_H
