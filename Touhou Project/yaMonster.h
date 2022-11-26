#pragma once
#include "yaGameObject.h"
#include "yaScene.h"
#include "yaDanmaku.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"

namespace ya
{
	class Image;
	class Monster : public GameObject
	{
	public:
		Monster();
		Monster(Vector2 position);
		~Monster();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		
		void NomalAttack();
		void DanmakuReset(Danmaku* danmaku, Vector2 pos);
		
		Vector2 GetPlayerDir(Vector2 firePos, Vector2 targetPos);

		Vector2 GetTargetPos()
		{
			GameObject* target = pScene->player;
			return target->GetPos();
		}

		PlayScene* pScene;

	private:
		Image* mImage;
		//Animator* mAnimator;
		float attackTime;
		float attackDelayTime;

		int attackCount;
		Vector2 firePos;
		Vector2 dir;
		//Vector2 mDanmakuDir;
	};
}