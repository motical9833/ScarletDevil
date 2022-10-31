#pragma once
#include "yaResource.h"
namespace ya
{
	class Image : public Resource
	{
	public:
		Image();
		~Image();

		virtual HRESULT Load(const std::wstring& path) override;

		HDC GetDC() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		//�̹���
		HBITMAP mBitmap;

		HDC mHdc;

		//�̹��� ���μ��α���
		UINT mWidth;
		UINT mHeight;

	};


	class Sound : public Resource
	{
	public:
		Sound();
		~Sound();

		virtual HRESULT Load(const std::wstring& path) override;

		HDC GetDC() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		//�̹���
		HBITMAP mBitmap;

		HDC mHdc;

		//�̹��� ���μ��α���
		UINT mWidth;
		UINT mHeight;

	};
}

