#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Image;
	class Player : public GameObject
	{
	public:
		Player();
		~Player();

		virtual void Tick() override;
		virtual void Render(HDC hec) override;


	private:
		float mSpeed;
		Image* mImage;
	};
}