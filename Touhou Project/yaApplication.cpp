#include "yaApplication.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaResources.h"
#include "yaCollisionManager.h"
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

		SceneManager::Tick();
		CollisionManager::Tick();
		//clear ����(���)
		Rectangle(mWindowData.backBuffer, -1, -1, mWindowData.width + 1, mWindowData.height + 1);


		SceneManager::Render(mWindowData.backBuffer);

		Input::Render(mWindowData.backBuffer);
		Time::Render(mWindowData.backBuffer);


		//BitBlt �Լ��� DC���� �̹����� �������ִ� �Լ�
		//ȭ�鿡 �׸���
		BitBlt(mWindowData.hdc,
			0, 0, mWindowData.width, mWindowData.height, mWindowData.backBuffer,
			0, 0,SRCCOPY);


		//Death()���°��� ������Ʈ ����
		//SceneManager::DestroyGameObject();
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

		//  ��Ʈ�� �ػ󵵸� �����ϱ� �� �� ���� ������ ũ�� ���
		RECT rect = { 0,0,mWindowData.width,mWindowData.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// ������ ũ�� ����
		SetWindowPos(mWindowData.hWnd,
			nullptr, 0, 0,
			rect.right - rect.left,
			rect.bottom - rect.top
			, 0);

		ShowWindow(mWindowData.hWnd, true);


		//��Ʈ������ ������� ���
		mWindowData.backTexture = 
			CreateCompatibleBitmap(mWindowData.hdc,mWindowData.width,mWindowData.height);

		mWindowData.backBuffer = CreateCompatibleDC(mWindowData.hdc);
		HBITMAP dafaultBitmap = 
			(HBITMAP)SelectObject(mWindowData.backBuffer, mWindowData.backTexture);

		DeleteObject(dafaultBitmap);

		// �޸� ���� ���־���Ѵ�.
		mPens[(UINT)ePenColor::Red] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		mPens[(UINT)ePenColor::Green] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		mPens[(UINT)ePenColor::Blue] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

		mBrushes[(UINT)eBrushColor::Transparent] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		mBrushes[(UINT)eBrushColor::Blakc] = (HBRUSH)GetStockObject(BLACK_BRUSH);
		mBrushes[(UINT)eBrushColor::Gray] = CreateSolidBrush(RGB(71, 71, 71));
		mBrushes[(UINT)eBrushColor::White] = (HBRUSH)GetStockObject(WHITE_BRUSH);
	}
}