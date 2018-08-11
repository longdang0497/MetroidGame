#pragma once

#include <DirectXMath.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "DeviceManager.h"
#include "GameObject.h"

class Camera
{
public:
	//Constructors and Destructor
	Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors);
	~Camera();

	//Game Functions
	void Update(float t);
	void SetTransform(DeviceManager *device) const;
	void SetMapBoundary(RECT rect);
	RECT getBoundary();
	void Follow(GameObject * object);

	void setIsChanging(bool value) { this->isChangingRoom = value; }
	bool getIsChanging() { return this->isChangingRoom; }
	void setStartPosX(float value) { this->startPosX = value; }
	float getStartPosX() { return this->startPosX; }
	void setEndPosX(float value) { this->endPosX = value; }
	float getEndPosX() { return this->endPosX; }
private:
	float angle;
	DirectX::XMFLOAT3 scaleFactors;
	D3DXMATRIX orthographicMatrix;	//ma trận tầm nhìn
	D3DXMATRIX identityMatrix;	//ma trận vật
	D3DXMATRIX viewMatrix;	//ma trận trong world

	int width;
	int height;
	RECT m_map_bound;
	GameObject* m_following = nullptr;
	RECT Camera_bound;

	bool isChangingRoom;
	float startPosX;	//vi tri bat dau luot camera (co dinh)
	float endPosX;	//

};
