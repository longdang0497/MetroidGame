#include "Map.h"

Map::Map(LPD3DXSPRITE spriteHandler, string filePath, int left, int top) {
	this->filePath = filePath;

	this->top = top;
	this->left = left;

	spriteHandler->GetDevice(&d3ddv);
	
	Texture * textureMap = new Texture();
	this->mapTexture = textureMap->loadTexture(d3ddv, BRICK_TEXTURE);
	if (mapTexture == NULL)
		trace(L"Unable to load BrickTexture");

	this->sprite = new Sprite(spriteHandler, mapTexture, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, 1, 1);
	if (this->sprite == NULL)
		trace(L"Unable to load map sprite");

	if (!this->loadMap(this->filePath)) {
		trace(L"Unable to load map");
	}
}

Map::~Map() {
	delete sprite;
	delete grid;
}

void Map::setLimitation(int width, int height) {
	m_boundary.left = this->left;
	m_boundary.right = this->left + width * 32;
	m_boundary.top = this->top;
	m_boundary.bottom = this->top + height * 32;
	this->widthLimitation = width * 32;
	this->heightLimitation = height * 32;
}

RECT Map::getBoundary()
{
	return m_boundary;
}

LPDIRECT3DDEVICE9 Map::getDevice() {
	return this->deviceManager->getdevice();
}

LPDIRECT3DTEXTURE9 Map::getTexture() {
	return this->mapTexture;
}

vector<string> Map::getStringMap() {
	return this->stringMap;
}

bool Map::loadMap(string filePath) {
	ifstream file_txt(filePath);
	string str;
	while (getline(file_txt, str)) {
		stringMap.push_back(str);
	}
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

void Map::drawBrick(brick value) {
	float x_pixel = value.x_pixel;
	float y_pixel = value.y_pixel;
	D3DXVECTOR3 pos = D3DXVECTOR3(x_pixel, y_pixel, 0);
	// draw different type of bricks
	switch (value.type)
	{
	case '1':
	{
		sprite->drawSprite(0, 0, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case '2':
	{
		sprite->drawSprite(0, 1 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case '3':
	{
		sprite->drawSprite(0, 2 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case '4':
	{
		sprite->drawSprite(0, 3 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case '5':
	{
		sprite->drawSprite(0, 4 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case '6':
	{
		sprite->drawSprite(0, 5 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case '7':
	{
		sprite->drawSprite(0, 6 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case '8':
	{
		sprite->drawSprite(0, 7 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case '9':
	{
		sprite->drawSprite(0, 8 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'a':
	{
		sprite->drawSprite(0, 9 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'b':
	{
		sprite->drawSprite(0, 10 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'c':
	{
		sprite->drawSprite(0, 11 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'd':
	{
		sprite->drawSprite(0, 12 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);

		break;
	}
	case 'e':
	{
		sprite->drawSprite(0, 13 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'f':
	{
		sprite->drawSprite(0, 14 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);

		break;
	}
	case 'g':
	{
		sprite->drawSprite(0, 15 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'h':
	{
		sprite->drawSprite(0, 16 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'i':
	{
		sprite->drawSprite(0, 17 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'k':
	{
		sprite->drawSprite(0, 18 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'l':
	{
		sprite->drawSprite(0, 19 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'm':
	{
		sprite->drawSprite(0, 20 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'n':
	{
		sprite->drawSprite(0, 21 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'o':
	{
		sprite->drawSprite(0, 22 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'p':
	{
		sprite->drawSprite(0, 23 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'q':
	{
		sprite->drawSprite(0, 24 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'r':
	{
		sprite->drawSprite(0, 25 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 's':
	{
		sprite->drawSprite(0, 26 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 't':
	{
		sprite->drawSprite(0, 27 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'u':
	{
		sprite->drawSprite(0, 28 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'v':
	{
		sprite->drawSprite(0, 29 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'w':
	{
		sprite->drawSprite(0, 30 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'x':
	{
		sprite->drawSprite(0, 31 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'y':
	{
		sprite->drawSprite(0, 32 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'z':
	{
		sprite->drawSprite(0, 33 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'A':
	{
		sprite->drawSprite(0, 34 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'B':
	{
		sprite->drawSprite(0, 35 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'C':
	{
		sprite->drawSprite(0, 36 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'D':
	{
		sprite->drawSprite(0, 37 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'E':
	{
		sprite->drawSprite(0, 38 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'F':
	{
		sprite->drawSprite(0, 39 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'G':
	{
		sprite->drawSprite(0, 40 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'H':
	{
		sprite->drawSprite(0, 41 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'I':
	{
		sprite->drawSprite(0, 42 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'K':
	{
		sprite->drawSprite(0, 43 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'L':
	{
		sprite->drawSprite(0, 44 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'M':
	{
		sprite->drawSprite(0, 45 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'N':
	{
		sprite->drawSprite(0, 46 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'O':
	{
		sprite->drawSprite(0, 47 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'P':
	{
		sprite->drawSprite(0, 48 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'Q':
	{
		sprite->drawSprite(0, 49 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'R':
	{
		sprite->drawSprite(0, 50 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'S':
	{
		sprite->drawSprite(0, 51 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case 'T':
	{
		sprite->drawSprite(0, 52 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
		break;
	}
	case'U':
	{
		sprite->drawSprite(0, 53 * BRICK_SIZE, WIDTH_SPRITE_BRICK, HEIGHT_SPRITE_BRICK, pos);
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

	//may phai kiem tra neu cai brick do nam ben trong cai bound
	for (int i = 0; i < strBrick.size(); i++)
	{
		for (int j = 0; j < strBrick[i].length(); j++)
		{
			float x_pixel = m_boundary.left + j * BRICK_SIZE;
			float y_pixel = m_boundary.top + i * BRICK_SIZE;
			D3DXVECTOR2 point(x_pixel, y_pixel);
			if ( Math::isPointinRectangle(point, bound) ) {
				brick new_brick = brick();
				new_brick.type = strBrick[i][j];
				new_brick.x_pixel = x_pixel;
				new_brick.y_pixel = y_pixel;
				drawBrickArray.push_back(new_brick);
			}
		}
	}
}

void Map::setGrid(Grid * grid) {
	if (grid == NULL)
		trace(L"Grid is NULL");
	else {
		this->grid = grid;
	}
}

Grid* Map::getGrid() {
	if (this->grid == NULL)
		return NULL;
	return this->grid;
}

void Map::inputBrickToGrid() {
	if (this->getStringMap().size() <= 0) {
		return;
	}
	for (int i = 0; i < this->stringMap.size(); i++) {
		for (int j = 0; j < this->stringMap[i].size(); j++) {
			if (this->stringMap[i][j] != '0') {
				float x = (float)j * 32;
				float y = (float)i * 32;
				Brick * brick = new Brick(x, y, BRICK_SIZE, BRICK_SIZE);
				this->grid->add(brick);
			}
		}
	}
}