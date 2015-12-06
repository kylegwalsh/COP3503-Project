#include "Map.h"

//CONSTRUCTOR
Map::Map()
{
	level = 1;
	importMap();
}

/*
 * Imports the map for the current level into Map's member data
 */
void Map::importMap()
{
	char lev = level + '0';
	fileName = "maplevel";
	fileName += lev;
	readMapData();
}

/*
 * File Input reads map from already saved text file
 * Also reads in the columns and rows of the map
 */
void Map::readMapData()
{
	std::ifstream readFile(fileName, std::ios::in);
	if (!readFile)
	{
		std::cout << "ERROR: Input file could not be opened!" << std::endl;
		exit(-1);
	}
	else
	{
		std::string currentLine;
		std::vector<std::string> rowVec;
		std::string pushStr;
		while (std::getline(readFile, currentLine))
		{
			if (currentLine.at(0) != '\\')
			{
				if (currentLine.at(0) == '#')
				{
					rows = atoi(currentLine.substr(1).c_str());
				}
				if (currentLine.at(0) == '$')
				{
					columns = atoi(currentLine.substr(1).c_str());
				}
			}
			else
			{
				for (int i = 0; i < currentLine.length(); i++)
				{
					rowVec.push_back(currentLine.substr(i, 1));
				}
				mapData.push_back(rowVec);
				rowVec.clear();
			}
		}
	}
}

/*
 * Loads the next map into member data
 * Clears previous data
 */
void Map::loadNext()
{
	mapData.clear();
	level++;
	importMap();
}

/*
 * returns the amount of columns
 */
int Map::getColumns()
{
	return columns;
}

/*
 * returns the amount of rows
 */
int Map::getRows()
{
	return rows;
}

/*
 * returns a read only const pointer version of the mapData
 */
std::vector<std::vector<std::string> > const &Map::getMapData() const
{
	return mapData;
}

