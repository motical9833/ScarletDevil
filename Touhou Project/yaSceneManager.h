#pragma once
#include "Common.h"

namespace ya
{
	class Scene;
	class SceneManager
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);
		static void DestroyGameObject();
		static void Release();

		static void ChangeScene(eSceneType type);
		static Scene* GetPlayScene() { return mPlayScene; }
		static Scene* GetScene() { return mScenes[(UINT)eSceneType::Play]; }
		static void SetPlayScene(Scene* playScene) { mPlayScene = playScene; }
		//static PlayScene* SetPscene() { return pScene; }
	private:
		//ÀüÃ¼ ¾À
		static Scene* mScenes[(UINT)eSceneType::MAX];
		//ÇöÀç ¾À
		static Scene* mPlayScene;

		//static PlayScene* pScene;
	};
}