#include "Camera.h"
#include "Samus.h"
Camera::Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors)
{
	this->startPosX = 0.0f;
	this->endPosX = 0.0f;

	this->isChangingRoom = false;
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

		// Cập nhật vị trí của camera
		Samus* samus = dynamic_cast<Samus*>(m_following);

		if (samus->getIsChangingRoom()) {
			switch (samus->getRoomNum())
			{
			case ROOM1:
				if (this->startPosX == 0.0f) {
					this->startPosX = m_map_bound.right;
				}

				//xet dieu kien chua qua nua 1/2 man camera, thi cap nhat theo right cua room
				if (Camera_bound.right - WIDTH_ROOM1 > 320) {
					this->endPosX = m_map_bound.left;
				}
				else {
					this->endPosX = m_map_bound.right;
				}

				//di chuyen left cua room khi samus dung giua man hinh
				if (this->endPosX >= WIDTH_ROOM1 + 320) {
					m_map_bound.left = WIDTH_ROOM1 - 320;
				}

				//day camera qua phai
				if (this->endPosX - this->startPosX <= 320 && this->endPosX - this->startPosX >= 0) {
					m_map_bound.right += 10;
				}
				else if (this->endPosX - this->startPosX >= -320 && this->endPosX - this->startPosX <= 0) {
					//m_map_bound.right += 10;
					m_map_bound.left += 10;
				}

				//day camera qua phai
				if (this->endPosX - this->startPosX <= 320 && this->endPosX - this->startPosX >= 0) {
					m_map_bound.right += 10;
				}
				else if (this->endPosX - this->startPosX >= -320 && this->endPosX - this->startPosX <= 0) {
					//m_map_bound.right += 10;
					m_map_bound.left += 10;
				}
				//khi day camera hoan toan qua room tiep theo
				else if (Camera_bound.right - m_map_bound.left >= 640) {
					m_map_bound.left = WIDTH_ROOM1;
					m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2;
					samus->setIsChangingRoom(false);
					samus->setRoomNum(ROOM2);
					this->startPosX = 0.0f;
					this->endPosX = 0.0f;
				}
				break;
			case ROOM2:
				if (this->startPosX == 0.0f) {
					this->startPosX = m_map_bound.right;
				}

				//xet dieu kien chua qua nua 1/2 man camera, thi cap nhat theo right cua room
				if (Camera_bound.right - (WIDTH_ROOM1 + WIDTH_ROOM2) > 320) {
					this->endPosX = m_map_bound.left;
				}
				else {
					this->endPosX = m_map_bound.right;
				}

				//di chuyen left cua room khi samus dung giua man hinh
				if (this->endPosX >= WIDTH_ROOM1 + WIDTH_ROOM2 + 320) {
					m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2 - 320;
				}

				//day camera qua phai
				if (this->endPosX - this->startPosX <= 320 
					&& this->endPosX - this->startPosX >= 0) {
					m_map_bound.right += 10;
				}
				else if (this->endPosX - this->startPosX >= -320 
					&& this->endPosX - this->startPosX <= 0) {
					//m_map_bound.right += 10;
					m_map_bound.left += 10;
				}

				//day camera qua phai
				if (this->endPosX - this->startPosX <= 320 
					&& this->endPosX - this->startPosX >= 0) {
					m_map_bound.right += 10;
				}
				else if (this->endPosX - this->startPosX >= -320 
					&& this->endPosX - this->startPosX <= 0) {
					//m_map_bound.right += 10;
					m_map_bound.left += 10;
				}
				//khi day camera hoan toan qua room tiep theo
				else if (Camera_bound.right - m_map_bound.left >= 640) {
					m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2;
					m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS;
					samus->setIsChangingRoom(false);
					samus->setRoomNum(BOSS1);
					this->startPosX = 0.0f;
					this->endPosX = 0.0f;
				}
				break;
			case BOSS1:
				if (this->startPosX == 0.0f) {
					this->startPosX = m_map_bound.right;
				}

				//xet dieu kien chua qua nua 1/2 man camera, thi cap nhat theo right cua room
				if (Camera_bound.right - (WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS) > 320) {
					this->endPosX = m_map_bound.left;
				}
				else {
					this->endPosX = m_map_bound.right;
				}

				//di chuyen left cua room khi samus dung giua man hinh
				if (this->endPosX >= WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS + 320) {
					m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS - 320;
				}

				//day camera qua phai
				if (this->endPosX - this->startPosX <= 320
					&& this->endPosX - this->startPosX >= 0) {
					m_map_bound.right += 10;
				}
				else if (this->endPosX - this->startPosX >= -320
					&& this->endPosX - this->startPosX <= 0) {
					//m_map_bound.right += 10;
					m_map_bound.left += 10;
				}

				//day camera qua phai
				if (this->endPosX - this->startPosX <= 320
					&& this->endPosX - this->startPosX >= 0) {
					m_map_bound.right += 10;
				}
				else if (this->endPosX - this->startPosX >= -320
					&& this->endPosX - this->startPosX <= 0) {
					//m_map_bound.right += 10;
					m_map_bound.left += 10;
				}
				//khi day camera hoan toan qua room tiep theo
				else if (Camera_bound.right - m_map_bound.left >= 640) {
					m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS;
					m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2 + 2 * WIDTH_ROOM_BOSS;
					samus->setIsChangingRoom(false);
					samus->setRoomNum(BOSS2);
					this->startPosX = 0.0f;
					this->endPosX = 0.0f;
				}
				break;
			}
		}

		//switch (samus->getRoomNum())
		//{
		//case ROOM1:
		//	
		//	break;
		///*case ROOM2:
		//	if (samus->getIsChangingRoom()) {
		//		if (this->startPosX == 0.0f) {
		//			this->startPosX = m_map_bound.right;
		//		}
		//		xet dieu kien chua qua nua 1/2 man camera, thi cap nhat theo right cua room
		//		if (Camera_bound.right - (WIDTH_ROOM1 + WIDTH_ROOM2) > 320) {
		//			this->endPosX = m_map_bound.left;
		//		}
		//		else {
		//			this->endPosX = m_map_bound.right;
		//		}
		//		di chuyen left cua room khi samus dung giua man hinh
		//		if (this->endPosX >= WIDTH_ROOM1 + WIDTH_ROOM2 + 320) {
		//			m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2 - 320;
		//		}

		//		day camera qua phai
		//		if (this->endPosX - this->startPosX <= 320 && this->endPosX - this->startPosX >= 0) {
		//			m_map_bound.right += 8;
		//		}
		//		else if (this->endPosX - this->startPosX >= -320 && this->endPosX - this->startPosX <= 0) {
		//			m_map_bound.right += 10;
		//			m_map_bound.left += 8;
		//		}
		//		khi day camera hoan toan qua room tiep theo
		//		else if (Camera_bound.right - m_map_bound.left >= 640) {
		//			m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2;
		//			m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS;
		//			samus->setIsChangingRoom(false);
		//			this->startPosX = 0.0f;
		//			this->endPosX = 0.0f;
		//		}
		//	}
		//	break;
		//case BOSS1:
		//	if (samus->getIsChangingRoom()) {
		//		if (this->startPosX == 0.0f) {
		//			this->startPosX = m_map_bound.right;
		//		}

		//		xet dieu kien chua qua nua 1/2 man camera, thi cap nhat theo right cua room
		//		if (Camera_bound.right - (WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS) > 320) {
		//			this->endPosX = m_map_bound.left;
		//		}
		//		else {
		//			this->endPosX = m_map_bound.right;
		//		}

		//		di chuyen left cua room khi samus dung giua man hinh
		//		if (this->endPosX >= WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS + 320) {
		//			m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2 - 320;
		//		}

		//		day camera qua phai
		//		if (this->endPosX - this->startPosX <= 320 && this->endPosX - this->startPosX >= 0) {
		//			m_map_bound.right += 8;
		//		}
		//		else if (this->endPosX - this->startPosX >= -320 && this->endPosX - this->startPosX <= 0) {
		//			m_map_bound.right += 10;
		//			m_map_bound.left += 8;
		//		}
		//		khi day camera hoan toan qua room tiep theo
		//		else if (Camera_bound.right - m_map_bound.left >= 640) {
		//			m_map_bound.left = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS;
		//			m_map_bound.right = WIDTH_ROOM1 + WIDTH_ROOM2 + 2 * WIDTH_ROOM_BOSS;
		//			samus->setIsChangingRoom(false);
		//			this->startPosX = 0.0f;
		//			this->endPosX = 0.0f;
		//		}
		//	}
		//	break;*/
		//}
		
		//m_map_bound.right = 2272;

		//set bound camera
		Camera_bound.top = m_map_bound.top - CAMERA_FOLLOW_POINT_TOP_RATIO * height;
		Camera_bound.bottom = m_map_bound.bottom + CAMERA_FOLLOW_POINT_BOTTOM_RATIO * height;
		Camera_bound.left = m_following->pos_x - CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
		Camera_bound.right = m_following->pos_x + CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;

		//check camera vs map bound
		//switch (m_following->getRoomNum()) {
		//case ROOM1:
		//	if (Camera_bound.left < m_map_bound.left)
		//		eye.x = m_map_bound.left + CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
		//	else if (Camera_bound.right > WIDTH_ROOM1)
		//		eye.x = WIDTH_ROOM1 - CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;
		//	break;
		//case ROOM2:
		//	if (Camera_bound.left < WIDTH_ROOM1)
		//		eye.x = WIDTH_ROOM1 + CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
		//	else if (Camera_bound.right > WIDTH_ROOM1 + WIDTH_ROOM2)
		//		eye.x = WIDTH_ROOM1 + WIDTH_ROOM2 - CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;
		//	break;
		//case BOSS1:
		//	if (Camera_bound.left < WIDTH_ROOM1 + WIDTH_ROOM2)
		//	{
		//		//eye.x += 64 * m_following->getCurrentTime();
		//		//if (eye.x == WIDTH_ROOM1 + WIDTH_ROOM2)
		//			eye.x = WIDTH_ROOM1 + WIDTH_ROOM2 + CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
		//	}
		//	else if (Camera_bound.right > WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS)
		//		eye.x = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS - CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;
		//	break;
		//case BOSS2:
		//	if (Camera_bound.left < WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS)
		//	{
		//		//eye.x += 64 * m_following->getCurrentTime();
		//		//if (eye.x == WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS)
		//			eye.x = WIDTH_ROOM1 + WIDTH_ROOM2 + WIDTH_ROOM_BOSS + CAMERA_FOLLOW_POINT_LEFT_RATIO * width;
		//	}
		//	else if (Camera_bound.right > WIDTH_ROOM1 + WIDTH_ROOM2 + 2 * WIDTH_ROOM_BOSS)
		//		eye.x = WIDTH_ROOM1 + WIDTH_ROOM2 + 2 * WIDTH_ROOM_BOSS - CAMERA_FOLLOW_POINT_RIGHT_RATIO * width;
		//	break;
		//}

		
		//update camera bound
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
	//device->getdevice()->SetTransform(D3DTS_WORLD, &identityMatrix);
	device->getdevice()->SetTransform(D3DTS_VIEW, &viewMatrix);
}

void Camera::SetMapBoundary(RECT rect)
{
	m_map_bound = rect;
	m_map_bound.right = WIDTH_ROOM1;
}






