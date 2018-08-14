#pragma once
#include "Sprite.h"
#include "GameObject.h"
#include "trace.h"
#include "World.h"

enum GATE_STATE {  //State of Gate
	OPEN,
	CLOSE,
	DESTROYING
};

enum GATE_TYPE
{
	GATE_LEFT,
	GATE_RIGHT
};

class Gate : public GameObject
{
protected:
	Sprite * exists_left;
	Sprite * exists_right;
	Sprite * destroying_left;
	Sprite * destroying_right;
	float time_survive;
	GATE_STATE state;
	GATE_TYPE gate_type;

	bool isRight = false;
	bool isLeft = false;
public:
	Gate();
	Gate(LPD3DXSPRITE spriteHandler, World * manager);
	~Gate();

	GATE_TYPE GetGateType();
	void setGateType(GATE_TYPE value);

	void setGateState(GATE_STATE value);
	GATE_STATE getGateState();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture, GATE_TYPE gateType);
	void Init(int x, int y);
	void Update(float t);
	void Render();
	void DestroyGate();

	void setIsRight(bool value);
	void setIsLeft(bool value);
};