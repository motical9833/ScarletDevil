#pragma once
#include "yaGameObject.h"
#include "yaDanmaku.h"
#include <array>
namespace ya
{
	class Animator;
	class Image;
	class Player : public GameObject
	{
	public:
		Player();
		~Player();

		virtual void Tick() override;
		virtual void Render(HDC hec) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;


		void MoveComplete();
		void Attack();
		void DanmakuReset(Danmaku* danmaku,Vector2 pos[5]);
		void DanmakuLevel(int level);

	private:
		float mCoff;
		float mSpeed;
		Image* mImage;
		std::array <Danmaku*, 1024> danmaku;
		Animator* mAnimator;
		float mTime;
		int danmakuLevel;
		int mCount;
		Vector2 firePos[5];
	};
}