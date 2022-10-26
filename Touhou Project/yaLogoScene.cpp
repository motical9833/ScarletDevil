#include "yaLogoScene.h"
#include "yaPlayer.h"

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
		AddGameObject(new Player());
	}
	void LogoScene::Tick()
	{

		// 오브젝트 tick 을 호출한다.
		Scene::Tick();
	}
	void LogoScene::Render(HDC hdc)
	{
		// 오브젝트 Render를 호출한다.
		Scene::Render(hdc);
	}
}