#pragma once
#include "yaScene.h"
#include "yaMonster.h"
#include "yaDanmaku.h"
#include <array>

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

		 std::array <Danmaku*, 1024> danmaku;


		 GameObject* player;
	private:

	};
}