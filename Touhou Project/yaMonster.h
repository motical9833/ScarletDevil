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
		~Monster();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void BgDanmakuSetting(PlayScene* scene,Vector2& dir, int speedMul, int speed);
		void BgDanmakuSetting(PlayScene* scene, int cnt);
		
		void WidthMoveOn() { moveBools[0] = true; }
		void VerticalMoveOn() { moveBools[1] = true; }
		void CircleMoveOn() { moveBools[2] = true; }
		void CoordinateMoveOn() { moveBools[3] = true; }


		void NomalAttacks();
		void NomalAttack_One();
		void NomalAttack_Two();
		void NomalAttack_Three();


		//void WidthMove(float direction,Vector2& enemyPos);
		//void VerticalMove(float direction, Vector2& enemyPos);
		//void CircleMove(float speed, Vector2& enemyPos);
		//void CoordinateMove(float speed, Vector2& targetPos, Vector2& enemyPos);
		//void ChenNomalAttacks();
		//void ChenNomalAttack_A();
		//void ChenNomalAttack_B();
		//void ChenNomalAttack_C();
		//void ChenSpellCards();
		//void ChenSpellCard_A();
		//void ChenSpellCard_B(bool leftorRight);
		//void ChenSpellCard_C();
		//void ChenPatternSetting_A();
		//void ChenPatternSetting_B();
		//void ChenPatternSetting_C();
		//void ChenPattern_C(Vector2& enemyPos);
		//void ChenSpellCard_B_Setting(PlayScene* scene, int cnt);
		//void ChenSpellCard_C_Setting(PlayScene* scene, int cnt);
		//void SetChanFireAngle();
		//void FireBossSpellAttack_A(bool value, int attackCnt = 1) { bossSpellAttackBools[0] = value, bossSpellAttackCnt[0] = attackCnt; }
		//void FireBossSpellAttack_B(bool value, int attackCnt = 1) { bossSpellAttackBools[1] = value, bossSpellAttackCnt[1] = attackCnt; }
		//void FireBossSpellAttack_C(bool value, int attackCnt = 1) { bossSpellAttackBools[2] = value, bossSpellAttackCnt[2] = attackCnt; }

		void DanmakuReset(Danmaku* danmaku, Vector2 dir);
		

		void SetWidthMoveOnOff(bool value) { moveBools[0] = value; }
		void SetVerticalMoveOnOff(bool value) { moveBools[1] = value; }
		void SetCircleMoveOnOff(bool value) { moveBools[2] = value; }
		void SetCoordinateMove(bool value) { moveBools[3] = value; }
		void SetMImage(Image* image) { mImage = image; }

		void FireNomalAttack_A(bool value, int attackCnt = 1) { nomalAttackBools[0] = value; nomalAttackCounts[0] = attackCnt; }
		void FireNomalAttack_B(bool value, int attackCnt = 1) { nomalAttackBools[1] = value; nomalAttackCounts[1] = attackCnt; }
		void FireNomalAttack_C(bool value, int attackCnt = 1) { nomalAttackBools[2] = value; nomalAttackCounts[2] = attackCnt; }
		

	

		void RotFire(float angle,float speed);
		void RotFire(float angle, float speed, float reMoveSpeed, float stopTime, bool backMoveOnOff);
		void RotFire(float angle, float speed, float reMoveSpeed, float stopTime, Vector2 target, bool targetChangeOnOff);

		void SetAttackDelayTime(float value) { attackDelayTime = value; }
		void SetEnemyMoveSpeed(float speed) { enemyMoveSpeed = speed; }
		void SetCircleR(float value) { circleR = value; }
		void SetTargetPos(Vector2 target) { targetPos = target; }
		void SetPatternOn(bool value) { patternOn = value; }
		void SetNomalHP(int value) { enemyNomalHP = value; }
		void SetPatternHP(int value) { enemyPatternHP = value; }
		void SetAttackTimeCnt(float value) { attackTime += value; }
		void SetAttackTimeZero() { attackTime = 0; }


		bool GetWidthMoveOn() { return moveBools[0]; }
		bool GetVerticalMoveOn() { return moveBools[1]; }
		bool GetCircleMoveOn() { return moveBools[2]; }
		bool& GetCoordinateMoveOn() { return moveBools[3]; }
		bool GetPatternOn() { return patternOn; }
	    float GetMonsterSpeed() { return enemyMoveSpeed; }
		int GetNomalHP() { return enemyNomalHP; }
		int GetPatternHP() { return enemyPatternHP; }
		Vector2 GetPlayerDir(Vector2 firePos, Vector2 targetPos);
		Vector2 GetPlayerPos()
		{
			GameObject* target = pScene->player;
			return target->GetPos();
		}
		Vector2 GetTargetPos() { return targetPos; }
		float& GetAttackTime() { return attackTime; }


		PlayScene* pScene;
		float attackTime;

	private:
		Image* mImage;
		float attackDelayTime;

		Vector2 mDanmakudir;


		Vector2 fireAngle[10][10];
		Vector2 enemyFireDir[6];
		Vector2 goalVector[5];
		Vector2 targetPos;

		bool moveBools[4];
		bool nomalAttackBools[3];
		int nomalAttackCounts[3];
		

		//bool bossSpellAttackBools[3];
		//int bossSpellAttackCnt[3];

		float enemyMoveSpeed;

		float circleR;
		float deg;

		ATTACKPATTERN spellPattern;
		int enemyPattern;

		bool patternOn;
		int moveCnt;
		int enemyNomalHP;
		int enemyPatternHP;
	};
}