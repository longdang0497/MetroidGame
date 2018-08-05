#pragma once
#include "Define.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include "trace.h"
#include <d3dx9.h>

using namespace std;

class Loader
{
private:
	int m_Row;
	int m_Col;
	string filePath;
public:
	Loader();
	Loader(string filePath);
	~Loader();

	void loadFile();
	int getRow();
	int getCol();
};
