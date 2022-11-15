#include "yaLogoScene.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaBgImageObject.h"

namespace ya
{
	LogoScene::LogoScene()
	{

	}
	LogoScene::~LogoScene()
	{

	}
	void LogoScene::Initialize()
	{
		 

		BgImageObject* bg = new BgImageObject();
		bg->SetImage(L"LogoBG", L"BG_Img\\LogoBG.bmp");
		
		bg->Initialize();
		AddGameObject(bg,eColliderLayer::BackGround);
		

	}
	void LogoScene::Tick()
	{ 
		// 오브젝트 tick 을 호출한다.
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Title);
		}
	}
	void LogoScene::Render(HDC hdc)
	{
		// 오브젝트 Render를 호출한다.
		Scene::Render(hdc);

		wchar_t szFloat[50] = {};

		swprintf_s(szFloat, 50, L"Logo Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		//글자출력
		TextOut(hdc, 10, 30, szFloat, strLen);
	}
	void LogoScene::Enter()
	{

	}
	void LogoScene::Exit()
	{

	}
}