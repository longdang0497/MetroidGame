#include "Math.h"

bool Math::isPointinRectangle(D3DXVECTOR2 point, RECT rect)
{
	if (point.x >= rect.left && point.x <= rect.right && point.y <= rect.bottom && point.y >= rect.top)
		return true;
	return false;
}