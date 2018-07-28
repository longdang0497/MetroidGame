﻿#include "Collision.h"

Collision::Collision() {
	//this->center = center;
	//this->halfSize = halfsize;
}

Collision::~Collision() {

}

Collision::Collision(float x, float y, float width, float height, float vX, float vY) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->vX = vX;
	this->vY = vY;
}

// Cai thuat toan nay dung de tinh thoi gian va cham
// Bản chất có thể hiểu là mỗi lần frame update bình thường thì sẽ chạy với vận tốc thì được quãng đường là x = v * t (trường hợp ở đây hiểu là 1s chạy được x quãng đường)
// Sau đó mình dùng thuật toán này để xác định trọng số của t lại, ví dụ thay vì chạy 1s là đc quãng đường x là thực tế, nhưng khi xét có va chạm thì 0.3s là có va chạm rồi, 
// Lúc này mình sẽ cho object di chuyển với thời gian là 0.5s thôi (hoặc là chạy với quãng đường bằng 0.3 / 1 so với quãng đường bình thường).
// Còn khoảng còn lại (ở đây là 1 - 0.3 = 0.7) dùng để xác định loại va chạm và đoạn đường đi tới đâu so với trường hợp va chạm mà mình xét).
float Collision::sweptAABB(GameObject* object, float normalX, float normalY) {
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// tim khoang cach giua 2 vat the 
	if (this->vX > 0.0f) {
		xInvEntry = object->getPosX() - (this->x + this->width);
		xInvExit = (object->getWidth() + object->getPosX()) - this->x;
	}
	else {
		xInvEntry = (object->getPosX() + object->getWidth()) - this->x;
		xInvExit = object->getPosX() - (this->x + this->width);
	}

	if (this->vY > 0.0f) {
		yInvEntry = object->getPosY() - (this->y + this->height);
		yInvExit = (object->getPosY() + object->getHeight()) - this->y;
	}
	else {
		yInvEntry = (object->getPosY() + object->getHeight()) - this->y;
		yInvExit = object->getPosY() - (this->y + this->height);
	}

	// Tinh khoang thoi gian va cham va thoi gian het va cham
	float xEntry, yEntry;
	float xExit, yExit;
	if (this->vX == 0.0f) {
		xEntry = std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else {
		xEntry = xInvEntry / this->vX;
		xExit = xInvExit / this->vY;
	}

	if (this->vY == 0.0f) {
		yEntry = std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else {
		yEntry = yInvEntry / this->vY;
		yExit = yInvExit / this->vY;
	}

	// Xac dinh truc nao bi va cham dau tien
	// --- thời gian va chạm theo 2 chiều
	float entryTime = max(xEntry, yEntry);      // Cho biet thoi gian bat dau va cham
	float exitTime = min(xExit, yExit);			// Cho biet thoi gian ket thuc va cham

												// neu khong co va cham
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f) {
		normalX = 0.0f;
		normalY = 0.0f;
		return 1.0f;
	}
	else {
		if (xEntry > yEntry) { // này là đã va chạm ở trục Y rồi
			if (xInvEntry < 0.0f) {  // Trường hợp nhân vật bị dính với object đang xét
				normalX = 1.0f;
				normalY = 0.0f;
			}
			else {					// Nếu chưa dính
				normalX = -1.0f;
				normalY = 0.0f;
			}
		}
		else {			// Này là va chạm với trục X rồi nè
			if (yInvEntry < 0.0f) {
				normalX = 0.0f;
				normalY = 1.0f;
			}
			else {
				normalX = 0.0f;
				normalY = -1.0f;
			}
		}
	}

	// Trả về thời gian va chạm
	return entryTime;
}

// Cap nhat lai vi tri bouding box khi co va cham xay ra
// Sau đó là sẽ xét va chạm.
// Đối với nhân vật thì có 2 loại va chạm: đẩy lùi khi trúng quái / đạn, trượt khi trúng tường dọc
// Đối với quái thì chỉ có:
//			+ con bò ngang thì theo tường sẽ chuyển sprite bò ngang theo tường
//			+ các con còn lại đạn bắn thì sẽ dần biến mất
void Collision::update(GameObject* object) {
	float collisionTime = sweptAABB(object, normalX, normalY);

	this->x += this->vX * collisionTime;
	this->y += this->vY * collisionTime;
	this->remainingTime = 1.0f - collisionTime;

	// Bị dội lại
	this->vX *= this->remainingTime;
	this->vY *= this->remainingTime;
	if (abs(this->normalX) > 0.001f)
		this->vX = -this->vX;
	if (abs(this->normalY) > 0.0001f)
		this->vY = -this->vY;

	// Bị trượt
	float dotProd = (this->vX * this->normalY + this->vY + this->normalX) * this->remainingTime;
	this->vX = dotProd * this->normalY;
	this->vY = dotProd * this->normalX;
}

bool Collision::isInside(RECT object, RECT other)
{
	bool top = object.top >= other.top && object.top <= other.bottom;
	bool bot = object.bottom >= other.top && object.bottom <= other.bottom;
	bool right = object.right <= other.right && object.right >= other.left;
	bool left = object.left <= other.right && object.left >= other.left;

	//va chạm góc trái trên - dưới object
	bool first_case = (left && bot) || (left && top);

	//va chạm góc phải trên - dưới object
	bool second_case = (right && bot) || (right && top);

	//va chạm object bao luôn other trái hoặc phải
	bool third_caseA = left && (object.bottom >= other.bottom) && (object.top <= other.top);
	bool third_caseB = right && (object.bottom >= other.bottom) && (object.top <= other.top);
	bool third_caseC = top && bot && right && (object.left <= other.left) && (object.left < other.right);
	bool third_caseD = top && bot && left && (object.right >= other.right && (object.right > other.right));
	bool third_case = third_caseA || third_caseB || third_caseC || third_caseD;

	//va chạm object bao luôn other trên hoặc dưới
	bool fourth_caseA = top && (object.left >= other.left) && (object.right <= other.right);
	bool fourth_caseB = bot && (object.left >= other.left) && (object.right <= other.right);
	bool fourth_caseC = top && (object.bottom >= other.bottom) && (object.left <= other.left) && (object.right >= other.right);
	bool fourth_caseD = bot && (object.top <= other.top) && (object.left <= other.left) && (object.right >= other.right);
	bool fourth_case = fourth_caseA || fourth_caseB || fourth_caseC || fourth_caseD;

	//other nằm bên trong object
	bool fifth_case_top = (object.top <= other.top) && (object.top < other.bottom);
	bool fifth_case_bot = (object.bottom > other.top) && (object.bottom >= other.bottom);
	bool fifth_case_left = (object.left <= other.left) && (object.left < other.right);
	bool fifth_case_right = (object.right > other.left) && (object.right >= other.right);
	bool fifth_case = fifth_case_top && fifth_case_bot &&fifth_case_right && fifth_case_left;


	if (first_case || second_case || third_case || fourth_case || fifth_case)
		return true;

	return false;
}

bool Collision::Overlaps(AABB other)
{
	if (Math::abs(collision.center.x, other.center.x) > collision.halfSize.x + other.halfSize.x) return false;
	if (Math::abs(collision.center.y, other.center.y) > collision.halfSize.y + other.halfSize.y) return false;
	return true;
}

float Collision::getX() {
	return this->x;
}

void Collision::setX(float x) {
	this->x = x;
}

float Collision::getY() {
	return this->y;
}


void Collision::setY(float y) {
	this->y = y;
}

float Collision::getWidth() {
	return this->width;
}

void Collision::setWidth(float width) {
	this->width = width;
}

float Collision::getHeight() {
	return this->height;
}

void Collision::setHeight(float height) {
	this->height = height;
}

float Collision::getVX() {
	return this->vX;
}

void Collision::setVX(float vX) {
	this->vX = vX;
}

float Collision::getVY() {
	return this->vY;
}

void Collision::setVY(float vY) {
	this->vY = vY;
}

float Collision::getNormalX() {
	return this->normalX;
}

float Collision::getNormalY() {
	return this->normalY;
}

float Collision::getRemainingTime() {
	return this->remainingTime;
}