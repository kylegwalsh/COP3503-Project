#include "Map.h"

Map::Map()
{
	level = 1;
 	importMap();
}

void Map::importMap()
{
	fileName = "maplevel";
	fileName += std::to_string(level);
	readMapData();
	initializeAllowableArea();
}

void Map::readMapData()
{
	std::ifstream readFile(fileName, std::ios::in);
	if (!readFile)
	{
		std::cout << "ERROR: Input file could not be opened!" << std::endl;
		exit (EXIT_FAILURE);
	}
	else
	{
		std::string currentLine;
		std::vector<std::string> rowVec;
		std::string pushStr;
		while (std::getline(readFile, currentLine))
		{
			if (currentLine.at(0)!='\\')
			{
				if (currentLine.at(0)=='#')
				{
					rows = atoi(currentLine.substr(1).c_str());
				}
				if (currentLine.at(0)=='$')
				{
					columns = atoi(currentLine.substr(1).c_str());
				}
			}
			else
			{
				for (int i=0; i<currentLine.length(); i++)
				{
					rowVec.push_back(currentLine.substr(i,1));
				}
				mapData.push_back(rowVec);
				rowVec.clear();
			}
		}
	}
}

void Map::initializeAllowableArea()
{
	for (int i=0; i<rows; i++)
	{
		std::vector<int> rowVec;
		for (int j=0; j<columns; j++)
		{
			rowVec.push_back(1);
		}
		boolAllowableArea.push_back(rowVec);
	}
}

void Map::reset()
{
	initializeAllowableArea();
}

void Map::loadNext()
{
	level++;
	importMap();
}

int Map::getColumns()
{
	return columns;
}

int Map::getRows()
{
	return rows;
}

std::vector< std::vector<std::string> > const &Map::getMapData() const
{
	return mapData;
}

std::vector< std::vector<int> > const &Map::getAllowableArea() const
{
	return boolAllowableArea;
}