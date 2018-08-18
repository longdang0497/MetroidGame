#include "World.h"
World::World()
{
}

World::World(LPD3DXSPRITE spriteHandler, Metroid * metroid)
{
	this->spriteHandler = spriteHandler;
	this->metroid = metroid;

	//Khởi tạo các đối tượng trong World
	samus = new Samus(spriteHandler, this, this->getMetroid()->getGrid());
	
	// Khởi tạo đạn (3 viên)
	Bullet *bullet1 = new Bullet(spriteHandler, this->getMetroid()->getGrid());
	Bullet *bullet2 = new Bullet(spriteHandler, this->getMetroid()->getGrid());
	Bullet *bullet3 = new Bullet(spriteHandler, this->getMetroid()->getGrid());
	this->samusBullet.push_back(bullet1);
	this->samusBullet.push_back(bullet2);
	this->samusBullet.push_back(bullet3);

	// Khoi tao Bullet Skree (4 vien)
	BulletSkree* bulletKree1 = new BulletSkree(spriteHandler, this, BULLET_RIGHT);
	BulletSkree* bulletKree2 = new BulletSkree(spriteHandler, this, BULLET_LEFT);
	BulletSkree* bulletKree3 = new BulletSkree(spriteHandler, this, BULLET_TOPLEFT);
	BulletSkree* bulletKree4 = new BulletSkree(spriteHandler, this, BULLET_TOPRIGHT);
	this->skreeBullet.push_back(bulletKree1);
	this->skreeBullet.push_back(bulletKree2);
	this->skreeBullet.push_back(bulletKree3);
	this->skreeBullet.push_back(bulletKree4);

	// Khoi tao dan cua Kraid (3 vien)
	BulletKraid* kraidBullet3 = new BulletKraid(spriteHandler, this);
	kraidBullet3->pos_y = 202.0f;
	BulletKraid* kraidBullet1 = new BulletKraid(spriteHandler, this);
	kraidBullet1->pos_y = 232.0f;
	BulletKraid* kraidBullet2 = new BulletKraid(spriteHandler, this);
	kraidBullet2->pos_y = 262.0f;
	this->kraidBullet.push_back(kraidBullet3);
	this->kraidBullet.push_back(kraidBullet1);
	this->kraidBullet.push_back(kraidBullet2);

	// Khoi tao boomerange cua kraid (2 vien)
	KraidBoomerang* boomerang1 = new KraidBoomerang(spriteHandler, this);
	KraidBoomerang* boomerang2 = new KraidBoomerang(spriteHandler, this);
	kraidBomerang.push_back(boomerang1);
	kraidBomerang.push_back(boomerang2);

	// Khoi tao dan cho ridley (5 vien)
	BulletRidley* ridleyBullet1 = new BulletRidley(spriteHandler, this);
	BulletRidley* ridleyBullet2 = new BulletRidley(spriteHandler, this);
	BulletRidley* ridleyBullet3 = new BulletRidley(spriteHandler, this);
	BulletRidley* ridleyBullet4 = new BulletRidley(spriteHandler, this);
	BulletRidley* ridleyBullet5 = new BulletRidley(spriteHandler, this);
	this->ridleyBullet.push_back(ridleyBullet1);
	this->ridleyBullet.push_back(ridleyBullet2);
	this->ridleyBullet.push_back(ridleyBullet3);
	this->ridleyBullet.push_back(ridleyBullet4);
	this->ridleyBullet.push_back(ridleyBullet5);

	maruMari = new MaruMari(spriteHandler, this);

	explodeEffect = new ExplodeEffect(spriteHandler, this, this->getMetroid()->getGrid());
	bombWeapon = new BombWeapon(spriteHandler, this);

	missible = new Missible(spriteHandler, this);

	gateRightRoom1 = new Gate(spriteHandler, this);
	gateLeftRoom1 = new Gate(spriteHandler, this);
	gateRightRoom2 = new Gate(spriteHandler, this);
	gateLeftRoom2 = new Gate(spriteHandler, this);
	gateRightBoss1 = new Gate(spriteHandler, this);
	gateLeftBoss1 = new Gate(spriteHandler, this);

	gateBlockRoom1 = new GateBlock(spriteHandler, this, metroid->getGrid());
	gateBlockRoom2 = new GateBlock(spriteHandler, this, metroid->getGrid());
	gateBlockBoss1 = new GateBlock(spriteHandler, this, metroid->getGrid());

	loadEnemyPositions("Monster_Room1.txt");

	ridley = new Ridley(spriteHandler, this);
	kraid = new Kraid(spriteHandler, this);
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

	for (int i = 0; i < this->skreeBullet.size(); i++) {
		this->skreeBullet[i]->Update(t);
	}

	for (int i = 0; i < this->kraidBullet.size(); i++) {
		this->kraidBullet[i]->Update(t);
	}

	for (int i = 0; i < this->kraidBomerang.size(); i++) {
		this->kraidBomerang[i]->Update(t);
	}

	for (int i = 0; i < this->ridleyBullet.size(); i++) {
		this->ridleyBullet[i]->Update(t);
	}

	/*START UPDATING ENEMY*/
	for (int i = 0; i < this->enemy.size(); i++) {
		if (this->enemy[i]->isInsideMapBound(this->metroid->camera->getBoundary())) {
			if (!this->enemy[i]->isActive) {
				if (this->enemy[i]->isDeath) {
				}
				else {
					enemy[i]->isActive = true;
				}

			}
			else if (this->enemy[i]->isActive && !this->enemy[i]->isDeath) {
				if (enemy[i]->getType() == SKREE) {
					enemy[i]->setSamusLocation(this->samus->pos_x, this->samus->pos_y);
				}
				enemy[i]->Update(t);
				
			}
		}
		else {
			// chet sau 15s ms mo lai
			if (GetTickCount() - enemy[i]->getTimeStartDie() >= 15000) {
				this->enemy[i]->isDeath = false;
				this->enemy[i]->health = 100.0f;
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

	this->missible->Update(t);
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

	for (int i = 0; i < this->skreeBullet.size(); i++) {
		this->skreeBullet[i]->Render();
	}

	for (int i = 0; i < this->kraidBullet.size(); i++) {
		this->kraidBullet[i]->Render();
	}

	for (int i = 0; i < this->kraidBomerang.size(); i++) {
		this->kraidBomerang[i]->Render();
	}

	for (int i = 0; i < this->ridleyBullet.size(); i++) {
		this->ridleyBullet[i]->Render();
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

	ridley->Render();
	kraid->Render();

	this->missible->Render();
}

void World::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	Texture * texture = new Texture();
	LPDIRECT3DTEXTURE9 samus_texture = texture->loadTexture(d3ddv, TEXTURE_GAME_CHARACTERS);
	samus->InitSprites(d3ddv, samus_texture);

	LPDIRECT3DTEXTURE9 maru_texture = texture->loadTexture(d3ddv, ITEM_SPRITE_PATH);
	maruMari->InitSprites(d3ddv, maru_texture);

	// Bullet Texture
	LPDIRECT3DTEXTURE9 bulletTexture = texture->loadTexture(d3ddv, SAMUS_BULLET_PATH);
	for (int i = 0; i < this->samusBullet.size(); i++) {
		this->samusBullet[i]->InitSprites(d3ddv, bulletTexture);
	}

	// Explode Texture
	LPDIRECT3DTEXTURE9 explode_texture = texture->loadTexture(d3ddv, EFFECT_SPRITE_PATH);
	explodeEffect->InitSprites(d3ddv, explode_texture);

	// Bomb Texture
	LPDIRECT3DTEXTURE9 bomb_texture = texture->loadTexture(d3ddv, BOMB_TEXTURE);
	bombWeapon->InitSprites(d3ddv, bomb_texture);
	
	// Enemy Texture
	LPDIRECT3DTEXTURE9 enemyTexture = texture->loadTexture(d3ddv, ENEMY_SPRITE_PATH);
	for (int i = 0; i < this->enemy.size(); i++) {
		enemy[i]->InitSprites(d3ddv, enemyTexture);
	}
	for (int i = 0; i < this->skreeBullet.size(); i++) {
		skreeBullet[i]->InitSprites(d3ddv, enemyTexture);
	}

	// Gate Texture
	LPDIRECT3DTEXTURE9 gate_texture = texture->loadTexture(d3ddv, GATE_SPRITES_PATH);
	gateRightRoom1->InitSprites(d3ddv, gate_texture, GATE_RIGHT);
	gateLeftRoom1->InitSprites(d3ddv, gate_texture, GATE_LEFT);
	gateRightRoom2->InitSprites(d3ddv, gate_texture, GATE_RIGHT);
	gateLeftRoom2->InitSprites(d3ddv, gate_texture, GATE_LEFT);
	gateRightBoss1->InitSprites(d3ddv, gate_texture, GATE_RIGHT);
	gateLeftBoss1->InitSprites(d3ddv, gate_texture, GATE_LEFT);

	gateBlockRoom1->InitSprites(d3ddv, gate_texture);
	gateBlockRoom2->InitSprites(d3ddv, gate_texture);
	gateBlockBoss1->InitSprites(d3ddv, gate_texture);

	// boss texture
	LPDIRECT3DTEXTURE9 boss_texture = texture->loadTexture(d3ddv, BOSS_TEXTURE);
	ridley->InitSprites(d3ddv, boss_texture);
	kraid->InitSprites(d3ddv, boss_texture);
	
	for (int i = 0; i < this->kraidBullet.size(); i++) {
		this->kraidBullet[i]->InitSprites(d3ddv, boss_texture);
	}
	for (int i = 0; i < this->kraidBomerang.size(); i++) {
		this->kraidBomerang[i]->InitSprites(d3ddv, boss_texture);
	}
	for (int i = 0; i < this->ridleyBullet.size(); i++) {
		this->ridleyBullet[i]->InitSprites(d3ddv, boss_texture);
	}

	// Missible Texture
	LPDIRECT3DTEXTURE9 missible_texture = texture->loadTexture(d3ddv, MISSIBLE_PATH);
	this->missible->InitSprites(d3ddv, missible_texture);

	texture = nullptr;
	delete(texture);
}

void World::loadEnemyPositions(string filePath) {
	ifstream file_txt(filePath);
	string str;
	vector<string> v;
	while (getline(file_txt, str)) {
		v = split(str, "\t");
		Enemy *monster = nullptr;
		int value = atoi(v[0].c_str());
		switch (value)
		{
		case ZOOMER_CASE: {
			monster = new Zoomer(spriteHandler, this, ZOOMER_YELLOW);
			this->setDirectionForZoomer(monster, v[5]);
			monster->setEnemyStatefromString(v[6]);
			
			break;
		}
		case SKREE_CASE: {
			monster = new Skree(spriteHandler, this, SKREE);
			break;
		}
		default:
			break;
		}
		if (monster != nullptr) {
			monster->setPosX(stoi(v[3]));
			monster->setInitPosX(stoi(v[3]));
			monster->setPosY(stoi(v[4]));
			monster->setInitPosY(stoi(v[4]));
			monster->setActive(false);
			monster->setVelocityX(0);
			monster->setVelocityY(0);
			this->enemy.push_back(monster);
			v.clear();
			this->getMetroid()->getGrid()->add(monster);
		}
			
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
		zoomer->setDirection(ZOOMER_RIGHT);
	}
	else if (str == "LEFT") {
		zoomer->setDirection(ZOOMER_LEFT);
	}
	else if (str == "UP") {
		zoomer->setDirection(ZOOMER_UP);
	}
	else if (str == "DOWN") {
		zoomer->setDirection(ZOOMER_DOWN);
	}
	zoomer->setInitDirection(zoomer->getDirection());
}