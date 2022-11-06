#include "yaSceneManager.h"
#include "yaLogoScene.h"
#include "yaTitleScene.h"
#include "yaPlayScene.h"
#include "yaEndScene.h"
#include "yaObject.h"
namespace ya
{
	Scene* SceneManager::mScenes[(UINT)eSceneType::MAX] = {};
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initialize()
	{
		//¸ğµç ¾À ÃÊ±âÈ­
		//·Î°í¾À ÃÊ±âÈ­
		mScenes[(UINT)eSceneType::Logo] = new LogoScene();
		ChangeScene(eSceneType::Logo);
		mScenes[(UINT)eSceneType::Logo]->Initialize();

		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Title]->Initialize();

		mScenes[(UINT)eSceneType::Play] = new PlayScene();
		mScenes[(UINT)eSceneType::Play]->Initialize();

		mScenes[(UINT)eSceneType::End] = new EndScene();
		mScenes[(UINT)eSceneType::End]->Initialize();

	}

	void SceneManager::Tick()
	{
		mPlayScene->Tick();
	}
	void SceneManager::Render(HDC hdc)
	{
		mPlayScene->Render(hdc);
	}
	void SceneManager::DestroyGameObject()
	{
		ya::object::Release();
	}
	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			delete scene;
			scene = nullptr;
		}
	}
	void SceneManager::ChangeScene(eSceneType tyep)
	{
		if (mPlayScene == nullptr)
		{
			mPlayScene = mScenes[(UINT)eSceneType::Logo];
		}
		else
		{
			mPlayScene->Exit();
			mPlayScene = mScenes[(UINT)tyep];
		}
		mPlayScene->Enter();
	}
}