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
					else if (enemy[i]->getType() == SKREE) {
						Skree* skree = dynamic_cast<Skree*>(enemy[i]);
						skree->isDeath = true;
						skree->reset();
						GameObject* object = static_cast<GameObject*>(skree);
						object->setActive(false);
						this->grid->updateGrid(object, this->getPosX(), this->getPosY());
					}

				}
			}
			
		}

		Kraid * kraid = this->manager->kraid;
		if (kraid->isActive) {
			if ((kraid->pos_x >= this->pos_x && kraid->pos_x <= this->pos_x + this->getWidth()
				|| this->pos_x >= kraid->pos_x && this->pos_x <= kraid->pos_x + kraid->width)
				&& (kraid->pos_y >= this->pos_y && kraid->pos_y <= this->pos_y + this->getHeight() ||
					this->pos_y >= kraid->pos_y && this->pos_y <= kraid->pos_y + kraid->getHeight()
					)) {
				kraid->setHealth(kraid->getHealth() - 2);
				if (kraid->getHealth() <= 0) {
					kraid->setIsDeath(true);
					kraid->setActive(false);
					GameObject * object = static_cast<Kraid*>(kraid);
					this->grid->updateGrid(object, this->getPosX(), this->getPosY());
				}
			}
		}

		Ridley * ridley = this->manager->ridley;
		if (ridley->isActive) {
			if ((ridley->pos_x >= this->pos_x && ridley->pos_x <= this->pos_x + this->getWidth()
				|| this->pos_x >= ridley->pos_x && this->pos_x <= ridley->pos_x + ridley->width)
				&& (ridley->pos_y >= this->pos_y && ridley->pos_y <= this->pos_y + this->getHeight() ||
					this->pos_y >= ridley->pos_y && this->pos_y <= ridley->pos_y + ridley->getHeight()
					)) {
				ridley->setHealth(ridley->getHealth() - 2);
				if (ridley->getHealth() <= 0) {
					//kraid->Destroy(kraid->pos_x, kraid->pos_y);
					ridley->setIsDeath(true);
					ridley->setActive(false);
					GameObject * object = static_cast<Ridley*>(ridley);
					this->grid->updateGrid(object, this->getPosX(), this->getPosY());
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

