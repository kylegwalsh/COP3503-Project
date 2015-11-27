#ifndef MAP_CREATOR_H
#define MAP_CREATOR_H


#include <iostream>

#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class MapCreator 
{
private:
	int mapLevel;
	std::vector<std::string> map; 
	int rows;
	int columns;
	int bossX;
	static const int bossY = 0;
	//number of diffferent areas
	int gatoradeMachines; //Representation G
	int houseNum; //Representation H
 	int barracksNum; //M
	int towerNum; //T
	int obstacleNum;

	void assignAreaAmounts();
	void assignHeightWidth();
	void createBasicMap();
	void addEnvironment();
	void addObstacles();
	void save();
	bool isIsolated(int c, int r);

public:
	MapCreator();
	MapCreator(int level);

	void printMap();
};

#endif //MAP_CREATOR_H