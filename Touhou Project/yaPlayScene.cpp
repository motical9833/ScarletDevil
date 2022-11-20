#include "yaPlayScene.h"
#include "yaSceneManager.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"
#include "yaBgImageObject.h"
#include "yaObject.h"
#include "yaDanmaku.h"
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
		AddGameObject(new Player(),eColliderLayer::Player);

		Monster* monster = new Monster();
		
		monster->pScene = this;
		AddGameObject(monster, eColliderLayer::Monster);

		//mon = monster;

	    //AddGameObject(new Monster(), eColliderLayer::Monster);

		//ya::object::Instantiate<Monster>(eColliderLayer::Monster);
		  
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Projecttile, true);

		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Monster_Projecttile, true);

		Scene* playScene = SceneManager::GetScene();
		for (size_t i = 0; i < 1024; i++)
		{
			danmaku[i] = new Danmaku();
			playScene->AddGameObject(danmaku[i], eColliderLayer::Monster_Projecttile);
			danmaku[i]->Death();
		}
	}
	void PlayScene::Tick()
	{
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::End);
		}
		 
		//ya::object::Destory(mon, 3.0f);
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[50] = {};

		swprintf_s(szFloat, 50, L"Play Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		//글자출력
		TextOut(hdc, 10, 30, szFloat, strLen);
	}

	void PlayScene::Enter()
	{

	}
	void PlayScene::Exit()
	{

	}
}
