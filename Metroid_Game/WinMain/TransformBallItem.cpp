//#include "TransformBallItem.h"
//#include "World.h"
//
//BallItem::BallItem(LPD3DXSPRITE spriteHandler, World * manager) :Item(spriteHandler, manager)
//{
//	item_type = MORPH_BALL_ITEM;
//	isActive = true;
//}
//
//BallItem::~BallItem()
//{
//}
//
//void BallItem::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
//{
//	if (d3ddv == NULL) return;
//	//Create sprite handler
//	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
//	if (result != D3D_OK) return;
//	itemSprite = new Sprite(spriteHandler, texture, ITEM_MORPH_BALL, ITEM_MORPH_BALL_WIDTH, ITEM_MORPH_BALL_HEIGHT, ITEM_MORPH_BALL_COUNT);
//}
//
//void BallItem::Update(float t)
//{
//}
//
//void BallItem::Render()
//{
//	if (!isActive)
//		return;
//	D3DXVECTOR3 position;
//	position.x = pos_x;
//	position.y = pos_y;
//	position.z = 0;
//
//	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
//	itemSprite->drawSprite(itemSprite->getWidth(), itemSprite->getHeight(), position);
//	spriteHandler->End();
//}
//
//void BallItem::Destroy()
//{
//	isActive = false;
//}
//
//
