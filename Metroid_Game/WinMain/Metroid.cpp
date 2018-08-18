#include "Metroid.h"


void Metroid::_InitBackground()
{
}

void Metroid::_InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	world->InitSprites(d3ddv);	
}

void Metroid::_InitPositions()
{
	// Thêm Brick vào brick
	this->map->inputBrickToGrid(this->grid);

	world->samus->InitPostition();
	this->grid->add(this->world->samus);

	world->maruMari->Init(420, 288);
	this->grid->add(this->world->maruMari);

	world->bombWeapon->CreateBomb(0, 0);
	this->grid->add(world->bombWeapon);
	world->bombWeapon->setActive(false);

	world->explodeEffect->CreateExplode(360, 360);
	this->grid->add(world->explodeEffect);
	world->explodeEffect->setActive(false);

	world->gateLeftRoom1->Init(2224, 160);
	grid->add(world->gateLeftRoom1);
	world->gateRightRoom1->Init(2304, 160);
	grid->add(world->gateRightRoom1);
	world->gateBlockRoom1->Init(2240, 160);
	grid->add(world->gateBlockRoom1);

	world->gateLeftRoom2->Init(4272, 160);
	grid->add(world->gateLeftRoom2);
	world->gateRightRoom2->Init(4352, 160);
	grid->add(world->gateRightRoom2);
	world->gateBlockRoom2->Init(4288, 160);
	grid->add(world->gateBlockRoom2);

	world->gateLeftBoss1->Init(4912, 160);
	grid->add(world->gateLeftBoss1);
	world->gateRightBoss1->Init(4992, 160);
	world->gateRightBoss1->setGateState(OPEN);
	grid->add(world->gateRightBoss1);
	world->gateBlockBoss1->Init(4928, 160);
	grid->add(world->gateBlockBoss1);

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

	screenMode = GAMEMODE_INTRO;
}

Metroid::~Metroid()
{
	/*delete(this->world);
	delete(this->intro);
	delete(this->appear);
	delete(this->sound);
	delete(this->grid);*/
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
	this->grid = new Grid(height, width);

	world = new World(spriteHandler, this);

	srand((unsigned)time(NULL));
	this->_InitSprites(d3ddev);
	this->_InitPositions();

	if (camera) 
	{
		camera->Follow(world->samus);
		camera->SetMapBoundary(map->getBoundary());
	}

	this->world->samus->setStringMap(this->map->getStringMap());
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
		this->grid->setDeltaTime(Delta);
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
		RenderIntro(d3ddv);
		break;
		// start screen
	case GAMEMODE_START:
		RenderStartScreen(d3ddv);
		break;
		// game running
	case GAMEMODE_GAMERUN:
		RenderFrame(d3ddv);
		break;
		// game over
	case GAMEMODE_GAMEOVER:
		RenderGameOver(d3ddv);
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
	world->Render();
	map->drawMap();
}

// Xử lý nhấn đè phím
void Metroid::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta)
{
	Samus* samus = this->world->samus;
	// Nếu đang va chạm vs enemy thì không điều khiển đc

	if (samus->isCollideWithEnemy || samus->getIsChangingRoom() || samus->getStartMovingAfterRoomChanged()) {
		return;
	}
	SAMUS_STATE state = samus->GetState();

	if (_input->IsKeyDown(DIK_RIGHT))
	{
		world->samus->setVelocityX(SAMUS_SPEED);
		if (!samus->getIsBall() && !samus->isMorphing && !samus->isJumping) {
			world->samus->SetState(RUNNING_RIGHT);

		}
		else if (samus->isJumping) {
			if (state == JUMP_LEFT) {
				this->world->samus->SetState(JUMP_RIGHT);
			}
			else if (state == JUMP_SHOOT_UP_LEFT) {
				samus->SetState(JUMP_SHOOT_UP_RIGHT);
			}
		}
		else if (samus->getIsBall()) {
			if (state == TRANSFORM_BALL_LEFT) {
				samus->SetState(TRANSFORM_BALL_RIGHT);
			}
		}
	}
	else if (_input->IsKeyDown(DIK_LEFT)) {
		world->samus->setVelocityX(-SAMUS_SPEED);
		if (!samus->getIsBall() && !samus->isMorphing && !samus->isJumping) {
			world->samus->SetState(RUNNING_LEFT);
		}
		else if (samus->isJumping) {
			if (state == JUMP_RIGHT)
				this->world->samus->SetState(JUMP_LEFT);
			else if (state == JUMP_SHOOT_UP_RIGHT)
				this->world->samus->SetState(JUMP_SHOOT_UP_LEFT);
		}
		else if (samus->getIsBall()) {
			if (state == TRANSFORM_BALL_RIGHT) {
				samus->SetState(TRANSFORM_BALL_LEFT);
			}
		}
	}
	
	else
	{
		world->samus->setVelocityX(0);
		if (!samus->getIsBall() && !samus->isMorphing && !samus->isJumping) {
			if (state == RUNNING_RIGHT || state == RUN_SHOOTING_RIGHT || state == STAND_RIGHT || state == STAND_SHOOT_UP_RIGHT || state == RUN_SHOOT_UP_RIGHT) {
				samus->SetState(STAND_RIGHT);

				for (int i = 0; i < this->world->samusBullet.size(); i++) {
					if (!this->world->samusBullet[i]->getIsRendered()) {
						this->world->samusBullet[i]->setDirection(SHOOT_RIGHT);
						break;
					}
				}
			}
			else if (state == RUNNING_LEFT || state == RUN_SHOOTING_LEFT || state == STAND_LEFT || state == STAND_SHOOT_UP_LEFT || state == RUN_SHOOT_UP_LEFT) {
				samus->SetState(STAND_LEFT);

				for (int i = 0; i < this->world->samusBullet.size(); i++) {
					if (!this->world->samusBullet[i]->getIsRendered()) {
						this->world->samusBullet[i]->setDirection(SHOOT_LEFT);
						break;
					}
				}
			}
		}
		else if (state == JUMP_SHOOT_UP_LEFT) {
			samus->SetState(JUMP_LEFT);
		}
		else if (state == JUMP_SHOOT_UP_RIGHT) {
			samus->SetState(JUMP_RIGHT);
		}
	}

	if (_input->IsKeyDown(DIK_UP))
	{
		Samus* samus = this->world->samus;

		switch (this->world->samus->GetState()) {
		case MORPH_LEFT: case MORPH_RIGHT: {
			break;
		}
		case STAND_LEFT: {
			samus->SetState(STAND_SHOOT_UP_LEFT);
			break;
		}
		case STAND_RIGHT: {
			samus->SetState(STAND_SHOOT_UP_RIGHT);
			break;
		}
		case RUNNING_LEFT: case RUN_SHOOTING_LEFT: {
			samus->SetState(RUN_SHOOT_UP_LEFT);
			break;
		}
		case RUNNING_RIGHT: case RUN_SHOOTING_RIGHT:{
			samus->SetState(RUN_SHOOT_UP_RIGHT);
			break;
		}
		case JUMP_LEFT: {
			samus->SetState(JUMP_SHOOT_UP_LEFT);
			break;
		}
		case JUMP_RIGHT: {
			samus->SetState(JUMP_SHOOT_UP_RIGHT);
			break;
		}
		case TRANSFORM_BALL_LEFT: {
			vector<string> stringMap = this->map->getStringMap();
			if (stringMap.size() > 0) {
				int column = (int)floor(this->world->samus->pos_x / 32.0f);
				int row = (int)floor(this->world->samus->pos_y / 32.0f);

				int column2 = (int)ceil(this->world->samus->pos_x / 32.0f);

				if (row <= stringMap.size() && column <= stringMap[0].size() && column2 <= stringMap[0].size()) {
					if (stringMap[row - 1][column] == '0' && stringMap[row - 1][column2] == '0') {
						this->world->samus->setPosY(this->world->samus->getPosY() - 32);
						world->samus->setIsBall(false);
						world->samus->SetState(STAND_LEFT);
					}
				}
			}
			break;
		}
		case TRANSFORM_BALL_RIGHT: {
			vector<string> stringMap = this->map->getStringMap();
			if (stringMap.size() > 0) {
				int column = (int)floor(this->world->samus->pos_x / 32.0f);
				int row = (int)floor(this->world->samus->pos_y / 32.0f);

				int column2 = (int)ceil(this->world->samus->pos_x / 32.0f);

				if (row <= stringMap.size() && column <= stringMap[0].size() && column2 <= stringMap[0].size()) {
					if (stringMap[row - 1][column] == '0' && stringMap[row - 1][column2] == '0') {
						this->world->samus->setPosY(this->world->samus->getPosY() - 32);
						world->samus->setIsBall(false);
						world->samus->SetState(STAND_RIGHT);
					}
				}
			}
			break;
		}
		}
	}
	else if (_input->IsKeyDown(DIK_DOWN)) {
		if (this->world->samus->getIsBall()) {
			return;
		}

		if (this->world->samus->GetState() == STAND_LEFT) {
			this->world->samus->setPosY(this->world->samus->getPosY() + 32);
			this->world->samus->SetState(TRANSFORM_BALL_LEFT);
			this->world->samus->setIsBall(true);
		}
		else if (this->world->samus->GetState() == STAND_RIGHT) {
			this->world->samus->setPosY(this->world->samus->getPosY() + 32);
			this->world->samus->SetState(TRANSFORM_BALL_RIGHT);
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
					this->setSamusBulletDirection(this->world->samusBullet[0]);
				}
			}
			else {
				if (this->world->samusBullet[i - 1]->getIsRendered() && this->world->samusBullet[i - 1]->getCount() > 2) {
					this->world->samusBullet[i]->setActive(true);
					this->setSamusBulletDirection(this->world->samusBullet[i]);
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
		
	if (_input->IsKeyDown(DIK_X))
	{
		if (world->samus->canJump) {
			world->samus->isOnGround = false;
			this->world->samus->setVelocityY(-GRAVITY_VELOCITY);
			this->world->samus->isJumping = true;
			this->world->samus->isFalling = false;
			
			if (state == STAND_RIGHT) {
				samus->SetState(JUMP_RIGHT);

			}
			else if (state == STAND_LEFT) {
				samus->SetState(JUMP_LEFT);
			}
			else if (state == STAND_SHOOT_UP_LEFT) {
				samus->SetState(JUMP_SHOOT_UP_LEFT);
			}
			else if (state == STAND_SHOOT_UP_RIGHT) {
				samus->SetState(JUMP_SHOOT_UP_RIGHT);

			}
			else if (state == RUNNING_LEFT || state == RUN_SHOOTING_LEFT || state == RUN_SHOOTING_LEFT) {
				samus->SetState(MORPH_LEFT);
				samus->isMorphing = true;

			}
			else if (state == RUNNING_RIGHT || state == RUN_SHOOTING_RIGHT || state == RUN_SHOOTING_RIGHT) {
				samus->SetState(MORPH_RIGHT);
				samus->isMorphing = true;
			}
		}
	}
}

// Xử lý nhấn phím 1 lần
void Metroid::OnKeyDown(int KeyCode)
{
	Samus* samus = this->world->samus;
	// Nếu đang va chạm vs enemy thì không điều khiển đc

	if (samus->isCollideWithEnemy || samus->getIsChangingRoom() || samus->getStartMovingAfterRoomChanged()) {
		return;
	}
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
				if (this->world->samus->isOnGround) {
					if (_input->IsKeyDown(DIK_SPACE) && world->bombWeapon->getBombExplode() == true)
					{
						world->bombWeapon->setActive(true);
						world->bombWeapon->setTimeSurvive(1);
						world->bombWeapon->setBombExplode(false);

						float xpos = world->samus->getPosX();
						float ypos = world->samus->getPosY();
						float bombPosX = xpos + world->samus->getWidth() / 2;
						float bombPosY = ypos + world->samus->getHeight() / 2;
						world->bombWeapon->setPosX(bombPosX);
						world->bombWeapon->setPosY(bombPosY);
					}
				}
				break;
			case DIK_X:
			{
				if (this->world->samus->getIsBall()) {
					vector<string> stringMap = this->map->getStringMap();
					if (stringMap.size() > 0) {
						int column = (int)floor(this->world->samus->pos_x / 32.0f);
						int row = (int)floor(this->world->samus->pos_y / 32.0f);

						int column2 = (int)ceil(this->world->samus->pos_x / 32.0f);

						if (row <= stringMap.size() && column <= stringMap[0].size() && column2 <= stringMap[0].size()) {
							if (stringMap[row - 1][column] == '0' && stringMap[row - 1][column2] == '0') {
								this->world->samus->setPosY(this->world->samus->getPosY() - 32);
								world->samus->setIsBall(false);
								if (world->samus->GetState() == TRANSFORM_BALL_RIGHT) {
									world->samus->SetState(STAND_RIGHT);
								}
								else if (world->samus->GetState() == TRANSFORM_BALL_LEFT) {
									world->samus->SetState(STAND_LEFT);
								}
							}
						}
					}
				}
				else {
					if (this->world->samus->isOnGround) {
						vector<string> stringMap = this->map->getStringMap();
						if (stringMap.size() > 0) {
							int column = (int)floor(this->world->samus->pos_x / 32.0f);
							int row = (int)floor(this->world->samus->pos_y / 32.0f);

							int column2 = (int)ceil(this->world->samus->pos_x / 32.0f);

							if (row <= stringMap.size() && column <= stringMap[0].size() && column2 <= stringMap[0].size()) {
								if (stringMap[row - 1][column] == '0' && stringMap[row - 1][column2] == '0') {
									this->world->samus->canJump = true;
									this->world->samus->setStartPosJump(this->world->samus->getPosY());
								}
							}
						}
						
					}
				}
			}
				break;

				// C la ban ten lua
			case DIK_C:
			{
				if (!this->world->missible->isActive) {
					if (this->world->samus->getIsBall() || this->world->samus->isMorphing)
						return;
					else {
						SAMUS_STATE samusState = this->world->samus->GetState();

						switch (samusState) {
						case STAND_LEFT: case RUNNING_LEFT: case JUMP_LEFT: case RUN_SHOOTING_LEFT: {
							this->world->missible->isActive = true;
							this->world->missible->setState(MISSIBLE_SHOT_LEFT);
							break;
						}

						case STAND_RIGHT: case RUNNING_RIGHT: case JUMP_RIGHT: case RUN_SHOOTING_RIGHT: {
							this->world->missible->isActive = true;
							this->world->missible->setState(MISSIBLE_SHOT_RIGHT);
							break;
						}

						case JUMP_SHOOT_UP_LEFT: case JUMP_SHOOT_UP_RIGHT: case STAND_SHOOT_UP_LEFT: case STAND_SHOOT_UP_RIGHT: {
							this->world->missible->isActive = true;
							this->world->missible->setState(MISSIBLE_SHOT_UP);
							break;
						}
						}

						if (samusState == RUNNING_RIGHT) {
							this->world->samus->SetState(RUN_SHOOT_UP_RIGHT);
						}
						else if (samusState == RUNNING_LEFT) {
							this->world->samus->SetState(RUN_SHOOT_UP_LEFT);
						}
					}
				}
			}
				break;

			case DIK_LEFT:
				if (world->samus->GetState() == MORPH_RIGHT)
					world->samus->SetState(MORPH_LEFT);
				else if (world->samus->GetState() == JUMP_RIGHT)
					world->samus->setStartPosJump(JUMP_LEFT);
				break;
			case DIK_RIGHT:
				if (world->samus->GetState() == MORPH_LEFT)
					world->samus->SetState(MORPH_RIGHT);
				else if (world->samus->GetState() == JUMP_LEFT)
					world->samus->SetState(JUMP_RIGHT);
				break;
			case DIK_DOWN:
				if (this->world->samus->getIsBall()) {
					return;
				}

				if (this->world->samus->GetState() == STAND_LEFT) {
					this->world->samus->setPosY(this->world->samus->getPosY() + 32);
					this->world->samus->SetState(TRANSFORM_BALL_LEFT);
					this->world->samus->setIsBall(true);
				}
				else if (this->world->samus->GetState() == STAND_RIGHT) {
					this->world->samus->setPosY(this->world->samus->getPosY() + 32);
					this->world->samus->SetState(TRANSFORM_BALL_RIGHT);
					this->world->samus->setIsBall(true);
				}
				break;
			}
		case DIK_UP: {

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
	Samus* samus = this->world->samus;
	// Nếu đang va chạm vs enemy thì không điều khiển đc

	if (samus->isCollideWithEnemy || samus->getIsChangingRoom() || samus->getStartMovingAfterRoomChanged()) {
		return;
	}
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
		break;

	case DIK_X:{
		if (this->world->samus->canJump) {
			this->world->samus->canJump = false;
		}
		break;
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

Map * Metroid::getMap() {
	return this->map;
}

Grid * Metroid::getGrid()
{
	return this->grid;
}

void Metroid::setSamusBulletDirection(Bullet* bullet) {
	switch (this->world->samus->GetState()) {
	case STAND_LEFT: case RUNNING_LEFT: case RUN_SHOOTING_LEFT: case JUMP_LEFT: {
		bullet->setDirection(SHOOT_LEFT);
		break;
	}
	case STAND_RIGHT: case RUNNING_RIGHT: case RUN_SHOOTING_RIGHT:case JUMP_RIGHT: {
		bullet->setDirection(SHOOT_RIGHT);
		break;
	}
	case STAND_SHOOT_UP_LEFT: case JUMP_SHOOT_UP_LEFT: case RUN_SHOOT_UP_LEFT:{
		bullet->setDirection(SHOOT_UP_LEFT);
		break;
	}
	case STAND_SHOOT_UP_RIGHT: case JUMP_SHOOT_UP_RIGHT: case RUN_SHOOT_UP_RIGHT: {
		bullet->setDirection(SHOOT_UP_RIGHT);
		break;
	}
	case MORPH_LEFT: case MORPH_RIGHT: case TRANSFORM_BALL_LEFT: case TRANSFORM_BALL_RIGHT: {
		bullet->setDirection(OFF);
		break;
	}
	}
}