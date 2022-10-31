#include "yaImage.h"
#include "yaApplication.h"
namespace ya
{
	Image::Image()
		:mBitmap(NULL)
		,mHdc(NULL)
		,mWidth(0)
		,mHeight(0)
	{

	}
	Image::~Image()
	{
		HWND hwnd = Application::GetInstance().GetWindowData().hWnd;
		ReleaseDC(hwnd, mHdc);
	}
	HRESULT Image::Load(const std::wstring& path)
	{

		//이미지 로드
		//Bmp Image
		mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str()
			,IMAGE_BITMAP, 0, 0
			,LR_LOADFROMFILE|LR_CREATEDIBSECTION);

		if (mBitmap == nullptr)
		{
			return E_FAIL;
		}

		//Load한 이미지 정보 저장
		BITMAP bitInfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		//이미지별로 브러쉬 추가
		HDC mainDC = Application::GetInstance().GetWindowData().hdc;
		mHdc = CreateCompatibleDC(mainDC);

		//기본 비트맵(흰색도화지) 제거
		HBITMAP prevBit = (HBITMAP)SelectObject(mHdc,mBitmap);
		DeleteObject(prevBit);


		return S_OK;
	}
}