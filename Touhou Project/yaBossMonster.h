#pragma once
#include "yaMonster.h"
namespace ya
{
	class BossMonster : public Monster
	{
	public:
		BossMonster();
		~BossMonster();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;


		void SetChanFireAngle();
		void FireNomalAttack_A(bool value, int attackCnt = 1) { nomalAttackBools[0] = value; nomalAttackCnt[0] = attackCnt; }
		void FireNomalAttack_B(bool value, int attackCnt = 1) { nomalAttackBools[1] = value; nomalAttackCnt[1] = attackCnt; }
		void FireNomalAttack_C(bool value, int attackCnt = 1) { nomalAttackBools[2] = value; nomalAttackCnt[2] = attackCnt; }

		void FireSpellAttack_A(bool value, int attackCnt = 1) { spellAttackBools[0] = value, spellAttackCnt[0] = attackCnt; }
		void FireSpellAttack_B(bool value, int attackCnt = 1) { spellAttackBools[1] = value, spellAttackCnt[1] = attackCnt; }
		void FireSpellAttack_C(bool value, int attackCnt = 1) { spellAttackBools[2] = value, spellAttackCnt[2] = attackCnt; }

		void ChenNomalAttack_A();
		void ChenNomalAttack_B();
		void ChenNomalAttack_C();

		void ChenSpellAttack_A();
		void ChenSpellAttack_B(bool leftorRight);
		void ChenSpellAttack_C();

		void ChenPatternSetting_C();
		void ChenPattern_C(Vector2& enemyPos);
	private:
		Image* mImage;

		ATTACKPATTERN spellPattern;

		Vector2 fireAngle[10][10];
		Vector2 goalVector[5];

		//bool patternOn;

		bool nomalAttackBools[3];
		bool spellAttackBools[3];

		int nomalAttackCnt[3];
		int spellAttackCnt[3];

		int moveCnt;

	};
}