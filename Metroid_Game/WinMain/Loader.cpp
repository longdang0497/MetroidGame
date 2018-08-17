#include "Loader.h"

Loader::Loader()
{
}

Loader::Loader(string filePath)
{
	m_Col = 0;
	m_Row = 0;
	this->filePath = filePath;
	stringMap = vector<string>();

	loadFile();
}

Loader::~Loader()
{
	this->filePath = "";
	m_Row = 0;
	m_Col = 0;
}

void Loader::loadFile()
{
	ifstream file_txt(this->filePath);
	string str = "";
	int row = 0, column = 0;
	while (getline(file_txt, str)) {
		row++;
		if (str.length() > column)
			column = str.length();
		stringMap.push_back(str);
	}

	m_Row = row;
	m_Col = column;
	if (stringMap.empty())
		trace(L"Unable to load this map !!!");
}

int Loader::getRow()
{
	return m_Row;
}

int Loader::getCol()
{
	return m_Col;
}

vector<string> Loader::getStringMap()
{
	return stringMap;
}
