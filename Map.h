#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>

//a class for the map
class Map
{
private:
	std::vector<std::vector<std::string> > mapData; //represents the map
	std::vector<std::vector<int> > boolAllowableArea; //1 - true, 0-false
	int columns; //x
	int rows; //y
	std::string fileName; //the file that the map is being read from
	int level; //current level

	void readMapData();
	void importMap();

public:
	Map();
	int getColumns();
	int getRows();
	void loadNext();
	std::vector<std::vector<std::string> > const &getMapData() const;
};

#endif //MAP_H
