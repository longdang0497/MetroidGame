#include "World.h"
#include <vector>

using namespace std;

World::World()
{
}

World::World(LPD3DXSPRITE spriteHandler, Metroid * metroid)
{
	this->spriteHandler = spriteHandler;
	this->metroid = metroid;

	//Khởi tạo các đối tượng trong World
	samus = new Samus(spriteHandler, this, metroid->getGrid());
	
	// Khởi tạo đạn (3 viên)
	Bullet *bullet1 = new Bullet(spriteHandler, metroid->getGrid());
	Bullet *bullet2 = new Bullet(spriteHandler, metroid->getGrid());
	Bullet *bullet3 = new Bullet(spriteHandler, metroid->getGrid());
	this->samusBullet.push_back(bullet1);
	this->samusBullet.push_back(bullet2);
	this->samusBullet.push_back(bullet3);

	maruMari = new MaruMari(spriteHandler, this);

	explodeEffect = new ExplodeEffect(spriteHandler, this, metroid->getGrid());
	bombWeapon = new BombWeapon(spriteHandler, this);

	gateRightRoom1 = new Gate(spriteHandler, this);
	gateLeftRoom1 = new Gate(spriteHandler, this);
	gateRightRoom2 = new Gate(spriteHandler, this);
	gateLeftRoom2 = new Gate(spriteHandler, this);
	gateRightBoss1 = new Gate(spriteHandler, this);
	gateLeftBoss1 = new Gate(spriteHandler, this);

	gateBlockRoom1 = new GateBlock(spriteHandler, this, metroid->getGrid());
	gateBlockRoom2 = new GateBlock(spriteHandler, this, metroid->getGrid());
	gateBlockBoss1 = new GateBlock(spriteHandler, this, metroid->getGrid());

	kraid = new Kraid(spriteHandler, this);
	ridley = new Ridley(spriteHandler, this);

	loadEnemyPositions("Monster_Room1.txt");
}

World::~World()
{
	delete(samus);
	delete(maruMari);
	delete(metroid);
	delete(explodeEffect);
	delete(bombWeapon);
	delete(gateLeftRoom1);
	delete(gateRightRoom1);
	delete(gateLeftRoom2);
	delete(gateRightRoom2);
	delete(gateLeftBoss1);
	delete(gateRightBoss1);
	delete(gateBlockRoom1);
	delete(gateBlockRoom2);
	delete(gateBlockBoss1);
	delete(ridley);
	delete(kraid);
}

void World::Update(float t)
{
	this->samus->Update(t);
	int row = (int)floor(this->samus->getlastPosY() / CELL_SIZE);
	int column = (int)floor(this->samus->getlastPosX() / CELL_SIZE);

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

	bombWeapon->Update(t);
	explodeEffect->Update(t);
	gateBlockRoom1->Update(t);
	gateBlockRoom2->Update(t);
	gateBlockBoss1->Update(t);

	gateLeftRoom1->Update(t);
	gateRightRoom1->Update(t);
	gateLeftRoom2->Update(t);
	gateRightRoom2->Update(t);
	gateLeftBoss1->Update(t);
	gateRightBoss1->Update(t);

	kraid->Update(t);
	ridley->Update(t);

	if (samus->pos_x < gateLeftRoom1->pos_x + gateLeftRoom1->width || samus->pos_x > gateLeftRoom1->pos_x + gateLeftRoom1->width)
	{
		//float time = 0.2;
		if (gateLeftRoom1->getGateState() == OPEN)
		{			
			//time -= t;
			//if (time <= 0)
				gateLeftRoom1->setGateState(CLOSE);
		}
	}
	if (samus->pos_x > gateRightRoom1->pos_x + gateRightRoom1->width || samus->pos_x < gateRightRoom1->pos_x + gateRightRoom1->width)
	{
		//float time = 0.2;
		if (gateRightRoom1->getGateState() == OPEN)
		{
			//time -= t;
			//if (time <= 0)
				gateRightRoom1->setGateState(CLOSE);
		}
	}
	/*else if(gateRight->getGateState() == DESTROYING)
		gateLeft->setGateState(DESTROYING);*/
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

	bombWeapon->Render();
	explodeEffect->Render();
	gateBlockRoom1->Render();
	gateBlockRoom2->Render();
	gateBlockBoss1->Render();

	gateRightRoom1->Render();
	gateLeftRoom1->Render();
	gateRightRoom2->Render();
	gateLeftRoom2->Render();
	gateRightBoss1->Render();
	gateLeftBoss1->Render();

	kraid->Render();
	ridley->Render();
}

void World::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	Texture * texture = new Texture();
	LPDIRECT3DTEXTURE9 samus_texture = texture->loadTexture(d3ddv, TEXTURE_GAME_CHARACTERS);
	if (samus_texture == NULL)
		trace(L"Unable to load PlayerTexture");
	samus->InitSprites(d3ddv, samus_texture);

	Texture * texture1 = new Texture();
	LPDIRECT3DTEXTURE9 maru_texture = texture1->loadTexture(d3ddv, ITEM_SPRITE_PATH);
	if (maru_texture == NULL)
		trace(L"Unable to load PlayerTexture");
	maruMari->InitSprites(d3ddv, maru_texture);

	// Bullet Texture
	LPDIRECT3DTEXTURE9 bulletTexture = texture1->loadTexture(d3ddv, SAMUS_BULLET_PATH);
	if (bulletTexture == NULL)
		trace(L"Unable to load BulletTexture");
	for (int i = 0; i < this->samusBullet.size(); i++) {
		this->samusBullet[i]->InitSprites(d3ddv, bulletTexture);
	}

	// Explode Texture
	Texture * textureExplode = new Texture();
	LPDIRECT3DTEXTURE9 explode_texture = textureExplode->loadTexture(d3ddv, EFFECT_SPRITE_PATH);
	if (explode_texture == NULL)
		trace(L"Unable to load Explode Texture");
	explodeEffect->InitSprites(d3ddv, explode_texture);

	// Bomb Texture
	Texture * textureBomb = new Texture();
	LPDIRECT3DTEXTURE9 bomb_texture = textureBomb->loadTexture(d3ddv, BOMB_TEXTURE);
	if (bomb_texture == NULL)
		trace(L"Unable to load Bomb Texture");
	bombWeapon->InitSprites(d3ddv, bomb_texture);
	
	// Enemy Texture
	LPDIRECT3DTEXTURE9 enemyTexture = texture1->loadTexture(d3ddv, ENEMY_SPRITE_PATH);
	//Enemy (Zoomer) Texture
	for (int i = 0; i < this->enemy.size(); i++) {
		this->enemy[i]->InitSprites(d3ddv, enemyTexture);
	}

	// Gate Texture
	Texture * textureGate = new Texture();
	LPDIRECT3DTEXTURE9 gate_texture = textureGate->loadTexture(d3ddv, GATE_SPRITES_PATH);
	if (gate_texture == NULL)
		trace(L"Unable to load Gate Texture");
	gateRightRoom1->InitSprites(d3ddv, gate_texture, GATE_RIGHT);
	gateLeftRoom1->InitSprites(d3ddv, gate_texture, GATE_LEFT);
	gateRightRoom2->InitSprites(d3ddv, gate_texture, GATE_RIGHT);
	gateLeftRoom2->InitSprites(d3ddv, gate_texture, GATE_LEFT);
	gateRightBoss1->InitSprites(d3ddv, gate_texture, GATE_RIGHT);
	gateLeftBoss1->InitSprites(d3ddv, gate_texture, GATE_LEFT);
	
	gateBlockRoom1->InitSprites(d3ddv, gate_texture);
	gateBlockRoom2->InitSprites(d3ddv, gate_texture);
	gateBlockBoss1->InitSprites(d3ddv, gate_texture);

	// Boss Texture
	Texture * textureBoss = new Texture();
	LPDIRECT3DTEXTURE9 boss_texture = textureBoss->loadTexture(d3ddv, BOSS_TEXTURE);
	if (boss_texture == NULL)
		trace(L"Unable to load Boss Texture");
	kraid->InitSprites(d3ddv, boss_texture);
	ridley->InitSprites(d3ddv, boss_texture);
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
			this->setDirectionForZoomer(monster, v[5]);
			monster->setEnemyStatefromString(v[6]);
			break;
		}
		case ZOOMER_PINK_CASE: {
			monster = new Zoomer(spriteHandler, this, ZOOMER_PINK);
			this->setDirectionForZoomer(monster, v[5]);
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
		monster->setInitPosX(stoi(v[3]));
		monster->setPosY(stoi(v[4]));
		monster->setInitPosY(stoi(v[4]));
		monster->setActive(false);
		monster->setVelocityX(0);
		monster->setVelocityY(0);
		this->enemy.push_back(monster);
		v.clear();
		if(monster != NULL)
			metroid->getGrid()->add(monster);
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

Metroid * World::getMetroid()
{
	return this->metroid;
}

void World::setDirectionForZoomer(Enemy* enemy, string str) {
	Zoomer* zoomer = dynamic_cast<Zoomer*>(enemy);
	if (str == "RIGHT") {
		zoomer->setInitDirection(ZOOMER_RIGHT);
	}
	else if (str == "LEFT") {
		zoomer->setInitDirection(ZOOMER_LEFT);
	}
	else if (str == "UP") {
		zoomer->setInitDirection(ZOOMER_UP);
	}
	else if (str == "DOWN") {
		zoomer->setInitDirection(ZOOMER_DOWN);
	}
}