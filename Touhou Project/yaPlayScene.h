#pragma once
#include "yaScene.h"

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

	private:

	};
}