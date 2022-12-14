#include "yaPlayScene.h"
#include "yaSceneManager.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaCollisionManager.h"
#include "yaBgImageObject.h"
#include "yaObject.h"
#include "yaDanmaku.h"
#include "yaResources.h"
#include "yaBossMonster.h"

namespace ya
{

	PlayScene::PlayScene()
	{

	}
	PlayScene::~PlayScene()
	{

	}
	void PlayScene::Initialize()
	{
		player = new Player();

		AddGameObject(player, eColliderLayer::Player);

		for (size_t i = 0; i < 1; i++)
		{
			enemy[i] = new Monster();
			AddGameObject(enemy[i], eColliderLayer::Monster);
			enemy[i]->Death();
		}

		boss = new BossMonster();
		AddGameObject(boss, eColliderLayer::Monster);
		  
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Projecttile, true);

		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Monster_Projecttile, true);

		Scene* playScene = SceneManager::GetScene();

		for (size_t i = 0; i < 1024; i++)
		{
			danmaku[i] = new Danmaku();
			playScene->AddGameObject(danmaku[i], eColliderLayer::Monster_Projecttile);
			danmaku[i]->Death();
			danmaku[i]->mImage = Resources::Load<Image>(L"EnemyDanmaku_01", L"..\\Resources\\Image\\Enemys_Img\\Enemy_Danmaku.bmp");
			danmaku[i]->SetSrc(16, 15);
		}
	}
	void PlayScene::Tick()
	{
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::End);
		}

		if (KEY_DOWN(eKeyCode::P))
		{
			enemy[0]->Alive();
		}
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[50] = {};

		swprintf_s(szFloat, 50, L"Play Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		//????????
		TextOut(hdc, 10, 30, szFloat, strLen);
	}

	void PlayScene::Enter()
	{

	}
	void PlayScene::Exit()
	{

	}
}
