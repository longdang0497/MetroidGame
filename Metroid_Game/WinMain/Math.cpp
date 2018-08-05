#include "Math.h"

bool Math::isPointinRectangle(D3DXVECTOR2 point, RECT rect)
{
	if (point.x >= rect.left && point.x <= rect.right && point.y <= rect.bottom && point.y >= rect.top)
		return true;
	return false;
}

float Math::distance(D3DXVECTOR2 point1, D3DXVECTOR2 point2)
{
	float result;
	result = (float)sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
	return result;
}

int Math::abs(int a, int b) 
{
	return (a - b)*((a - b) % 1);
}