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
	world->samus->InitPostition();
	world->maruMari->Init(420, 290);
	world->grid->add(world->maruMari);

	world->itemBomb->Init(1056, 352);
	world->grid->add(world->itemBomb);

	world->bomb->CreateBomb(0, 0);
	world->grid->add(world->bomb);
	world->bomb->setActive(false);

	world->explode->CreateExplode(360, 360);
	world->grid->add(world->explode);
	world->explode->setActive(false);

	world->gateLeft->Init(2224, 160);
	world->gateLeft->grid->add(world->gateLeft);
	world->gateRight->Init(2304, 160);
	world->gateRight->grid->add(world->gateRight);

	world->gateBlock->Init(2240, 160);
	world->gateBlock->grid->add(world->gateBlock);
}

Metroid::Metroid(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate) 
	:Game(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	tick_per_frame = 1000 / _dxgraphics->getFrameRate();

	isOnFloor = false;
	isInGame = false;
	isFreezing = false;

	sound = new GameSound();	
	collision = new Collision();

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
	delete(map);
	delete(world);
}

/*
	Khoi tao Spritehandler cho game
*/
void Metroid::LoadResources(LPDIRECT3DDEVICE9 d3ddev)
{
	//---------Khởi tạo spriteHandler---------------
	if (d3ddev == NULL) return;

	HRESULT result = D3DXCreateSprite(d3ddev, &spriteHandler);
	if (result != D3D_OK) 
		trace(L"Unable to create SpriteHandler");

	/*bool check = sound->Init(_dxgraphics->getWnd());
	if (!check)
	{
		MessageBox(_dxgraphics->getWnd(), L"Error initialize sound !", L"Error", MB_OK);
	}

	CSound * intro = sound->LoadSound(GAME_INTRO_SOUND);
	if (intro != NULL)
		sound->Loopsound(intro);*/
	
	world = new World(spriteHandler, this);
	srand((unsigned)time(NULL));
	this->_InitSprites(d3ddev);

	// Khoi tao map
	this->map = new Map(this->getSpriteHandler(), MAP_ROOM1, world, 0, 0, world->grid);
		
	if (camera) 
	{
		camera->Follow(world->samus);
		camera->SetMapBoundary(map->getBoundary());
	}
		
	this->_InitPositions();
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
		map->UpdateMap(this->camera->getBoundary());
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
	//DWORD now = GetTickCount();
	//if (now - Delta  > 1000 / 100)
	//{
	//	intro->Next();
	//	Delta = now;
	//}
}

//update các object trong game
void Metroid::UpdateFrame(float Delta)
{
	currentTime = Delta;
	if (isInGame)
	{
		/*for (int i = 0; i < world->zoomerYellow.size(); i++)
			world->zoomerYellow[i]->setActive(false);*/
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
		if (world->samus->vx > 0)
		{
			if (world->samus->vy != 0)
				world->samus->setVelocityY(0);
		}

		if (world->samus->GetState() != MORPH_LEFT && world->samus->GetState() != MORPH_RIGHT
			&& world->samus->GetState() != JUMP_LEFT && world->samus->GetState() != JUMP_RIGHT
			&& world->samus->GetState() != JUMP_SHOOT_UP_LEFT && world->samus->GetState() != JUMP_SHOOT_UP_RIGHT
			&& world->samus->GetState() != TRANSFORM_BALL_LEFT && world->samus->GetState() != TRANSFORM_BALL_RIGHT)
		{
			world->samus->SetState(RUNNING_RIGHT);			
		}
	}
	else if (_input->IsKeyDown(DIK_LEFT)) {
		world->samus->setVelocityXLast(world->samus->getVelocityX());
		world->samus->setVelocityX(-SAMUS_SPEED);
		if (world->samus->GetState() != MORPH_LEFT && world->samus->GetState() != MORPH_RIGHT
			&& world->samus->GetState() != JUMP_LEFT && world->samus->GetState() != JUMP_RIGHT
			&& world->samus->GetState() != JUMP_SHOOT_UP_LEFT && world->samus->GetState() != JUMP_SHOOT_UP_RIGHT
			&& world->samus->GetState() != TRANSFORM_BALL_LEFT && world->samus->GetState() != TRANSFORM_BALL_RIGHT)
		{
			world->samus->SetState(RUNNING_LEFT);
		}
	}
	else
	{
		world->samus->setVelocityX(0);
		if (world->samus->getVelocityXLast() > 0)
		{
			if (world->samus->GetState() != MORPH_LEFT && world->samus->GetState() != MORPH_RIGHT
				&& world->samus->GetState() != JUMP_LEFT && world->samus->GetState() != JUMP_RIGHT
				&& world->samus->GetState() != JUMP_SHOOT_UP_LEFT && world->samus->GetState() != JUMP_SHOOT_UP_RIGHT
				&& world->samus->GetState() != TRANSFORM_BALL_LEFT && world->samus->GetState() != TRANSFORM_BALL_RIGHT)
			{
				world->samus->SetState(STAND_RIGHT);
				world->samus->ResetAllSprites();
			}
		}
		else if (world->samus->getVelocityXLast() < 0)
		{
			if (world->samus->GetState() != MORPH_LEFT && world->samus->GetState() != MORPH_RIGHT
				&& world->samus->GetState() != JUMP_LEFT && world->samus->GetState() != JUMP_RIGHT
				&& world->samus->GetState() != JUMP_SHOOT_UP_LEFT && world->samus->GetState() != JUMP_SHOOT_UP_RIGHT
				&& world->samus->GetState() != TRANSFORM_BALL_LEFT && world->samus->GetState() != TRANSFORM_BALL_RIGHT)
			{
				world->samus->SetState(STAND_LEFT);
				world->samus->ResetAllSprites();
			}
		}
	}

	if (_input->IsKeyDown(DIK_UP))
	{
		if (world->samus->GetState() == RUNNING_LEFT)
			world->samus->SetState(RUN_SHOOT_UP_LEFT);
		if (world->samus->GetState() == RUNNING_RIGHT)
			world->samus->SetState(RUN_SHOOT_UP_RIGHT);
		if (world->samus->GetState() == STAND_LEFT)
			world->samus->SetState(STAND_SHOOT_UP_LEFT);
		if (world->samus->GetState() == STAND_RIGHT)
			world->samus->SetState(STAND_SHOOT_UP_RIGHT);
		if (world->samus->GetState() == JUMP_LEFT)
		{
			world->samus->SetState(JUMP_SHOOT_UP_LEFT);
		}
		if (world->samus->GetState() == JUMP_RIGHT)
		{
			world->samus->SetState(JUMP_SHOOT_UP_RIGHT);
		}
		if (world->samus->GetState() == MORPH_LEFT)
			world->samus->SetState(STAND_LEFT);
		if (world->samus->GetState() == MORPH_RIGHT)
			world->samus->SetState(STAND_RIGHT);
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
				if (_input->IsKeyDown(DIK_SPACE))
				{
					world->bomb->setActive(true);
					world->bomb->setTimeSurvive(3);
					float bombPosX = world->samus->getPosX() + world->samus->currentSprite->getWidth() / 2;
					float bombPosY = world->samus->getPosY() + world->samus->currentSprite->getHeight() / 2;
					//world->bomb->ResetBomb(bombPosX, bombPosY);
					world->bomb->setPosX(bombPosX);
					world->bomb->setPosY(bombPosY);
					//world->bomb->setBombNo(0);
				}
				break;
			case DIK_DOWN:
				if (_input->IsKeyDown(DIK_DOWN) && world->samus->canMorph) {
					if (world->samus->getVelocityXLast() < 0) {
						if (world->samus->GetState() == STAND_LEFT || world->samus->GetState() == RUNNING_LEFT) {
							world->samus->Reset(world->samus->getPosX(), world->samus->getPosY() + 32.0f); 
							world->samus->SetState(TRANSFORM_BALL_LEFT);
							world->samus->isMorphing = true;
						}
					}
					else if (world->samus->getVelocityXLast() > 0) {
						if (world->samus->GetState() == STAND_RIGHT || world->samus->GetState() == RUNNING_RIGHT) {
							world->samus->Reset(world->samus->getPosX(), world->samus->getPosY() + 32.0f); 
							world->samus->SetState(TRANSFORM_BALL_RIGHT);
							world->samus->isMorphing = true;
						}
					}
				}		
				break;
			case DIK_UP:
				/*if (_input->IsKeyDown(DIK_UP))
				{
					if (world->samus->getVelocityXLast() < 0)
						world->samus->SetState(JUMP_LEFT);
					else if (world->samus->getVelocityXLast() > 0)
						world->samus->SetState(JUMP_RIGHT);
					float previous = 0;
					float current = GetTickCount();

					while (true)
					{
						previous = current;
						current = GetTickCount();

						float deltaTime = current - previous;
						if (deltaTime > 10 * tick_per_frame)
							deltaTime = 10 * tick_per_frame;
						if(world->samus->getVelocityXLast() > 0)
							world->samus->SetState(JUMP_RIGHT);
						world->samus->vy += world->samus->gravity * deltaTime;
					}
				}*/
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
	case DIK_DOWN:
		if (world->samus->getVelocityXLast() < 0)
		{
			world->samus->SetState(STAND_LEFT);
			if (world->samus->isMorphing == true)
			{
				world->samus->isMorphing = false;
				world->samus->Reset(world->samus->getPosX(), world->samus->getPosY() - 32.0f);
			}				
		}
		else if (world->samus->getVelocityXLast() > 0)
		{
			world->samus->isMorphing = false;
			world->samus->SetState(STAND_RIGHT);
			if (world->samus->isMorphing == true)
			{
				world->samus->isMorphing = false;
				world->samus->Reset(world->samus->getPosX(), world->samus->getPosY() - 32.0f);
			}
		}
		break;
	case DIK_UP:
		if (world->samus->GetState() == JUMP_RIGHT || world->samus->GetState() == JUMP_SHOOT_UP_RIGHT
			|| world->samus->GetState() == MORPH_RIGHT)
		{
			world->samus->SetState(STAND_RIGHT);
		}
		else if (world->samus->GetState() == JUMP_LEFT || world->samus->GetState() == JUMP_SHOOT_UP_LEFT
			|| world->samus->GetState() == MORPH_LEFT)
		{
			world->samus->SetState(STAND_LEFT);
		}
		break;
	case DIK_SPACE:
		if (world->bomb->isActive == false)
			world->bomb->ResetBombNo(1);
		else if (world->bomb->isActive == false)
			world->bomb->setBombNo(0);
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
	return this->map;
}