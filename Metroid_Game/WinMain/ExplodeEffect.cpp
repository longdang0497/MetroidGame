#include "ExplodeEffect.h"
#include "World.h"
ExplodeEffect::ExplodeEffect()
{
}

ExplodeEffect::ExplodeEffect(LPD3DXSPRITE spriteHandler, World *manager, Grid * grid) : Effect(spriteHandler, manager, grid)
{
	this->spriteHandler = spriteHandler;
	this->grid = grid;
	this->manager = manager;
	explode = nullptr;
	isActive = false;
	this->width = EFFECT_EXPLOSION_WIDTH;
	this->height = EFFECT_EXPLOSION_HEIGHT;
	
}


ExplodeEffect::~ExplodeEffect()
{
	//delete explode;
	//delete manager;
	//delete grid;
}


void ExplodeEffect::Update(float t)
{

	if (isActive == true && manager->bombWeapon->getBombExplode() == true)
	{
		vector<Enemy*> enemy = this->manager->enemy;
		for (int i = 0; i < enemy.size(); i++) {
			if (enemy[i]->isActive) {
				if ((enemy[i]->pos_x >= this->pos_x && enemy[i]->pos_x <= this->pos_x + this->getWidth() 
					|| this->pos_x >= enemy[i]->pos_x && this->pos_x <= enemy[i]->pos_x + enemy[i]->width)
					&& (enemy[i]->pos_y >= this->pos_y && enemy[i]->pos_y <= this->pos_y + this->getHeight()||
						this->pos_y >= enemy[i]->pos_y && this->pos_y <= enemy[i]->pos_y + enemy[i]->getHeight()
						)) {
					if (enemy[i]->getType() == ZOOMER_PINK || enemy[i]->getType() == ZOOMER_YELLOW) {
						Zoomer* zoomer = dynamic_cast<Zoomer*>(enemy[i]);
						zoomer->isDeath = true;
						zoomer->setIsEnemyFreezed(false);

						zoomer->reset();
						GameObject* object = static_cast<GameObject*>(zoomer);
						object->setActive(false);
						this->grid->updateGrid(object, this->getPosX(), this->getPosY());
					}

				}
			}
			
		}
		//time_survive = EFFECT_TIME_SURVIVE;
		DWORD now = GetTickCount();
		if (now - last_time > 1000 / ANIMATE_RATE)
		{
			explode->updateSprite();
			last_time = now;
		}
		// Tính thời gian hiển thị
		time_survive -= t;
		if (time_survive < 0)
		{
			isActive = false;
		}

	}
	else
		return;


}

void ExplodeEffect::Render()
{
	if (time_survive <= 0)
		isActive = false;

	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	if (isActive == true && manager->bombWeapon->getBombExplode() == true && time_survive > 0)
	{
		//isRendering == true;
		explode->drawSprite(EFFECT_EXPLOSION_WIDTH, EFFECT_EXPLOSION_HEIGHT, position);
	}

}

void ExplodeEffect::CreateExplode(float x, float y)
{
	this->pos_y = y;
	this->pos_x = x;
	//currentSprite = explode;
}

void ExplodeEffect::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;

	explode = new Sprite(spriteHandler, texture, EFFECT_EXPLOSION, EFFECT_EXPLOSION_WIDTH, EFFECT_EXPLOSION_HEIGHT, EFFECT_EXPLOSION_COUNT);
}

