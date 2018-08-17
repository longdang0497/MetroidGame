#include "Camera.h"
#include "Samus.h"
#include <d3d9.h>

Camera::Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors)
{
	this->startPosX = 0.0f;
	this->endPosX = 0.0f;

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

void Camera::Update()
{
	D3DXVECTOR3 eye(320, 352, 1);	// x,y not important, camera've been following m_following
	D3DXVECTOR3 direction(0, 0, -1);
	D3DXVECTOR3 up(0, -1, 0);	

	if (m_following != nullptr)
	{
		//camera follow object
		eye.x = m_following->pos_x;
		eye.y = m_following->pos_y;

		// Cập nhật vị trí của camera
		Samus* samus = dynamic_cast<Samus*>(m_following);
		
		//chuyển room từ trái qua phải
		if (samus->getIsChangingRoomLR()) {
			switch (samus->getRoomNum())
			{
			case ROOM1:
			{
				if (this->startPosX == 0.0f) {
					this->startPosX = m_map_bound.right;
				}

				// Khi mà camera qua đứng giữa nhân vật thì set lại qua bên trái
				if (Camera_bound.right - WIDTH_ROOM1 >= 320) {
					this->endPosX = m_map_bound.left;
					//m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2 - 320;
				}
				else {
					this->endPosX = m_map_bound.right;
				}

				//di chuyen left cua room khi samus dung giua man hinh
				if (this->endPosX >= WIDTH_ROOM1 + 320) {
					m_map_bound.left = WIDTH_ROOM1 - 320;
				}

				// day camera qua phai
				if (this->endPosX - this->startPosX <= 320 && this->endPosX - this->startPosX >= 0) {
					m_map_bound.right += 5;
				}
				else if (this->endPosX - this->startPosX >= -320 && this->endPosX - this->startPosX < 0) {
					m_map_bound.left += 5;
				}
				if (m_map_bound.left >= WIDTH_ROOM1) {
					m_map_bound.left = WIDTH_ROOM1;
					m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2;
					samus->setIsChangingRoomLR(false);
					samus->setRoomNum(ROOM2);
					samus->setStartMovingAfterRoomChanged(true);
					this->startPosX = 0.0f;
					this->endPosX = 0.0f;

				}
				break;
			}
			case ROOM2:
			{
				if (this->startPosX == 0.0f) {
					this->startPosX = m_map_bound.right;
				}

				// Khi mà camera qua đứng giữa nhân vật thì set lại qua bên trái
				if (Camera_bound.right - (WIDTH_ROOM1 + WIDTH_ROOM2) >= 320) {
					this->endPosX = m_map_bound.left;
					//m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS - 320;
				}
				else {
					this->endPosX = m_map_bound.right;
				}

				//di chuyen left cua room khi samus dung giua man hinh
				if (this->endPosX >= WIDTH_ROOM1 + WIDTH_ROOM2 + 320) {
					m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2 + - 320;
				}

				// day camera qua phai
				if (this->endPosX - this->startPosX <= 320 && this->endPosX - this->startPosX >= 0) {
					m_map_bound.right += 5;
				}
				else if (this->endPosX - this->startPosX >= -320 && this->endPosX - this->startPosX < 0) {
					m_map_bound.left += 5;
				}
				if (m_map_bound.left >= WIDTH_ROOM1) {
					m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2;
					m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS;
					samus->setIsChangingRoomLR(false);
					samus->setRoomNum(BOSS1);
					samus->setStartMovingAfterRoomChanged(true);
					this->startPosX = 0.0f;
					this->endPosX = 0.0f;

				}
				break;
			}
			case BOSS1:
			{
				if (this->startPosX == 0.0f) {
					this->startPosX = m_map_bound.right;
				}

				// Khi mà camera qua đứng giữa nhân vật thì set lại qua bên trái
				if (Camera_bound.right - (WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS) >= 320) {
					this->endPosX = m_map_bound.left;
					//m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS - 320;
				}
				else {
					this->endPosX = m_map_bound.right;
				}

				//di chuyen left cua room khi samus dung giua man hinh
				if (this->endPosX >= WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS + 320) {
					m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS - 320;
				}

				// day camera qua phai
				if (this->endPosX - this->startPosX <= 320 && this->endPosX - this->startPosX >= 0) {
					m_map_bound.right += 5;
				}
				else if (this->endPosX - this->startPosX >= -320 && this->endPosX - this->startPosX < 0) {
					m_map_bound.left += 5;
				}
				if (m_map_bound.left >= WIDTH_ROOM1) {
					m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS;
					m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2 + 2 * WIDTH_ROOM_BOSS;
					samus->setIsChangingRoomLR(false);
					samus->setRoomNum(BOSS2);
					samus->setStartMovingAfterRoomChanged(true);
					this->startPosX = 0.0f;
					this->endPosX = 0.0f;

				}
				break;
			}
			}
		}

		//chuyển room từ phải qua trái
		if (samus->getIsChangingRoomRL()) {
			switch (samus->getRoomNum())
			{
			case ROOM2:
			{
				//m_map_bound.left = WIDTH_ROOM1;
				if (this->startPosX == 0.0f) {
					this->startPosX = m_map_bound.left;
				}

				// Khi mà camera qua đứng giữa nhân vật thì set lại qua bên phải
				if (Camera_bound.left <= WIDTH_ROOM1 - 320) {
					this->endPosX = m_map_bound.right;
					//m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2 - 320;
				}
				else {
					this->endPosX = m_map_bound.left;
				}

				//di chuyen left cua room khi samus dung giua man hinh
				if (this->endPosX <= WIDTH_ROOM1 - 320) {
					m_map_bound.right = WIDTH_ROOM1 + 320;
				}

				// day camera qua trai
				if (this->endPosX - this->startPosX <= 320 && this->endPosX - this->startPosX >= 0) {
					m_map_bound.left -= 5;
				}
				else if (this->endPosX - this->startPosX >= -320 && this->endPosX - this->startPosX <= 0) {
					m_map_bound.right -= 5;
				}
				if (m_map_bound.right <= WIDTH_ROOM1) {
					m_map_bound.right = WIDTH_ROOM1;
					m_map_bound.left = 0;
					samus->setIsChangingRoomRL(false);
					samus->setRoomNum(ROOM1);
					samus->setStartMovingAfterRoomChanged(true);
					this->startPosX = 0.0f;
					this->endPosX = 0.0f;
				}
				break;
			}
			case BOSS1:
			{
				//if (this->startPosX == 0.0f) {
				//	this->startPosX = m_map_bound.right;
				//}

				//// Khi mà camera qua đứng giữa nhân vật thì set lại qua bên trái
				//if (Camera_bound.right - (WIDTH_ROOM1 + WIDTH_ROOM2) >= 320) {
				//	this->endPosX = m_map_bound.left;
				//	//m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS - 320;
				//}
				//else {
				//	this->endPosX = m_map_bound.right;
				//}

				////di chuyen left cua room khi samus dung giua man hinh
				//if (this->endPosX >= WIDTH_ROOM1 + WIDTH_ROOM2 + 320) {
				//	m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2 + -320;
				//}

				//// day camera qua phai
				//if (this->endPosX - this->startPosX <= 320 && this->endPosX - this->startPosX >= 0) {
				//	m_map_bound.right += 5;
				//}
				//else if (this->endPosX - this->startPosX >= -320 && this->endPosX - this->startPosX < 0) {
				//	m_map_bound.left += 5;
				//}
				//if (m_map_bound.left >= WIDTH_ROOM1) {
				//	m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2;
				//	m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS;
				//	samus->setIsChangingRoom(false);
				//	samus->setRoomNum(BOSS1);
				//	samus->setStartMovingAfterRoomChanged(true);
				//	this->startPosX = 0.0f;
				//	this->endPosX = 0.0f;

				//}
				break;
			}
			case BOSS2:
			{
				//if (this->startPosX == 0.0f) {
				//	this->startPosX = m_map_bound.right;
				//}

				//// Khi mà camera qua đứng giữa nhân vật thì set lại qua bên trái
				//if (Camera_bound.right - (WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS) >= 320) {
				//	this->endPosX = m_map_bound.left;
				//	//m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS - 320;
				//}
				//else {
				//	this->endPosX = m_map_bound.right;
				//}

				////di chuyen left cua room khi samus dung giua man hinh
				//if (this->endPosX >= WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS + 320) {
				//	m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS + -320;
				//}

				//// day camera qua phai
				//if (this->endPosX - this->startPosX <= 320 && this->endPosX - this->startPosX >= 0) {
				//	m_map_bound.right += 5;
				//}
				//else if (this->endPosX - this->startPosX >= -320 && this->endPosX - this->startPosX < 0) {
				//	m_map_bound.left += 5;
				//}
				//if (m_map_bound.left >= WIDTH_ROOM1) {
				//	m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS;
				//	m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2 + 2 * WIDTH_ROOM_BOSS;
				//	samus->setIsChangingRoom(false);
				//	samus->setRoomNum(BOSS2);
				//	samus->setStartMovingAfterRoomChanged(true);
				//	this->startPosX = 0.0f;
				//	this->endPosX = 0.0f;

				//}
				break;
			}
			}
		}

		//set bound camera
		Camera_bound.top = m_map_bound.top - CAMERA_FOLLOW_POINT_TOP_RATIO * height;
		Camera_bound.bottom = m_map_bound.bottom + CAMERA_FOLLOW_POINT_BOTTOM_RATIO * height;
		Camera_bound.left	= m_following->pos_x - CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
		Camera_bound.right	= m_following->pos_x + CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;

		//check camera vs map bound
		if (Camera_bound.left < m_map_bound.left)
			eye.x = m_map_bound.left + CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
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
	device->getdevice()->SetTransform(D3DTS_VIEW, &viewMatrix);
}

void Camera::SetMapBoundary(RECT rect)
{
	m_map_bound = rect;
	m_map_bound.right = WIDTH_ROOM1; // +WIDTH_ROOM2 + WIDTH_ROOM_BOSS;
	//m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2;
}






