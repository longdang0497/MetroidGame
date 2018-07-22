#include "Map.h"


Map::Map(LPD3DXSPRITE spriteHandler, string filePath, LPDIRECT3DDEVICE9 d3ddev, int left, int top) {
	this->filePath = filePath;
	this->d3ddev = d3ddev;

	grid = new Grid();
	
	//---------Khởi tạo spriteHandler---------------
	if (this->d3ddev == NULL) return;

	HRESULT result = D3DXCreateSprite(this->d3ddev, &spriteHandler);
	if (result != D3D_OK)
		trace(L"Unable to create SpriteHandler");

	Texture * texture = new Texture();
	_texture = texture->loadTexture(this->d3ddev, BRICK_TEXTURE);
	if (_texture == NULL)
		trace(L"Unable to load BrickTexture");

	tileMap = new TileObject();
	tileMap->InitSprites(this->d3ddev, _texture);
	tileMap->Init(left, top);

	if (!this->loadMap(this->filePath)) {
		trace(L"Unable to load map");
	}
	this->setLimitation(left, top, m_max_Column * BRICK_SIZE, m_max_Row * BRICK_SIZE);
}

Map::~Map() {
	
}

void Map::setLimitation(int x, int y, int width, int height) {
	m_boundary.left = x;
	m_boundary.right = x + width;
	m_boundary.top = y;
	m_boundary.bottom = y + height;
	this->widthLimitation = width;
	this->heightLimitation = height;
}

RECT Map::getBoundary()
{
	return m_boundary;
}

vector<string> Map::getStringMap() {
	return this->stringMap;
}

bool Map::loadMap(string filePath) {
	ifstream file_txt(filePath);
	string str;
	int row = 0, column = 0;
	while (getline(file_txt, str)) {
		row++;
		if (str.length() > column)
			column = str.length();
		stringMap.push_back(str);
	}

	m_max_Row = row;
	m_max_Column = column;

	if (!stringMap.empty())
		return true;
	return false;
}

void Map::drawMap() {
	for (int i = 0; i < drawBrickArray.size(); i++)
	{
		drawBrick(drawBrickArray[i]);
	}
}

void Map::drawBrick(TileObject * value) {
	float x_pixel = value->x_pixel;
	float y_pixel = value->y_pixel;
	D3DXVECTOR3 pos = D3DXVECTOR3(x_pixel, y_pixel, 0);
	// draw different type of bricks
	switch (value->type)
	{
	case '1':
	{
		tileMap->Render('1', 0, pos);
		break;
	}
	case '2':
	{
		tileMap->Render('2', 1, pos);
		break;
	}
	case '3':
	{
		tileMap->Render('3', 2, pos);
		break;
	}
	case '4':
	{
		tileMap->Render('4', 3, pos);
		break;
	}
	case '5':
	{
		tileMap->Render('5', 4, pos);
		break;
	}
	case '6':
	{
		tileMap->Render('6', 5, pos);
		break;
	}
	case '7':
	{
		tileMap->Render('7', 6, pos);
		break;
	}
	case '8':
	{
		tileMap->Render('8', 7, pos);
		break;
	}
	case '9':
	{
		tileMap->Render('9', 8, pos);
		break;
	}
	case 'a':
	{
		tileMap->Render('a', 9, pos);
		break;
	}
	case 'b':
	{
		tileMap->Render('b', 10, pos);
		break;
	}
	case 'c':
	{
		tileMap->Render('c', 11, pos);
		break;
	}
	case 'd':
	{
		tileMap->Render('d', 12, pos);

		break;
	}
	case 'e':
	{
		tileMap->Render('e', 13, pos);
		break;
	}
	case 'f':
	{
		tileMap->Render('f', 14, pos);

		break;
	}
	case 'g':
	{
		tileMap->Render('g', 15, pos);
		break;
	}
	case 'h':
	{
		tileMap->Render('h', 16, pos);
		break;
	}
	case 'i':
	{
		tileMap->Render('i', 17, pos);
		break;
	}
	case 'k':
	{
		tileMap->Render('k', 18, pos);
		break;
	}
	case 'l':
	{
		tileMap->Render('l', 19, pos);
		break;
	}
	case 'm':
	{
		tileMap->Render('m', 20, pos);
		break;
	}
	case 'n':
	{
		tileMap->Render('n', 21, pos);
		break;
	}
	case 'o':
	{
		tileMap->Render('o', 22, pos);
		break;
	}
	case 'p':
	{
		tileMap->Render('p', 23, pos);
		break;
	}
	case 'q':
	{
		tileMap->Render('q', 24, pos);
		break;
	}
	case 'r':
	{
		tileMap->Render('r', 25, pos);
		break;
	}
	case 's':
	{
		tileMap->Render('s', 26, pos);
		break;
	}
	case 't':
	{
		tileMap->Render('t', 27, pos);
		break;
	}
	case 'u':
	{
		tileMap->Render('u', 28, pos);
		break;
	}
	case 'v':
	{
		tileMap->Render('v', 29, pos);
		break;
	}
	case 'w':
	{
		tileMap->Render('w', 30, pos);
		break;
	}
	case 'x':
	{
		tileMap->Render('x', 31, pos);
		break;
	}
	case 'y':
	{
		tileMap->Render('y', 32, pos);
		break;
	}
	case 'z':
	{
		tileMap->Render('z', 33, pos);
		break;
	}
	case 'A':
	{
		tileMap->Render('A', 34, pos);
		break;
	}
	case 'B':
	{
		tileMap->Render('B', 35, pos);
		break;
	}
	case 'C':
	{
		tileMap->Render('C', 36, pos);
		break;
	}
	case 'D':
	{
		tileMap->Render('D', 37, pos);
		break;
	}
	case 'E':
	{
		tileMap->Render('E', 38, pos);
		break;
	}
	case 'F':
	{
		tileMap->Render('F', 39, pos);
		break;
	}
	case 'G':
	{
		tileMap->Render('G', 40, pos);
		break;
	}
	case 'H':
	{
		tileMap->Render('H', 41, pos);
		break;
	}
	case 'I':
	{
		tileMap->Render('I', 42, pos);
		break;
	}
	case 'K':
	{
		tileMap->Render('K', 43, pos);
		break;
	}
	case 'L':
	{
		tileMap->Render('L', 44, pos);
		break;
	}
	case 'M':
	{
		tileMap->Render('M', 45, pos);
		break;
	}
	case 'N':
	{
		tileMap->Render('N', 46, pos);
		break;
	}
	case 'O':
	{
		tileMap->Render('O', 47, pos);
		break;
	}
	case 'P':
	{
		tileMap->Render('P', 48, pos);
		break;
	}
	case 'Q':
	{
		tileMap->Render('Q', 49, pos);
		break;
	}
	case 'R':
	{
		tileMap->Render('R', 50, pos);
		break;
	}
	case 'S':
	{
		tileMap->Render('S', 51, pos);
		break;
	}
	case 'T':
	{
		tileMap->Render('T', 52, pos);
		break;
	}
	case'U':
	{
		tileMap->Render('U', 53, pos);
		break;
	}
	case '0':
	{
		break;
	}
	default:
		break;
	}
}

void Map::Update(int roomID) {

}

void Map::UpdateMap(RECT cameraBound) {
	drawBrickArray.clear();
	RECT bound = cameraBound;
	bound.left -=  2 * BRICK_SIZE;
	bound.top -= 2 * BRICK_SIZE;
	vector<string> strBrick = this->getStringMap();

	//kiem tra neu brick nam ben trong cai bound
	for (int i = 0; i < strBrick.size(); i++)
	{
		for (int j = 0; j < strBrick[i].length(); j++)
		{
			float x_pixel = m_boundary.left + j * BRICK_SIZE;
			float y_pixel = m_boundary.top + i * BRICK_SIZE;
			D3DXVECTOR2 point(x_pixel, y_pixel);
			if ( Math::isPointinRectangle(point, bound) ) {
				TileObject * new_brick = new TileObject();
				new_brick->type = strBrick[i][j];
				new_brick->x_pixel = x_pixel;
				new_brick->y_pixel = y_pixel;
				new_brick->pos_x = new_brick->x_pixel;
				new_brick->pos_y = new_brick->y_pixel;
				grid->add(new_brick);
				drawBrickArray.push_back(new_brick);
			}
		}
	}
}