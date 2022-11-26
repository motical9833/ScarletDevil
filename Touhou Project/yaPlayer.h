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
		void NomalAttack();
		void BonusAttack();
		void MiddleAttack();
		void BombAttack();

		void DanmakuReset(Danmaku* danmaku,Vector2 pos,Vector2 angle);
		void DanmakuLevelUP();

	private:
		float mCoff;
		float mSpeed;
		Image* mImage;
		std::array <Danmaku*, 1024> danmaku;
		std::array<std::array<Danmaku*, 500>, 3> pDanmaku;
		std::array <Danmaku*, 24> bombDanmaku;
		Animator* mAnimator;
		float nomalTime;
		float bonusTime;
		float bombTime;
		bool bombOnOff;
		float danmakuTime[2];

		int danmakuLevel;
		int level;
		int mCount;
		
		Vector2 mDanmakuDir;


		Vector2 firePos[3];
		Vector2 fireAngle[3];
		Vector2 bombAngle[8];
	};
}