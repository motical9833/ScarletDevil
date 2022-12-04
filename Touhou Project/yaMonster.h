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

		void BgDanmakuSetting(PlayScene* scene,Vector2 dir, int speedMul, int speed);
		void BgDanmakuSetting(PlayScene* scene, int cnt);
		



		void NomalAttack_One();
		void NomalAttack_Two();
		void NomalAttack_Three();

		void ChenNomalAttack_A();
		void ChenNomalAttack_B();

		void ChenSpellCard_A();
		void ChenSpellCard_A_Setting(PlayScene* scene, Vector2 dir, int speedMul, int speed, float stopTime);
		void DanmakuReset(Danmaku* danmaku, Vector2 dir);
		
		void SetChanFireAngle();
		Vector2 GetPlayerDir(Vector2 firePos, Vector2 targetPos);

		Vector2 GetTargetPos()
		{
			GameObject* target = pScene->player;
			return target->GetPos();
		}

		//PlayScene* pScene;
		PlayScene* pScene;

	private:
		Image* mImage;
		float attackTime;
		float attackDelayTime;

		int attackCount;
		Vector2 mDanmakudir;


		Vector2 fireAngle[5][10];
		Vector2 enemyFireDir[6];

		bool test;
	};
}