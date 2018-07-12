#include "Camera.h"
#include <d3d9.h>

Camera::Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors)
{
	this->width = width;
	this->height = height;
	this->angle = angle;
	this->scaleFactors = scaleFactors;
	//D3DXMatrixOrthoLH(&orthographicMatrix, width, height, 0.0f, 1.0f);

	
	float left = -width * CAMERA_FOLLOW_POINT_LEFT_RATIO;
	float right = width * CAMERA_FOLLOW_POINT_RIGHT_RATIO;
	float top = height * CAMERA_FOLLOW_POINT_TOP_RATIO;
	float bottom = -height * CAMERA_FOLLOW_POINT_BOTTOM_RATIO;
	D3DXMatrixOrthoOffCenterLH(&orthographicMatrix, left, right, bottom, top, 0.0f, 1.0f);
	D3DXMatrixIdentity(&identityMatrix);
}

Camera::~Camera()
{
	
}

void Camera::Follow(GameObject * object) {
	m_following = object;
}

RECT Camera::getBoundary() {
	return Camera_bound;
}

void Camera::Update()
{
	D3DXVECTOR3 eye(320, 352, 1);	// x,y not important, camera've been following m_following
	D3DXVECTOR3 direction(0, 0, -1);
	D3DXVECTOR3 up(0, -1, 0);	//r

	//int cameraX = width/2, cameraY = height/2;

	if (m_following != nullptr)
	{
		//camera follow object
		eye.x = m_following->pos_x;
		eye.y = m_following->pos_y;

		//set bound camera
		Camera_bound.top	= m_following->pos_y - CAMERA_FOLLOW_POINT_TOP_RATIO * height;
		Camera_bound.bottom = m_following->pos_y + CAMERA_FOLLOW_POINT_BOTTOM_RATIO * height;
		Camera_bound.left	= m_following->pos_x - CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
		Camera_bound.right	= m_following->pos_x + CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;

		//check camera vs map bound
		if (Camera_bound.left < m_map_bound.left)
			eye.x = m_map_bound.left  + CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
		else if (Camera_bound.right > m_map_bound.right)
			eye.x = m_map_bound.right - CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;
		if (Camera_bound.top < m_map_bound.top)
			eye.y = m_map_bound.top + CAMERA_FOLLOW_POINT_TOP_RATIO * height;
		else if (Camera_bound.bottom > m_map_bound.bottom)
			eye.y = m_map_bound.bottom - CAMERA_FOLLOW_POINT_BOTTOM_RATIO * height;

		//update camera bound
		Camera_bound.top = eye.y - CAMERA_FOLLOW_POINT_TOP_RATIO * height;
		Camera_bound.bottom = eye.y + CAMERA_FOLLOW_POINT_BOTTOM_RATIO * height;
		Camera_bound.left = eye.x - CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
		Camera_bound.right = eye.x + CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;
	}

	D3DXMatrixLookAtLH(&viewMatrix, &eye, &(eye + direction), &up);
}

void Camera::SetTransform(DeviceManager* device) const
{
	device->getdevice()->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	device->getdevice()->SetTransform(D3DTS_WORLD, &identityMatrix);
	device->getdevice()->SetTransform(D3DTS_VIEW, &viewMatrix);
}

void Camera::SetMapBoundary(RECT rect)
{
	m_map_bound = rect;
}






