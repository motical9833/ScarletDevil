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

		// ������Ʈ tick �� ȣ���Ѵ�.
		Scene::Tick();
	}
	void LogoScene::Render(HDC hdc)
	{
		// ������Ʈ Render�� ȣ���Ѵ�.
		Scene::Render(hdc);
	}
}