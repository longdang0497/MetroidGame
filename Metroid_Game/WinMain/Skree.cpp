#include "Skree.h"
#include "World.h"
#include "Define.h"

Skree::Skree()
{
}

Skree::Skree(LPD3DXSPRITE spriteHandler, World * manager) : Enemy(spriteHandler, manager)
{
	this->isActive = true;

	//Set animate rate ban đầu
	animate_rate = SKREE_STANDARD_ANIMATE_RATE;
}

Skree::~Skree()
{
	delete(skree);
}

void Skree::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;

	// Khởi tạo sprite
	skree = new Sprite(spriteHandler, texture, SKREE_PATH, SKREE_WIDTH, SKREE_HEIGHT, SKREE_COUNT);
}
void Skree::Update(float t)
{
	grid->add(this);
	if (!isActive) return;

	// Nếu không nằm trong Camera thì unactive
	/*if (!IsInCamera())
	{
		isActive = false;
		return;
	}*/
	// khi samus đi vào vùng va chạm

	/*if (this->IsCollide(manager->samus) == true)
	{
		vy = -0.28f;
		animate_rate = BIRD_BOOST_ANIMATE_RATE;
		if (pos_x < manager->samus->getPosX())
		{
			vx = 0.05f;
		}
		else
		{
			vx = -0.05f;
		}
	}*/

	/*float scaletime = SweptAABB(manager->samus, t);
	if (scaletime < 1.0f)
	{
	Deflect(manager->samus, t, scaletime);
	}*/

	pos_x += vx * t;
	pos_y += vy * t;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / animate_rate)
	{
		skree->updateSprite();
		last_time = now;
	}
}

void Skree::Render()
{
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	// Nếu không active thì không render
	if (!isActive)
		return;
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	skree->drawSprite(skree->getWidth(), skree->getHeight(), position);
	spriteHandler->End();
}

void Skree::Destroy()
{
	//// Effect explosion

	//// Destroy
	//vx = 0;

	//manager->explsEffect->Init(this->pos_x, this->pos_y);	 // Xảy ra lỗi khi giết những mục tiêu to (Ridley, Mother Brain)
	//														 // Drop item after destroyed
	//int random;

	///* initialize random seed: */
	//srand(time(NULL));

	///* generate secret number between 1 and 10: */
	//random = rand() % 10 + 1;

	//if (random == 1 || random == 5)
	//	manager->energyItem->Init(this->pos_x, this->pos_y);
	//else if (random == 7 || random == 9)
	//	manager->missileItem->Init(this->pos_x, this->pos_y);
	//Enemy::Destroy();
}