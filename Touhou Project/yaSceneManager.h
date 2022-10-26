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

		static void Release();
	private:
		//ÀüÃ¼ ¾À
		static Scene* mScenes[(UINT)eSceneType::MAX];
		//ÇöÀç ¾À
		static Scene* mPlayScene;
	};
}