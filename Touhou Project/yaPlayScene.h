#pragma once
#include "yaScene.h"
#include "yaGameObject.h"
#include "yaMonster.h"
#include "yaDanmaku.h"
#include "yaCollisionManager.h"
#include "yaCollider.h"
#include <array>

using namespace std;

namespace ya
{


	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();

		PlayScene* GetScene() { return this; }

		array <Danmaku*, 1024> danmaku;
		array <GameObject*, 1> enemy;
		GameObject* boss;


		GameObject* player;
	private:

	};
}