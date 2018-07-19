#include "bullet.h"

Bullet::Bullet(LPD3DXSPRITE spriteHandler, float X, float Y, float VX, float VY)
{
	bullet = NULL;
	bulletTexture = NULL;
	texture = new Texture();
	isRender = false;
	this->spriteHandler = spriteHandler;

	HRESULT result = this->spriteHandler->GetDevice(&m_d3ddv);
	if (result != D3D_OK) return;

	CreateBullet();

	pos_x = X;
	pos_y = Y;

	vx = VX;
	vy = VY;
}

Bullet::~Bullet()
{
	//if (m_d3ddv) { bullet = nullptr; delete m_d3ddv; };
	if (bullet) { bullet = nullptr;	delete bullet; };
}

void Bullet::SetState(BulletDirection value)
{
	bulletdir = value;
}

BulletDirection Bullet::GetState()
{
	return bulletdir;
}

void Bullet::CreateBullet()
{
	//if (m_d3ddv == NULL) return;
	//Create sprite handler
	
	bulletTexture = texture->loadTexture(m_d3ddv, BULLET_TEXTURE);
	bullet = new Sprite(this->spriteHandler, bulletTexture, BULLET_PATH, WIDTH_BULLET, HEIGHT_BULLET, 1);
}

void Bullet::Update(float Delta)
{
	pos_x += vx * Delta;
	pos_y += vy * Delta;
	bullet->updateSprite();
}

void Bullet::Render()
{
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	this->spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	bullet->drawSprite(bullet->getWidth(), bullet->getHeight(), position);
	this->spriteHandler->End();
	isRender = true;
}

bool Bullet::isRendering()
{
	Render();
	if (!isRender) return false;
	else
		return true;
}