#include "Zoomer.h"
#include "World.h"

Zoomer::Zoomer()
{
}

Zoomer::Zoomer(LPD3DXSPRITE spriteHandler, World * manager, ENEMY_TYPE enemy_type) : Enemy(spriteHandler, manager)
{
	this->enemy_type = enemy_type;
	this->isActive = true;

	//Set vận tốc
	gravity = FALLDOWN_VELOCITY_DECREASE;
	vx = ZOOMER_SPEED;
	vy = 0;
}


Zoomer::~Zoomer()
{
	delete(top);
	delete(bottom);
	delete(left);
	delete(right);
}


void Zoomer::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;

	LPWSTR top_path = NULL, bottom_path = NULL, left_path = NULL, right_path = NULL;

	switch (enemy_type)
	{
	case ZOOMER_YELLOW:
		top_path = ZOOMER_YELLOW_TOP;
		bottom_path = ZOOMER_YELLOW_BOTTOM;
		left_path = ZOOMER_YELLOW_LEFT;
		right_path = ZOOMER_YELLOW_RIGHT;

		//Khởi tạo máu
		//health = HEALTH_BEDGEHOG_YELLOW;

		//Khởi tạo sát thương
		//damage = DAMAGE_BEDGEHOG;
		break;
	case ZOOMER_PINK:
		top_path = ZOOMER_PINK_UP;
		bottom_path = ZOOMER_PINK_BOTTOM;
		left_path = ZOOMER_PINK_LEFT;
		right_path = ZOOMER_PINK_RIGHT;

		//Khởi tạo máu
		//health = HEALTH_ZOOMER_PINK;

		//Khởi tạo sát thương
		//damage = DAMAGE_ZOOMER;
		break;
	}

	//// Khởi tạo sprite
	top = new Sprite(spriteHandler, texture, top_path, ZOOMER_WIDTH, ZOOMER_HEIGHT, ZOOMER_SPRITE_COUNT);
	bottom = new Sprite(spriteHandler, texture, bottom_path, ZOOMER_WIDTH, ZOOMER_HEIGHT, ZOOMER_SPRITE_COUNT);
	left = new Sprite(spriteHandler, texture, left_path, ZOOMER_WIDTH, ZOOMER_HEIGHT, ZOOMER_SPRITE_COUNT);
	right = new Sprite(spriteHandler, texture, right_path, ZOOMER_WIDTH, ZOOMER_HEIGHT, ZOOMER_SPRITE_COUNT);

}

//void Zoomer::Update(float t)
//{
//	isCollision = false;
//
//	if (!isActive) return;
//
//	// Nếu không nằm trong Camera thì unactive
//	if (!IsInCamera())
//	{
//		isActive = false;
//		return;
//	}
//
//	//if (onGround)
//	//	vy -= FALLDOWN_VELOCITY_DECREASE;
//	if (!isCollision)
//		vy -= gravity;
//
//	// CODE NÀY DƠ, BỎ - QUAN
//	//Kiểm tra va chạm với Samus
//	//float clsTimeSamus = SweptAABB(manager->samus, t);
//	//if (clsTimeSamus < 1.0f)
//	//{
//	//	if (normalx < -0.1f)
//	//	{
//	//		// this = target
//	//		manager->samus->SetPosX((manager->samus->GetPosX() + manager->samus->GetCollider()->GetLeft() - this->GetCollider()->GetRight()) - 0.2f);
//	//		//manager->samus->SetPosX(manager->samus->GetPosX() - manager->samus->GetVelocityX()*t);
//	//	}
//	//	else if (normalx > 0.1f)
//	//	{
//
//	//	}
//	//}
//
//	//Kiểm tra va chạm với ground
//	
//	for (int i = 0; i < manager->quadtreeGroup->size; i++)
//	{
//		switch (manager->quadtreeGroup->objects[i]->GetType())
//		{
//		case BRICK:
//			float timeScale = SweptAABB(manager->quadtreeGroup->objects[i], t);
//			if (timeScale < 1.0f)
//			{
//				isCollision = true;
//				ResponseGround(manager->quadtreeGroup->objects[i], t, timeScale);
//				
//					//pos_x += vx * timeScale;
//					//pos_y += vy * timeScale;
//					//if (normaly > 0.1f)
//					//{
//					//	gravity = 0.03f;
//					//	pos_y += 0.1f;
//					//	vx = BEDGEHOG_SPEED;
//					//	vy = 0.05f;
//					//}
//					//if (normalx < -0.1f)
//					//{
//					//	pos_x -= 0.1f;
//					//	gravity = 0;
//					//	vy = 0.07f;
//					//	vx = BEDGEHOG_SPEED;
//					//}
//					///*if (normalx > 0.1f)
//					//{
//					//	pos_x += 0.1f;
//					//	gravity = 0;
//					//	vy = -0.07f;
//					//	vx = -BEDGEHOG_SPEED;
//					//}*/
//					//if (normaly < -0.1f)
//					//{
//					//	gravity = -0.03f;
//					//	pos_y -= 0.1f;
//					//	vx = -BEDGEHOG_SPEED;
//					//	vy = 0.05f;
//					//}
//
//					//float magnitude = sqrt(vx*vx + vy*vy)*(1 - timeScale);
//					//float dotprod = (vx*normaly + vy*normalx);
//					//if (dotprod > 0.0f)
//					//{
//					//	dotprod = 1.0f;
//					//}
//					//else if (dotprod < 0.0f)
//					//{
//					//	dotprod = -1.0f;
//					//}
//					//vx = dotprod*normaly*magnitude;
//					//vy = dotprod*normalx*magnitude;
//			}
//			break;
//		}
//	}
//
//	for (int i = 0; i < manager->colBrick->objects.size(); i++)
//	{
//		float timeScale = SweptAABB(manager->colBrick->objects[i], t);
//		// Nếu có va chạm
//		if (timeScale < 1.0f)
//		{
//			isCollision = true;
//			ResponseGround(manager->colBrick->objects[i], t, timeScale);
//		}
//	}
//
//	if (!isCollision && gravity == 0)
//	{
//		if (last_normalx > 0.1f)
//		{
//			state = ON_ZOOMER_BOTTOM;
//			vx = -BEDGEHOG_SPEED;
//			vy = 0.01f;
//		}
//		else if (last_normalx < -0.1f)
//		{
//			state = ON_ZOOMER_UP;
//			vx = BEDGEHOG_SPEED;
//			vy = -0.01f;
//		}
//
//		if (last_normaly > 0.1f)
//		{
//			state = ON_ZOOMER_RIGHT;
//			vx = -0.01f;
//			vy = -0.05f;
//		}
//		else if (last_normaly < -0.1f)
//		{
//			vx = 0.01f;
//			vy = 0.05f;
//			state = ON_ZOOMER_LEFT;
//		}
//	}
//
//	// Nếu frame này không va chạm
//	/*if (!isCollision && gravity == 0 && (last_normalx !=0 || last_normaly != 0))
//	{
//		if (last_normalx > 0.1f)
//		{
//			state = ON_ZOOMER_BOTTOM;
//			vx = -BEDGEHOG_SPEED;
//			vy = 0.01f;
//		}
//		else if (last_normalx < -0.1f)
//		{
//			state = ON_ZOOMER_UP;
//			vx = BEDGEHOG_SPEED;
//			vy = -0.01f;
//		}
//
//		if (last_normaly > 0.1f)
//		{
//			state = ON_ZOOMER_RIGHT;
//			vx = -0.01f;
//			vy = -0.05f;
//		}
//		else if (last_normaly < -0.1f)
//		{
//			vx = 0.15f;
//			vy = 0.05f;
//			state = ON_ZOOMER_LEFT;
//		}
//	}*/
//
//	pos_x += vx*t;
//	pos_y += vy*t;
//
//	DWORD now = GetTickCount();
//	if (now - last_time > 1000 / ANIMATE_RATE)
//	{
//		switch (state)
//		{
//		case ON_ZOOMER_UP:
//			up->Next();
//			break;
//		case ON_ZOOMER_BOTTOM:
//			bottom->Next();
//			break;
//		case ON_ZOOMER_LEFT:
//			left->Next();
//			break;
//		case ON_ZOOMER_RIGHT:
//			right->Next();
//			break;
//		}
//		last_time = now;
//	}
//
//	// --TO DO: Xử lý va chạm
//	// ...
//	// Khi cần xử lý va chạm, gọi groupCollision ở world
//	//	
//}

void Zoomer::Update(float t)
{
	grid->add(this);
	if (!isActive) return;

	pos_x += vx * t;
	pos_y += vy * t;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_ENEMY_RATE)
	{
		switch (state)
		{
		case ON_ZOOMER_UP:
			top->updateSprite();
			break;
		case ON_ZOOMER_BOTTOM:
			bottom->updateSprite();
			break;
		case ON_ZOOMER_LEFT:
			left->updateSprite();
			break;
		case ON_ZOOMER_RIGHT:
			right->updateSprite();
			break;
		}
		last_time = now;
	}

}

void Zoomer::Render()
{
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	// Nếu không active thì không render
	if (!isActive)
		return;
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	switch (state)
	{
	case ON_ZOOMER_UP:
		top->drawSprite(top->getWidth(), top->getHeight(), position);
		break;
	case ON_ZOOMER_BOTTOM:
		bottom->drawSprite(bottom->getWidth(), bottom->getHeight(), position);
		break;
	case ON_ZOOMER_LEFT:
		left->drawSprite(left->getWidth(), left->getHeight(), position);
		break;
	case ON_ZOOMER_RIGHT:
		right->drawSprite(right->getWidth(), right->getHeight(), position);
		break;
	}
	spriteHandler->End();
}

void Zoomer::Destroy()
{
}