 #pragma once

#include "framework.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <bitset>
#include <set>

#include <functional>

#include "def.h"
#include "Maths.h"


#pragma comment(lib,"Msimg32.lib")

//typedef Pos POINT;
//using Pos = POINT;

//typedef std::vector<std::vector<GameObject*>> GameObjects;
//typedef std::vector<GameObject*> LayerObjects;

struct WindowData
{
	HWND hWnd;
	HDC hdc;
	HBITMAP backTexture;
	HDC backBuffer;
	UINT height;
	UINT width;

	void clear()
	{
		hWnd = nullptr;
		hdc = nullptr;
		height = 0;
		width = 0;
	}
};

struct Pen
{
private:
	HDC mHdc;
	HPEN mOldPen;
	HPEN mPen;

public:
	Pen(HDC hdc)
		:mHdc(hdc)
		, mOldPen(NULL)
		, mPen(NULL)
	{

	}
	Pen(HDC hdc, HPEN pen)
		:mHdc(hdc)
		, mOldPen(NULL)
		, mPen(pen)
	{
		mOldPen = (HPEN)SelectObject(mHdc, pen);
	}
	~Pen()
	{
		SelectObject(mHdc, mOldPen);
		DeleteObject(mPen); 
	}

	void SetPen(HPEN pen)
	{
		mOldPen = (HPEN)SelectObject(mHdc, pen);
	}
};

struct Brush
{
private:
	HDC mHdc;
	HBRUSH mOldBrush;
	HBRUSH mBrush;

public:
	Brush(HDC hdc, HBRUSH brush)
		:mHdc(hdc)
		, mOldBrush(NULL)
		, mBrush(brush)
	{
		mOldBrush = (HBRUSH)SelectObject(mHdc, brush);
	}
	~Brush()
	{
		SelectObject(mHdc, mOldBrush);
		DeleteObject(mBrush);
	}
};