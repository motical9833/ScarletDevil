#include "yaEndScene.h"
#include "yaBgImageObject.h"

namespace ya
{
	EndScene::EndScene()
	{

	}
	EndScene::~EndScene()
	{

	}
	void EndScene::Initialize()
	{
		BgImageObject* bg = new BgImageObject();
		bg->SetImage(L"PlaySceneBground", L"BG_Img\\PlaySceneBG.bmp");
		bg->SetPos({10.0f,10.0f});
		bg->Initialize();
		AddGameObject(bg, eColliderLayer::BackGround);
	}
	void EndScene::Tick()
	{
		Scene::Tick();
	}
	void EndScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[50] = {};

		swprintf_s(szFloat, 50, L"End Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		//글자출력
		TextOut(hdc, 10, 30, szFloat, strLen);
	}
	void EndScene::Enter()
	{
	}
	void EndScene::Exit()
	{
	}
}