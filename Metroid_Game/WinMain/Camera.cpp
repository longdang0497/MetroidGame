#include "Camera.h"
#include <d3d9.h>

Camera::Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors)
{
	this->width = width;
	this->height = height;
	this->angle = angle;
	this->scaleFactors = scaleFactors;
	//D3DXMatrixOrthoLH(&orthographicMatrix, width, height, 0.0f, 1.0f);
	D3DXMatrixOrthoOffCenterLH(&orthographicMatrix, -width / 2, width / 2, -height / 4, 3*(height / 4), 0.0f, 1.0f);
	D3DXMatrixIdentity(&identityMatrix);
}

Camera::~Camera()
{
	
}

void Camera::Follow(GameObject * object) {
	m_following = object;
}

void Camera::Update(Map * map)
{
	D3DXVECTOR3 eye(90, 90, 1);	
	D3DXVECTOR3 direction(0, 0, -1);
	D3DXVECTOR3 up(0, -1, 0);	//r

	//int cameraX = width/2, cameraY = height/2;
	if (m_following != nullptr)
	{
		eye.x = m_following->pos_x;
		eye.y = m_following->pos_y;
	}

	int cameraY = m_following->pos_y - 3 * (height / 4);
	int cameraX = m_following->pos_x - width / 4;

	if (cameraY > 3 * (height / 4))
	{
		m_following->pos_y = 3 * (height / 4);
	}
	else if (cameraX > (width/2))
	{
		m_following->pos_x = width / 4;
	}

	D3DXMatrixLookAtLH(&viewMatrix, &eye, &(eye + direction), &up);
}

void Camera::SetTransform(DeviceManager* device) const
{
	device->getdevice()->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	device->getdevice()->SetTransform(D3DTS_WORLD, &identityMatrix);
	device->getdevice()->SetTransform(D3DTS_VIEW, &viewMatrix);
}






