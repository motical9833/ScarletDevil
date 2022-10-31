#include "yaApplication.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResources.h"
namespace ya
{
	//Application Application::mInstance;
	void Application::Initialize(WindowData data)
	{
		initializeWindow(data);


		Time::Initialize();
		Input::Initialize();

		SceneManager::Initialize();
	}

	void Application::Tick()
	{
		Time::Tick();
		Input::Tick();

		//clear 배경색(흰색)
		Rectangle(mWindowData.backBuffer, -1, -1, mWindowData.width + 1, mWindowData.height + 1);


		SceneManager::Tick();
		SceneManager::Render(mWindowData.backBuffer);

		Input::Render(mWindowData.backBuffer);
		Time::Render(mWindowData.backBuffer);


		//BitBlt 함수는 DC간에 이미지를 복사해주는 함수
		BitBlt(mWindowData.hdc,
			0, 0, mWindowData.width, mWindowData.height, mWindowData.backBuffer,
			0, 0,SRCCOPY);
	}
	 
	Application::Application()
	{
		mWindowData.clear();
	}

	Application::~Application()
	{
		SceneManager::Release();
		Resources::Release();

		ReleaseDC(mWindowData.hWnd, mWindowData.hdc);
		ReleaseDC(mWindowData.hWnd, mWindowData.backBuffer);

	}

	void Application::initializeWindow(WindowData data)
	{
		mWindowData = data;
		mWindowData.hdc = GetDC(data.hWnd);

		//  비트맵 해상도를 설정하기 위 한 실제 윈도우 크기 계산
		RECT rect = { 0,0,mWindowData.width,mWindowData.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// 윈도우 크기 변경
		SetWindowPos(mWindowData.hWnd,
			nullptr, 0, 0,
			rect.right - rect.left,
			rect.bottom - rect.top
			, 0);

		ShowWindow(mWindowData.hWnd, true);


		//비트맵으로 더블버퍼 기능
		mWindowData.backTexture = 
			CreateCompatibleBitmap(mWindowData.hdc,mWindowData.width,mWindowData.height);

		mWindowData.backBuffer = CreateCompatibleDC(mWindowData.hdc);
		HBITMAP dafaultBitmap = 
			(HBITMAP)SelectObject(mWindowData.backBuffer, mWindowData.backTexture);

		DeleteObject(dafaultBitmap);
	}
}