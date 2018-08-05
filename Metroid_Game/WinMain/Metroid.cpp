﻿#include "Metroid.h"

void Metroid::_InitBackground()
{
}

void Metroid::_InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	world->InitSprites(d3ddv);	
}

void Metroid::_InitPositions()
{
	world->samus->InitPostition();
	world->grid->add(world->samus);

	world->maruMari->Init(420, 352);
	world->grid->add(world->maruMari);

	world->itemBomb->Init(1056, 352);
	world->grid->add(world->itemBomb);

	world->bomb->CreateBomb(0, 0);
	world->grid->add(world->bomb);
	world->bomb->setActive(false);

	world->explode->CreateExplode(360, 360);
	world->grid->add(world->explode);
	world->explode->setActive(false);

	/*world->gateLeft->Init(2224, 160);
	world->gateLeft->grid->add(world->gateLeft);
	world->gateRight->Init(2304, 160);
	world->gateRight->grid->add(world->gateRight);

	world->gateBlock->Init(2240, 160);
	world->gateBlock->grid->add(world->gateBlock);*/
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

	roomNum = ROOM1;
}

Metroid::~Metroid()
{
	delete(mapRoom1);
	delete(mapRoom2);
	delete(mapRoom3);
	delete(mapStair);
	delete(world);
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

	loadMap1 = new Loader(MAP_ROOM1);
	loadMap2 = new Loader(MAP_ROOM2);
	loadMap3 = new Loader(MAP_ROOM3);
	loadStair = new Loader(MAP_STAIR);

	// Khoi tao map
	mapRoom1 = new Map(this->getSpriteHandler(), MAP_ROOM1, 0, 0);
	mapRoom1->setLimitation(loadMap1->getCol(), loadMap1->getRow());

	/*int topRoom2 = this->mapRoom1->getBoundary().top - this->loadMap2->getRow() * 32;
	int leftRoom2 = this->mapRoom1->getBoundary().right - this->loadMap2->getCol() * 32;
	int topRoom3 = this->mapRoom1->getBoundary().top - topRoom2 - this->loadMap3->getRow() * 32;
	int leftRoom3 = this->mapRoom1->getBoundary().right - this->loadMap3->getCol() * 32;
	int topStair = this->mapRoom1->getBoundary().bottom - this->loadStair->getRow() * 32;
	int leftStair = this->mapRoom1->getBoundary().right;

	mapRoom2 = new Map(this->getSpriteHandler(), MAP_ROOM2, topRoom2, leftRoom2);
	mapRoom2->setLimitation(loadMap2->getCol(), loadMap2->getRow());

	mapRoom3 = new Map(this->getSpriteHandler(), MAP_ROOM3, topRoom3, leftRoom3);
	mapRoom3->setLimitation(loadMap3->getCol(), loadMap3->getRow());

	mapStair = new Map(this->getSpriteHandler(), MAP_STAIR, topStair, leftStair);
	mapStair->setLimitation(loadStair->getCol(), loadStair->getRow());
*/

	int gridHeight = 0, gridWidth = 0;
	switch (roomNum) {
	case ROOM1:
		gridHeight = this->loadMap1->getRow();
		gridWidth = this->loadMap1->getCol();
		break;
	case ROOM2:
		//gridHeight = this->loadMap2->getRow();
		//gridWidth = this->loadMap2->getCol();
		break;
	case ROOM3:
		//gridHeight = this->loadMap3->getRow();
		//gridWidth = this->loadMap3->getCol();
		break;
	case STAIR:
		//gridHeight = this->loadStair->getRow();
		//gridWidth = this->loadStair->getCol();
		break;
	}
	world = new World(spriteHandler, this, gridWidth, gridWidth);

	this->mapRoom1->setGrid(world->grid);
	this->mapRoom1->inputBrickToGrid();

	/*this->mapRoom2->setGrid(world->grid);
	this->mapRoom2->inputBrickToGrid();

	this->mapRoom3->setGrid(world->grid);
	this->mapRoom3->inputBrickToGrid();

	this->mapStair->setGrid(world->grid);
	this->mapStair->inputBrickToGrid();*/

	srand((unsigned)time(NULL));
	this->_InitSprites(d3ddev);
	this->_InitPositions();

	if (camera) 
	{
		camera->Follow(world->samus);
		camera->SetMapBoundary(mapRoom1->getBoundary());
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
		this->camera->Update();
		switch (roomNum) {
		case ROOM1:
			mapRoom1->UpdateMap(this->camera->getBoundary());
			break;
		case ROOM2:
			//mapRoom2->UpdateMap(this->camera->getBoundary());
			break;
		case ROOM3:
			//mapRoom3->UpdateMap(this->camera->getBoundary());
			break;
		case STAIR:
			//mapStair->UpdateMap(this->camera->getBoundary());
			break;
		}
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
	switch (roomNum) {
	case ROOM1:
		mapRoom1->drawMap();
		break;
	case ROOM2:
		//mapRoom2->drawMap();
		break;
	case ROOM3:
		//mapRoom3->drawMap();
		break;
	case STAIR:
		//mapStair->drawMap();
		break;
	}
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
			switch (KeyCode) {
			case DIK_SPACE:
				if (_input->IsKeyDown(DIK_SPACE) && world->bomb->getBombExplode() == true)
				{
					world->bomb->setActive(true);
					world->bomb->setTimeSurvive(3);
					world->bomb->setBombExplode(false);

					float xpos = world->samus->getPosX();
					float ypos = world->samus->getPosY();
					float bombPosX = xpos + world->samus->currentSprite->getWidth() / 2;
					float bombPosY = ypos + world->samus->currentSprite->getHeight() / 2;
					world->bomb->setPosX(bombPosX);
					world->bomb->setPosY(bombPosY);
				}
				break;
			case DIK_DOWN:
				if (_input->IsKeyDown(DIK_DOWN)) {
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
				break;
			case DIK_X:
				if (_input->IsKeyDown(DIK_X) && world->samus->canJump == true)
				{
					world->samus->canJump = true;
					if (world->samus->getVelocityY() > MAX_VELOCITY_Y)
						world->samus->setVelocityY(MAX_VELOCITY_Y);
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
				this->world->samusBullet[i]->setCount(0);
			}
		}
	}
	}
}

DWORD Metroid::GetTickPerFrame()
{
	return tick_per_frame;
}

LPD3DXSPRITE Metroid::getSpriteHandler() {
	return this->spriteHandler;
}

Map * Metroid::getMapRoom1() {
	return this->mapRoom1;
}

Map * Metroid::getMapRoom2()
{
	return this->mapRoom2;
}

Map * Metroid::getMapRoom3()
{
	return this->mapRoom3;
}

Map * Metroid::getMapStair()
{
	return this->mapStair;
}

ROOM_NUMBER Metroid::getRoomNum()
{
	return roomNum;
}

void Metroid::setRoomNum(ROOM_NUMBER value)
{
	roomNum = value;
}
