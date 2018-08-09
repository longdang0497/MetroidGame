#include "Metroid.h"
#include <time.h>
#include "trace.h"
#include "utils.h"

void Metroid::_InitBackground()
{
}

void Metroid::_InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	world->InitSprites(d3ddv);	
}

void Metroid::_InitPositions()
{
	//this->map->inputBrickToGrid(this);
	
	for (int i = 0; i < this->map->getStringMap().size(); i++) {
		for (int j = 0; j < this->map->getStringMap()[i].size(); j++) {
			if (this->map->getStringMap()[i][j] != '0'
				&& this->map->getStringMap()[i][j] != 'V'
				&& this->map->getStringMap()[i][j] != 'W') {
				float x = (float)j * 32;
				float y = (float)i * 32;
				Brick * brick = new Brick(x, y, BRICK_SIZE, BRICK_SIZE);
				brick->setIndexX(j);
				brick->setIndexY(i);
				grid->add(brick);
				brick = nullptr;
				delete brick;
			}
		}
	}

	world->samus->InitPostition();
	this->grid->add(this->world->samus);

	world->maruMari->Init(420, 352);
	this->grid->add(this->world->maruMari);

	world->bombWeapon->CreateBomb(0, 0);
	grid->add(world->bombWeapon);
	world->bombWeapon->setActive(false);

	world->explodeEffect->CreateExplode(360, 360);
	grid->add(world->explodeEffect);
	world->explodeEffect->setActive(false);

	world->gateLeft->Init(2224, 160);
	grid->add(world->gateLeft);
	//world->gateRight->Init(2304, 160);
	//grid->add(world->gateRight);
	world->gateBlock->Init(2240, 160);
	grid->add(world->gateBlock);
}

Metroid::Metroid(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate) 
	:Game(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	tick_per_frame = 1000 / _dxgraphics->getFrameRate();

	isOnFloor = false;
	isInGame = false;
	isFreezing = false;

	sound = new GameSound();	

	time_jump = 3 * _DeltaTime;
	time_freezing = TIME_FREEZING;
	time_in_game = TIME_IN_GAME;

	introscreen = NULL;
	startscreen = NULL;
	gameoverscreen = NULL;

	screenMode = GAMEMODE_GAMERUN; // GAMEMODE_INTRO;
}

Metroid::~Metroid()
{
	/*delete(map);
	delete(world);*/
}

/*
	Khoi tao Spritehandler va Texture cho game
*/
void Metroid::LoadResources(LPDIRECT3DDEVICE9 d3ddev)
{
	//---------Khởi tạo spriteHandler---------------
	if (d3ddev == NULL) return;

	HRESULT result = D3DXCreateSprite(d3ddev, &spriteHandler);
	if (result != D3D_OK) 
		trace(L"Unable to create SpriteHandler");

	_texture = texture.loadTexture(d3ddev, BRICK_TEXTURE);
	if (_texture == NULL)
		trace(L"Unable to load BrickTexture");

	// Khoi tao map
	this->map = new Map(this->getSpriteHandler(), _texture, MAP_FULL_ROOM, 0, 0);

	int height = this->map->getRow();
	int width = this->map->getColumn();
	grid = new Grid(height, width);

	world = new World(spriteHandler, this);

	//this->map->setGrid(this->grid);
	
	srand((unsigned)time(NULL));
	this->_InitSprites(d3ddev);
	this->_InitPositions();

	if (camera) 
	{
		camera->Follow(world->samus);
		camera->SetMapBoundary(map->getBoundary());
	}

}

//Kiểm tra screen Mode (bắt đầu, room1, room2,... hay gameover)
void Metroid::Update(float Delta)
{
	switch (screenMode)
	{
		// intro
	case GAMEMODE_INTRO:
		UpdateIntro(Delta);
		break;
		// start screen
	case GAMEMODE_START:
		break;
		// game running
	case GAMEMODE_GAMERUN:
		this->camera->Update(Delta);
		map->UpdateMap(this->camera->getBoundary());
		grid->setDeltaTime(Delta);
		UpdateFrame(Delta);
		break;
		// game over
	case GAMEMODE_GAMEOVER:
	default:
		break;
	}
}

void Metroid::UpdateIntro(float Delta)
{
}

//update các object trong game
void Metroid::UpdateFrame(float Delta)
{
	if (isInGame)
	{
		time_in_game -= Delta;
		if (time_in_game <= 0)
		{
			isInGame = false;
		}
	}

	if (isFreezing)
	{
		time_freezing -= Delta;
		if (time_freezing <= 0)
		{
			isFreezing = false;
			time_freezing = TIME_FREEZING;
		}
		return;
	}

	world->Update(Delta);
	

	if (world->samus->isSamusDeath() == true)
	{
		screenMode = GAMEMODE_GAMEOVER;
		return;
	}
}

//render từng screen mode (room1, room2,... hay gameover)
void Metroid::Render(LPDIRECT3DDEVICE9 d3ddv)
{	
	switch (screenMode)
	{
		// intro
	case GAMEMODE_INTRO:
		//RenderIntro(d3ddv);
		break;
		// start screen
	case GAMEMODE_START:
		//RenderStartScreen(d3ddv);
		break;
		// game running
	case GAMEMODE_GAMERUN:
		RenderFrame(d3ddv);
		break;
		// game over
	case GAMEMODE_GAMEOVER:
		//RenderGameOver(d3ddv);
	default:
		break;
	}
}

void Metroid::RenderIntro(LPDIRECT3DDEVICE9 d3ddv)
{
	// Background
	d3ddv->StretchRect(
		introscreen,		// from 
		NULL,				// which portion?
		_device->getBuffer(),		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);
	introscreen = CreateSurfaceFromFile(_device->getdevice(), INTROSCREEN_FILE);
}

//render các scene chính (room1, room2...) trong game
void Metroid::RenderStartScreen(LPDIRECT3DDEVICE9 d3ddv)
{
	// Start screen
	d3ddv->StretchRect(
		startscreen,		// from 
		NULL,				// which portion?
		_device->getBuffer(),		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);
	startscreen = CreateSurfaceFromFile(d3ddv, STARTSCREEN_FILE);
}

void Metroid::RenderGameOver(LPDIRECT3DDEVICE9 d3ddv)
{
	d3ddv->StretchRect(
		gameoverscreen,		// from 
		NULL,				// which portion?
		_device->getBuffer(),		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);
	gameoverscreen = CreateSurfaceFromFile(d3ddv, GAMEOVERSCREEN_FILE);
}

//render từng object trong game
void Metroid::RenderFrame(LPDIRECT3DDEVICE9 d3ddv)
{
	map->drawMap();
	world->Render();
}

void Metroid::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta)
{
	if (_input->IsKeyDown(DIK_RIGHT))
	{
		world->samus->setVelocityXLast(world->samus->getVelocityX());
		world->samus->setVelocityX(SAMUS_SPEED);
		if (!this->world->samus->getIsBall()) {
			if (world->samus->GetState() != MORPH_LEFT && world->samus->GetState() != MORPH_RIGHT
				&& world->samus->GetState() != JUMP_LEFT && world->samus->GetState() != JUMP_RIGHT
				&& world->samus->GetState() != JUMP_SHOOT_UP_LEFT && world->samus->GetState() != JUMP_SHOOT_UP_RIGHT
				&& world->samus->GetState() != TRANSFORM_BALL_LEFT && world->samus->GetState() != TRANSFORM_BALL_RIGHT)
			{
				world->samus->SetState(RUNNING_RIGHT);

				for (int i = 0; i < this->world->samusBullet.size(); i++) {
					if (!this->world->samusBullet[i]->getIsRendered()) {
						this->world->samusBullet[i]->setDirection(SHOOT_RIGHT);
						break;
					}
				}
			}
		}
	}
	else if (_input->IsKeyDown(DIK_LEFT)) {
		world->samus->setVelocityXLast(world->samus->getVelocityX());
		world->samus->setVelocityX(-SAMUS_SPEED);
		if (!this->world->samus->getIsBall()) {
			if (world->samus->GetState() != MORPH_LEFT && world->samus->GetState() != MORPH_RIGHT
				&& world->samus->GetState() != JUMP_LEFT && world->samus->GetState() != JUMP_RIGHT
				&& world->samus->GetState() != JUMP_SHOOT_UP_LEFT && world->samus->GetState() != JUMP_SHOOT_UP_RIGHT
				&& world->samus->GetState() != TRANSFORM_BALL_LEFT && world->samus->GetState() != TRANSFORM_BALL_RIGHT)
			{
				world->samus->SetState(RUNNING_LEFT);
				for (int i = 0; i < this->world->samusBullet.size(); i++) {
					if (!this->world->samusBullet[i]->getIsRendered()) {
						this->world->samusBullet[i]->setDirection(SHOOT_LEFT);
						break;
					}
				}
			}
		}
	}
	else
	{
		world->samus->setVelocityX(0);
		if (!this->world->samus->getIsBall()) {
			if (world->samus->getVelocityXLast() > 0)
			{
				if (world->samus->GetState() != MORPH_LEFT && world->samus->GetState() != MORPH_RIGHT
					&& world->samus->GetState() != JUMP_LEFT && world->samus->GetState() != JUMP_RIGHT
					&& world->samus->GetState() != JUMP_SHOOT_UP_LEFT && world->samus->GetState() != JUMP_SHOOT_UP_RIGHT
					&& world->samus->GetState() != TRANSFORM_BALL_LEFT && world->samus->GetState() != TRANSFORM_BALL_RIGHT)
				{
					world->samus->SetState(STAND_RIGHT);
					
					for (int i = 0; i < this->world->samusBullet.size(); i++) {
						if (!this->world->samusBullet[i]->getIsRendered()) {
							this->world->samusBullet[i]->setDirection(SHOOT_RIGHT);
							break;
						}
					}
				}
			}
			else if (world->samus->getVelocityXLast() < 0)
			{
				if (world->samus->GetState() != MORPH_LEFT && world->samus->GetState() != MORPH_RIGHT
					&& world->samus->GetState() != JUMP_LEFT && world->samus->GetState() != JUMP_RIGHT
					&& world->samus->GetState() != JUMP_SHOOT_UP_LEFT && world->samus->GetState() != JUMP_SHOOT_UP_RIGHT
					&& world->samus->GetState() != TRANSFORM_BALL_LEFT && world->samus->GetState() != TRANSFORM_BALL_RIGHT && !world->samus->getIsBall())
				{
					world->samus->SetState(STAND_LEFT);
					
					for (int i = 0; i < this->world->samusBullet.size(); i++) {
						if (!this->world->samusBullet[i]->getIsRendered()) {
							this->world->samusBullet[i]->setDirection(SHOOT_LEFT);
							break;
						}
					}
				}

			}
		}
	}

	

	if (_input->IsKeyDown(DIK_UP))
	{
		if (world->samus->GetState() == RUNNING_LEFT)
		{
			world->samus->SetState(RUN_SHOOT_UP_LEFT);
			for (int i = 0; i < this->world->samusBullet.size(); i++) {
				if (!this->world->samusBullet[i]->getIsRendered()) {
					this->world->samusBullet[i]->setDirection(SHOOT_UP_LEFT);
					break;
				}
			}
		}
		if (world->samus->GetState() == RUNNING_RIGHT)
		{
			world->samus->SetState(RUN_SHOOT_UP_RIGHT);
			
			for (int i = 0; i < this->world->samusBullet.size(); i++) {
				if (!this->world->samusBullet[i]->getIsRendered()) {
					this->world->samusBullet[i]->setDirection(SHOOT_UP_RIGHT);
					break;
				}
			}
		}
		if (world->samus->GetState() == STAND_LEFT)
		{
			world->samus->SetState(STAND_SHOOT_UP_LEFT);
			for (int i = 0; i < this->world->samusBullet.size(); i++) {
				if (!this->world->samusBullet[i]->getIsRendered()) {
					this->world->samusBullet[i]->setDirection(SHOOT_UP_LEFT);
					break;
				}
			}
		}
		if (world->samus->GetState() == STAND_RIGHT)
		{
			world->samus->SetState(STAND_SHOOT_UP_RIGHT);
			
			for (int i = 0; i < this->world->samusBullet.size(); i++) {
				if (!this->world->samusBullet[i]->getIsRendered()) {
					this->world->samusBullet[i]->setDirection(SHOOT_UP_RIGHT);
					break;
				}
			}
		}
		if (world->samus->GetState() == JUMP_LEFT)
		{
			world->samus->SetState(JUMP_SHOOT_UP_LEFT);
			
			for (int i = 0; i < this->world->samusBullet.size(); i++) {
				if (!this->world->samusBullet[i]->getIsRendered()) {
					this->world->samusBullet[i]->setDirection(SHOOT_LEFT);
					break;
				}
			}
		}
		if (world->samus->GetState() == JUMP_RIGHT)
		{
			world->samus->SetState(JUMP_SHOOT_UP_RIGHT);
			
			for (int i = 0; i < this->world->samusBullet.size(); i++) {
				if (!this->world->samusBullet[i]->getIsRendered()) {
					this->world->samusBullet[i]->setDirection(SHOOT_RIGHT);
					break;
				}
			}
		}
		if (world->samus->GetState() == MORPH_LEFT)
		{
			world->samus->SetState(STAND_LEFT);
			
			for (int i = 0; i < this->world->samusBullet.size(); i++) {
				if (!this->world->samusBullet[i]->getIsRendered()) {
					this->world->samusBullet[i]->setDirection(SHOOT_LEFT);
					break;
				}
			}
		}
		if (world->samus->GetState() == MORPH_RIGHT)
		{
			world->samus->SetState(STAND_RIGHT);
			
			for (int i = 0; i < this->world->samusBullet.size(); i++) {
				if (!this->world->samusBullet[i]->getIsRendered()) {
					this->world->samusBullet[i]->setDirection(SHOOT_RIGHT);
					break;
				}
			}
		}
		if (world->samus->GetState() == TRANSFORM_BALL_RIGHT) {
			world->samus->SetState(STAND_RIGHT);
			world->samus->setIsBall(false);
			this->world->samus->setPosY(this->world->samus->getPosY() - 32);
			
			for (int i = 0; i < this->world->samusBullet.size(); i++) {
				if (!this->world->samusBullet[i]->getIsRendered()) {
					this->world->samusBullet[i]->setDirection(SHOOT_RIGHT);
					break;
				}
			}
		}
		if (world->samus->GetState() == TRANSFORM_BALL_LEFT) {
			this->world->samus->setPosY(this->world->samus->getPosY() - 32);
			world->samus->setIsBall(false);
			world->samus->SetState(STAND_LEFT);

			for (int i = 0; i < this->world->samusBullet.size(); i++) {
				if (!this->world->samusBullet[i]->getIsRendered()) {
					this->world->samusBullet[i]->setDirection(SHOOT_LEFT);
					break;
				}
			}
		}
	}
	else if (_input->IsKeyDown(DIK_DOWN)) {
		if (this->world->samus->GetState() == STAND_LEFT) {
			this->world->samus->setPosY(this->world->samus->getPosY() + 32);
			this->world->samus->SetState(TRANSFORM_BALL_LEFT);
			for (int i = 0; i < this->world->samusBullet.size(); i++) {
				if (!this->world->samusBullet[i]->getIsRendered()) {
					this->world->samusBullet[i]->setDirection(OFF);
					break;
				}
			}

			this->world->samus->setIsBall(true);
		}
		else if(this->world->samus->GetState() == STAND_RIGHT){
			this->world->samus->setPosY(this->world->samus->getPosY() + 32);
			this->world->samus->SetState(TRANSFORM_BALL_RIGHT);
			for (int i = 0; i < this->world->samusBullet.size(); i++) {
				if (!this->world->samusBullet[i]->getIsRendered()) {
					this->world->samusBullet[i]->setDirection(OFF);
					break;
				}
			}
			this->world->samus->setIsBall(true);
		}
	}
	
	// Xử lý các sự kiện bắn, nhảy
	// Z: bắn
	// X: nhảy
	if (_input->IsKeyDown(DIK_Z)) {
		for (int i = 0; i < this->world->samusBullet.size(); i++) {
			if (i == 0) {
				if (!this->world->samusBullet[2]->getIsRendered() || this->world->samusBullet[2]->getCount() > 2 && this->world->samusBullet[2]->getIsRendered()) {
					this->world->samusBullet[0]->setActive(true);
				}
			}
			else {
				if (this->world->samusBullet[i - 1]->getIsRendered() && this->world->samusBullet[i - 1]->getCount() > 2) {
					this->world->samusBullet[i]->setActive(true);
				}
			}
		}
		if (this->world->samus->GetState() == RUNNING_RIGHT) {
			this->world->samus->SetState(RUN_SHOOTING_RIGHT);
		}
		else if (this->world->samus->GetState() == RUNNING_LEFT) {
			this->world->samus->SetState(RUN_SHOOTING_LEFT);
		}
	}
		
	if (_input->IsKeyDown(DIK_X) && world->samus->getJump() == true)
	{
		world->samus->setlastPosY(world->samus->getPosY());
		if (world->samus->getJump() == true)
		{
			world->samus->setFall(true);
			world->samus->setVelocityY(world->samus->getVelocityY() - JUMP_VELOCITY_BOOST_FIRST * Delta);
			//if (world->samus->getPosY() == world->samus->getlastPosY() - 160)
				//world->samus->setVelocityY(world->samus->getVelocityY() - JUMP_VELOCITY_BOOST * Delta);
			world->samus->setJump(false);

			if (world->samus->getVelocityXLast() > 0)
				world->samus->SetState(JUMP_RIGHT);
			else if (world->samus->getVelocityXLast() < 0)
				world->samus->SetState(JUMP_LEFT);

			if (world->samus->GetState() != MORPH_RIGHT && _input->IsKeyDown(DIK_RIGHT))
				world->samus->SetState(MORPH_RIGHT);
			if (world->samus->GetState() != MORPH_LEFT && _input->IsKeyDown(DIK_LEFT))
				world->samus->SetState(MORPH_LEFT);

			if (world->samus->getVelocityXLast() < 0)
			{
				if (world->samus->GetState() != JUMP_LEFT && world->samus->GetState() != MORPH_LEFT
					&& world->samus->GetState() != JUMP_SHOOT_UP_LEFT)
				{
					if (world->samus->GetState() == STAND_SHOOT_UP_LEFT)
						world->samus->SetState(JUMP_SHOOT_UP_LEFT);
					else
						world->samus->SetState(JUMP_LEFT);
				}
			}
			if (world->samus->getVelocityXLast() > 0)
			{
				if (world->samus->GetState() != JUMP_RIGHT && world->samus->GetState() != MORPH_RIGHT
					&& world->samus->GetState() != JUMP_SHOOT_UP_RIGHT)
				{
					if (world->samus->GetState() == STAND_SHOOT_UP_RIGHT)
						world->samus->SetState(JUMP_SHOOT_UP_RIGHT);
					else
						world->samus->SetState(JUMP_RIGHT);
				}
			}
		}
	}
}

void Metroid::OnKeyDown(int KeyCode)
{
	switch (screenMode)
	{
		// intro
		case GAMEMODE_INTRO:
		{
			if (KeyCode == DIK_RETURN)
			{
				screenMode = GAMEMODE_START;
			}
			break;
		}
		// start screen
		case GAMEMODE_START://------------------------------------------------
		{
			if (KeyCode == DIK_RETURN)
			{
				screenMode = GAMEMODE_GAMERUN;
				//sound->Stopsound(intro);
				/*CSound * appear = sound->LoadSound(APPEARING_SOUND);
				if (appear != NULL)
				sound->Loopsound(appear);*/
				isInGame = true;
			}
			break;
		}		
		// game running
		case GAMEMODE_GAMERUN:// -------------------------------------------------
		{
			switch (KeyCode)
			{
			case DIK_SPACE:
				if (_input->IsKeyDown(DIK_SPACE) && world->bombWeapon->getBombExplode() == true)
				{
					world->bombWeapon->setActive(true);
					world->bombWeapon->setTimeSurvive(3);
					world->bombWeapon->setBombExplode(false);

					float xpos = world->samus->getPosX();
					float ypos = world->samus->getPosY();
					float bombPosX = xpos + world->samus->getWidth() / 2;
					float bombPosY = ypos + world->samus->getHeight() / 2;
					world->bombWeapon->setPosX(bombPosX);
					world->bombWeapon->setPosY(bombPosY);
				}
				break;
			case DIK_X:

				break;
			case DIK_LEFT:
				if (world->samus->GetState() == MORPH_RIGHT)
					world->samus->SetState(MORPH_LEFT);
				break;
			case DIK_RIGHT:
				if (world->samus->GetState() == MORPH_LEFT)
					world->samus->SetState(MORPH_RIGHT);
				break;
			case DIK_DOWN:
				if (_input->IsKeyDown(DIK_DOWN)) {
					if (this->world->samus->GetState() == STAND_LEFT) {
						this->world->samus->setlastPosY(this->world->samus->getPosY());
						this->world->samus->setPosY(this->world->samus->getPosY() + 32);
						this->world->samus->SetState(TRANSFORM_BALL_LEFT);
						if (_input->IsKeyDown(DIK_RIGHT))
						{
							world->samus->setVelocityXLast(world->samus->getVelocityX());
							world->samus->setVelocityX(SAMUS_SPEED);
						}
						else if (_input->IsKeyDown(DIK_LEFT))
						{
							world->samus->setVelocityXLast(world->samus->getVelocityX());
							world->samus->setVelocityX(-SAMUS_SPEED);
						}

						for (int i = 0; i < this->world->samusBullet.size(); i++) {
							if (!this->world->samusBullet[i]->getIsRendered()) {
								this->world->samusBullet[i]->setDirection(OFF);
								break;
							}
						}

						this->world->samus->setIsBall(true);
					}
					else if (this->world->samus->GetState() == STAND_RIGHT) {
						this->world->samus->setPosY(this->world->samus->getPosY() + 32);
						this->world->samus->SetState(TRANSFORM_BALL_RIGHT);
						for (int i = 0; i < this->world->samusBullet.size(); i++) {
							if (!this->world->samusBullet[i]->getIsRendered()) {
								this->world->samusBullet[i]->setDirection(OFF);
								break;
							}
						}
						this->world->samus->setIsBall(true);
					}
				}
				else {
					world->samus->setPosY(world->samus->getlastPosY());
				}
				break;
			}
		}
		break;
		// game over
		case GAMEMODE_GAMEOVER://------------------------------------------------
		{
			if (KeyCode == DIK_RETURN)
			{
				screenMode = GAMEMODE_INTRO;
				//world->samus->Reset(1275, 150);
			}
			break;
		}
	}
}

void Metroid::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_Z:
	{
		for (int i = 0; i < this->world->samusBullet.size(); i++) {
			this->world->samusBullet[i]->setActive(false);
			if (!this->world->samusBullet[i]->getIsRendered()) {
				this->world->samusBullet[i]->Reset();
			}
		}
		break;
	}
	case DIK_DOWN:
		world->samus->setPosY(world->samus->getlastPosY());
		break;
	}
}

DWORD Metroid::GetTickPerFrame()
{
	return tick_per_frame;
}

LPD3DXSPRITE Metroid::getSpriteHandler() {
	return this->spriteHandler;
}

Map * Metroid::getMap() {
	return map;
}

Grid * Metroid::getGrid()
{
	return this->grid;
}
