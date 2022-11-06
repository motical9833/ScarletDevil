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

		static void ChangeScene(eSceneType tyep);
		static Scene* GetPlayScene() { return mPlayScene; }
	private:
		//��ü ��
		static Scene* mScenes[(UINT)eSceneType::MAX];
		//���� ��
		static Scene* mPlayScene;
	};
}