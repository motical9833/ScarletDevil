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

		//�̹��� �ε�
		//Bmp Image
		mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str()
			,IMAGE_BITMAP, 0, 0
			,LR_LOADFROMFILE|LR_CREATEDIBSECTION);

		if (mBitmap == nullptr)
		{
			return E_FAIL;
		}

		//Load�� �̹��� ���� ����
		BITMAP bitInfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		//�̹������� �귯�� �߰�
		HDC mainDC = Application::GetInstance().GetWindowData().hdc;
		mHdc = CreateCompatibleDC(mainDC);

		//�⺻ ��Ʈ��(�����ȭ��) ����
		HBITMAP prevBit = (HBITMAP)SelectObject(mHdc,mBitmap);
		DeleteObject(prevBit);


		return S_OK;
	}
}