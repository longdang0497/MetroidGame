#include "Camera.h"

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
	//D3DXMatrixIdentity(&identityMatrix);
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

void Camera::Update(float t)
{
	D3DXVECTOR3 eye(320, 352, 1);	// x,y not important, camera've been following m_following
	D3DXVECTOR3 direction(0, 0, -1);
	D3DXVECTOR3 up(0, -1, 0);

	if (m_following != nullptr)
	{
		//camera follow object
		eye.x = m_following->pos_x;
		eye.y = m_following->pos_y;

		//set bound camera
		Camera_bound.top = m_map_bound.top - CAMERA_FOLLOW_POINT_TOP_RATIO * height;
		Camera_bound.bottom = m_map_bound.bottom + CAMERA_FOLLOW_POINT_BOTTOM_RATIO * height;
		Camera_bound.left = m_following->pos_x - CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
		Camera_bound.right = m_following->pos_x + CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;

		//check camera vs map bound
		switch (m_following->getRoomNum()) {
		case ROOM1:
			if (Camera_bound.left < m_map_bound.left)
				eye.x = m_map_bound.left + CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
			else if (Camera_bound.right > WIDTH_ROOM1)
				eye.x = WIDTH_ROOM1 - CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;

			if (m_following->pos_x > WIDTH_ROOM1)
			{
				eye.x = WIDTH_ROOM1 + CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
			}
			break;
		case ROOM2:
			if (Camera_bound.left < WIDTH_ROOM1)
			{			
				//eye.x += 64;
				//if (eye.x == WIDTH_ROOM1)
					eye.x = WIDTH_ROOM1 + CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
			}
			else if (Camera_bound.right > WIDTH_ROOM1 + WIDTH_ROOM2)
				eye.x = WIDTH_ROOM1 + WIDTH_ROOM2 - CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;
			break;
		case BOSS1:
			if (Camera_bound.left < WIDTH_ROOM1 + WIDTH_ROOM2)
			{
				//eye.x += 64 * m_following->getCurrentTime();
				//if (eye.x == WIDTH_ROOM1 + WIDTH_ROOM2)
					eye.x = WIDTH_ROOM1 + WIDTH_ROOM2 + CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
			}
			else if (Camera_bound.right > WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS)
				eye.x = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS - CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;
			break;
		case BOSS2:
			if (Camera_bound.left < WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS)
			{
				//eye.x += 64 * m_following->getCurrentTime();
				//if (eye.x == WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS)
					eye.x = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS + CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
			}
			else if (Camera_bound.right > WIDTH_ROOM1 + WIDTH_ROOM2 + 2 * WIDTH_ROOM_BOSS)
				eye.x = WIDTH_ROOM1 + WIDTH_ROOM2 + 2 * WIDTH_ROOM_BOSS - CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;
			break;
		}

		if (Camera_bound.top < m_map_bound.top)
			eye.y = m_map_bound.top + CAMERA_FOLLOW_POINT_TOP_RATIO * height;
		else if (Camera_bound.bottom > m_map_bound.bottom)
			eye.y = m_map_bound.bottom - CAMERA_FOLLOW_POINT_BOTTOM_RATIO * height;

		//if (m_following->pos_x >= WIDTH_ROOM1)
		//{
		//	//eye.x += 32;
		//	//if (eye.x == WIDTH_ROOM1)
		//	//{
		//	//	
		//	//	//m_following->isActive = true;
		//	//}

		//	if (m_following->pos_x >= WIDTH_ROOM1 - GATE_BLOCK_WIDTH / 2
		//		&& Camera_bound.left <= WIDTH_ROOM1)
		//	{
		//		m_following->pos_x += m_following->getVelocityX() * t;
		//		/*if (m_following->pos_x >= WIDTH_ROOM1 + 96)
		//		m_following->pos_x = WIDTH_ROOM1 + 96;*/
		//	}
		//	eye.x = WIDTH_ROOM1 + CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
		//}
		
		//update camera bound
		Camera_bound.top = eye.y - CAMERA_FOLLOW_POINT_TOP_RATIO * height;
		Camera_bound.bottom = eye.y + CAMERA_FOLLOW_POINT_BOTTOM_RATIO * height;
		Camera_bound.left = eye.x - CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
		if (m_following->pos_x < WIDTH_ROOM1 + WIDTH_ROOM2 + 2 * WIDTH_ROOM_BOSS)
			Camera_bound.right = m_following->pos_x + CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;
		else
			Camera_bound.right = eye.x + CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;

		if (m_following->pos_x > WIDTH_ROOM1)
		{
			int leftCamera = eye.x - CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
			leftCamera += m_following->getCurrentTime();
			if (leftCamera == WIDTH_ROOM1)
				leftCamera = WIDTH_ROOM1;

			Camera_bound.top = eye.y - CAMERA_FOLLOW_POINT_TOP_RATIO * height;
			Camera_bound.bottom = eye.y + CAMERA_FOLLOW_POINT_BOTTOM_RATIO * height;
			Camera_bound.left = leftCamera;
			Camera_bound.right = m_following->pos_x + CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;
		}
	}

	D3DXMatrixLookAtLH(&viewMatrix, &eye, &(eye + direction), &up);
}

void Camera::SetTransform(DeviceManager* device) const
{
	device->getdevice()->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	//device->getdevice()->SetTransform(D3DTS_WORLD, &identityMatrix);
	device->getdevice()->SetTransform(D3DTS_VIEW, &viewMatrix);
}

void Camera::SetMapBoundary(RECT rect)
{
	m_map_bound = rect;
}






