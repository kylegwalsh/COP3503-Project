#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

class Map 
{
private:
	std::vector< std::vector<std::string> > mapData; 
	std::vector< std::vector<int>  > boolAllowableArea; //1 - true, 0-false
	int columns; //x
	int rows; //y
	std::string fileName;

	void readMapData();
	void initializeAllowableArea();
	vector

public:
	Map();
	Map(int level);
	int getColumns();
	int getRows();
	std::vector< std::vector<std::string> > const &getMapData() const;
};

#endif //MAP_H