#pragma once
#include <d3d9.h>
#include <vector>
#include <d3dx9.h>

static class Math
{
public:
	static bool isPointinRectangle(D3DXVECTOR2 point, RECT rect);
};
