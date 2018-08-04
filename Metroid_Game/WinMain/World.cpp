#include "World.h"
#include <vector>

using namespace std;

World::World()
{
}

World::World(LPD3DXSPRITE spriteHandler, Metroid * metroid, int width, int height)
{
	this->spriteHandler = spriteHandler;
	this->metroid = metroid;

	//Khởi tạo các đối tượng trong World
	grid = new Grid(height, width);
	/*gateRight = new Gate(spriteHandler, this, grid);
	gateLeft = new Gate(spriteHandler, this, grid);
	gateBlock = new GateBlock(spriteHandler, this, grid);*/
	samus = new Samus(spriteHandler, this, grid);
	maruMari = new MaruMari(spriteHandler, this, grid);
	explode = new ExplodeEffect(spriteHandler, this, grid);
	bomb = new Bomb(spriteHandler, this);
	itemBomb = new ItemBomb(spriteHandler, this, grid);
	
	// Khởi tạo đạn (3 viên)
	Bullet *bullet1 = new Bullet(spriteHandler);
	Bullet *bullet2 = new Bullet(spriteHandler);
	Bullet *bullet3 = new Bullet(spriteHandler);
	this->samusBullet.push_back(bullet1);
	this->samusBullet.push_back(bullet2);
	this->samusBullet.push_back(bullet3);

	loadEnemyPositions("Monster_Room1.txt");

}

World::~World()
{
	delete(samus);
	delete(maruMari);
	delete(gateRight);
	delete(gateLeft);
	delete(gateBlock);
	delete(grid);
	delete(metroid);
	//delete(skree);
	delete(explode);
	delete(bomb);
	delete(itemBomb);
}

void World::Update(float t)
{
	this->grid->setDeltaTime(t);
	this->samus->Update(t);
	/*int row = (int)floor(this->samus->getlastPosY() / CELL_SIZE);
	int column = (int)floor(this->samus->getlastPosX() / CELL_SIZE);*/

	maruMari->Update(t);

	for (int i = 0; i < this->samusBullet.size(); i++) {
		this->samusBullet[i]->Update(t, this->samus->getPosX(), this->samus->getPosY());
	}

	/*START UPDATING ENEMY*/
	for (int i = 0; i < this->enemy.size(); i++) {
		if (this->enemy[i]->isInsideMapBound(this->metroid->camera->getBoundary())) {
			if (!this->enemy[i]->isActive && !this->enemy[i]->isDeath) {
				enemy[i]->isActive = true;
				enemy[i]->startMoving();
			}
			else if (this->enemy[i]->isActive && !this->enemy[i]->isDeath) {
				enemy[i]->Update(t);
			}
			else {
				//khong lam gi het
			}
		}
	}
	/*END UPDATING ENEMY*/
}

void World::Render()
{
	this->samus->Render();
	maruMari->Render();
	for (int i = 0; i < this->samusBullet.size(); i++) {
		this->samusBullet[i]->Render();
	}

	for (int i = 0; i < this->enemy.size(); i++) {
		if (this->enemy[i]->isInsideMapBound(this->metroid->camera->getBoundary())) {
			if (this->enemy[i]->isActive && !this->enemy[i]->isDeath) {
				this->enemy[i]->Render();
			}
		}
	}
}

void World::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	Texture * textureSamus = new Texture();
	LPDIRECT3DTEXTURE9 samus_texture = textureSamus->loadTexture(d3ddv, TEXTURE_GAME_CHARACTERS);
	if (samus_texture == NULL)
		trace(L"Unable to load Samus Texture");
	samus->InitSprites(d3ddv, samus_texture);

	Texture * textureMaru = new Texture();
	LPDIRECT3DTEXTURE9 maru_texture = textureMaru->loadTexture(d3ddv, ITEM_SPRITE_PATH);
	if (maru_texture == NULL)
		trace(L"Unable to load Maru Mari Texture");
	maruMari->InitSprites(d3ddv, maru_texture);

	Texture * textureGate = new Texture();
	LPDIRECT3DTEXTURE9 gate_texture = textureGate->loadTexture(d3ddv, GATE_SPRITES_PATH);
	if (gate_texture == NULL)
		trace(L"Unable to load Gate Texture");
	/*gateRight->InitSprites(d3ddv, gate_texture, GATE_RIGHT);
	gateLeft->InitSprites(d3ddv, gate_texture, GATE_LEFT);
	gateBlock->InitSprites(d3ddv, gate_texture);*/

	Texture * textureExplode = new Texture();
	LPDIRECT3DTEXTURE9 explode_texture = textureExplode->loadTexture(d3ddv, EFFECT_SPRITE_PATH);
	if (explode_texture == NULL)
		trace(L"Unable to load Explode Texture");
	explode->InitSprites(d3ddv, explode_texture);

	Texture * textureItemBomb = new Texture();
	LPDIRECT3DTEXTURE9 itemBomb_texture = textureItemBomb->loadTexture(d3ddv, ITEM_SPRITE_PATH);
	if (itemBomb_texture == NULL)
		trace(L"Unable to load item Bomb Texture");
	itemBomb->InitSprites(d3ddv, itemBomb_texture);

	Texture * textureBomb = new Texture();
	LPDIRECT3DTEXTURE9 bomb_texture = textureBomb->loadTexture(d3ddv, BOMB_TEXTURE);
	if (bomb_texture == NULL)
		trace(L"Unable to load Bomb Texture");
	bomb->InitSprites(d3ddv, bomb_texture);

// Bullet Texture
	Texture texture2;
	LPDIRECT3DTEXTURE9 bulletTexture = texture2.loadTexture(d3ddv, SAMUS_BULLET_PATH);
	if (bulletTexture == NULL)
		trace(L"Unable to load BulletTexture");
	for (int i = 0; i < this->samusBullet.size(); i++) {
		this->samusBullet[i]->InitSprites(d3ddv, bulletTexture);
	}

	//Enemy (Zoomer) Texture
	for (int i = 0; i < this->enemy.size(); i++) {
		this->enemy[i]->InitSprites(d3ddv);
	}
}

void World::loadEnemyPositions(string filePath) {
	ifstream file_txt(filePath);
	string str;
	vector<string> v;
	while (getline(file_txt, str)) {
		v = split(str, "\t");
		Enemy *monster;
		int value = atoi(v[0].c_str());
		switch (value)
		{
		case ZOOMER_YELLOW_CASE: {
			monster = new Zoomer(spriteHandler, this, ZOOMER_YELLOW);
			monster->SetDirection(v[5]);
			monster->setEnemyStatefromString(v[6]);
			break;
		}
		case ZOOMER_PINK_CASE: {
			monster = new Zoomer(spriteHandler, this, ZOOMER_PINK);
			monster->SetDirection(v[5]);
			monster->setEnemyStatefromString(v[6]);
			break;
		}
		case SKREE_CASE: {

			break;
		}
		case RIO_CASE: {

			break;
		}
		default:
			break;
		}
		monster->setPosX(stoi(v[3]));
		monster->setPosY(stoi(v[4]));
		monster->setActive(false);
		monster->setVelocityX(0);
		monster->setVelocityY(0);
		this->enemy.push_back(monster);
		v.clear();
	}
	if (v.size() != NULL)
		trace(L"Unable to load EnemyPosition");
}

vector<string> World::split(string s, string c) {
	string::size_type i = 0;
	string::size_type j = s.find(c);
	vector<string> v;
	while (j != string::npos) {
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);

		if (j == string::npos)
			v.push_back(s.substr(i, s.length()));
	}
	return v;
}
