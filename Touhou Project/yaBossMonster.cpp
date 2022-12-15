#include "yaBossMonster.h"
#include "yaResources.h"
#include "yaTime.h"
#include "yaMovePattern.h"
#include "yaInput.h"
namespace ya
{
	BossMonster::BossMonster() 
		: Monster()
		,spellPattern(ATTACKPATTERN::NOMALATTACK_C)
	{
		SetName(L"Chen");
		SetPos({ 800, 100 });
		SetScale({ 3.0f, 3.0f });
		SetNomalHP(100);
		SetPatternHP(100);
		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Monster"
				, L"..\\Resources\\Image\\Enemys_Img\\Enemy.bmp");
		}
		
		AddComponent(new Animator());
		AddComponent(new Collider());

		//FireNomalAttack_A(true);
		//FireNomalAttack_B(true);
		//FireNomalAttack_C(true);
		//FireSpellAttack_A(true);
		//FireSpellAttack_B(true);
		//FireSpellAttack_C(true);
		SetChanFireAngle();
	}
	BossMonster::~BossMonster()
	{

	}

	void BossMonster::Tick()
	{
		GameObject::Tick();

		Vector2 pos = GetPos();
		
		//SetAttackTimeCnt(Time::DeltaTime());

		//if (GetAttackTime() >= 2)
		//{
		//	SetAttackTimeCnt(0);
		//}

		switch (spellPattern)
		{
		case ATTACKPATTERN::NMALMONSTER:

			break;
		case ATTACKPATTERN::NOMALATTACK_A:

			if (GetNomalHP() <= 0)
			{
				//ChenPatternSetting_A();
				spellPattern = ATTACKPATTERN::SPELLATTACK_A;
			}
			break;
		case ATTACKPATTERN::NOMALATTACK_B:
			if (GetNomalHP() <= 0)
			{
				//ChenPatternSetting_B();
				spellPattern = ATTACKPATTERN::SPELLATTACK_B;
			}
			break;
		case ATTACKPATTERN::NOMALATTACK_C:
			if (GetNomalHP() <= 0)
			{
				ChenPatternSetting_C();
				spellPattern = ATTACKPATTERN::SPELLATTACK_C;
			}
			break;
		case ATTACKPATTERN::SPELLATTACK_A:
			if (GetPatternHP() <= 0)
			{
				spellPattern = ATTACKPATTERN::NOMALATTACK_B;
			}
			break;
		case ATTACKPATTERN::SPELLATTACK_B:
			if (GetPatternHP() <= 0)
			{
				spellPattern = ATTACKPATTERN::NOMALATTACK_C;
			}
			break;
		case ATTACKPATTERN::SPELLATTACK_C:
			if (GetPatternHP() <= 0)
			{

				spellPattern = ATTACKPATTERN::DIE;
			}
			ChenPattern_C(pos);
			ChenSpellAttack_C();
			break;
		}

		SetPos(pos);

		if (KEY_DOWN(eKeyCode::T))
		{
			SetNomalHP(0);
		}
	}

	void BossMonster::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		Vector2 finalPos;
		finalPos.x = (pos.x - mImage->GetWidth() * (scale.x / 2.0f));
		finalPos.y = (pos.y - mImage->GetHeight() * (scale.y / 2.0f));

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;


		TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));

		GameObject::Render(hdc);
	}

	void BossMonster::OnCollisionEnter(Collider* other)
	{

	}

	void BossMonster::OnCollisionStay(Collider* other)
	{

	}

	void BossMonster::OnCollisionExit(Collider* other)
	{

	}

	void BossMonster::SetChanFireAngle()
	{
		fireAngle[0][0] = Vector2(0.0f, 1.0f);
		fireAngle[0][1] = Vector2(0.2f, 1.0f);
		fireAngle[0][2] = Vector2(-0.2f, 1.0f);
		fireAngle[0][3] = Vector2(-0.1f, 1.0f);
		fireAngle[0][4] = Vector2(0.1f, 1.0f);
		fireAngle[0][5] = Vector2(0.0f, 1.0f);

		fireAngle[1][0] = Vector2(0.75f, -0.75f);
		fireAngle[1][1] = Vector2(0.95f, -0.75f);
		fireAngle[1][2] = Vector2(0.60f, -0.75f);
		fireAngle[1][3] = Vector2(0.65f, -0.75f);
		fireAngle[1][4] = Vector2(0.85f, -0.75f);
		fireAngle[1][5] = Vector2(0.75f, -0.75f);

		fireAngle[2][0] = Vector2(-0.75f, -0.75f);
		fireAngle[2][1] = Vector2(-0.95f, -0.75f);
		fireAngle[2][2] = Vector2(-0.60f, -0.75f);
		fireAngle[2][3] = Vector2(-0.65f, -0.75f);
		fireAngle[2][4] = Vector2(-0.85f, -0.75f);
		fireAngle[2][5] = Vector2(-0.75f, -0.75f);

		//8각도
		fireAngle[3][0] = Vector2(0.75f, 0.75f);
		fireAngle[3][1] = Vector2(-0.75f, 0.75f);
		fireAngle[3][2] = Vector2(0.75f, -0.75f);
		fireAngle[3][3] = Vector2(-0.75f, -0.75f);
		fireAngle[3][4] = Vector2(0.0f, 1.0f);
		fireAngle[3][5] = Vector2(0.0f, -1.0f);
		fireAngle[3][6] = Vector2(0.5f, 0.0f);
		fireAngle[3][7] = Vector2(-0.5f, 0.0f);

		//10각도
		fireAngle[4][0] = Vector2(0.0f, -1.0f);
		fireAngle[4][1] = Vector2(0.2f, -0.25f);
		fireAngle[4][2] = Vector2(0.4f, -0.1f);
		fireAngle[4][3] = Vector2(0.6f, 0.3f);
		fireAngle[4][4] = Vector2(0.8f, 1.0f);
		fireAngle[4][5] = Vector2(0.0f, 1.0f);
		fireAngle[4][6] = Vector2(-0.8f, 1.0f);
		fireAngle[4][7] = Vector2(-0.6f, 0.2f);
		fireAngle[4][8] = Vector2(-0.4f, -0.1f);
		fireAngle[4][9] = Vector2(-0.2f, -0.25f);


		fireAngle[5][0] = Vector2(0.0f, -1.0f);
		fireAngle[5][1] = Vector2(0.2f, -0.25f);
		fireAngle[5][2] = Vector2(0.4f, -0.1f);
		fireAngle[5][3] = Vector2(0.6f, 0.3f);
		fireAngle[5][4] = Vector2(0.8f, 1.0f);
		fireAngle[5][5] = Vector2(0.0f, 1.0f);
		fireAngle[5][6] = Vector2(-0.8f, 1.0f);
		fireAngle[5][7] = Vector2(-0.6f, 0.2f);
		fireAngle[5][8] = Vector2(-0.4f, -0.1f);
		fireAngle[5][9] = Vector2(-0.2f, -0.25f);


		for (size_t i = 0; i < 5; i++)
		{
			goalVector[i] = Vector2::Zero;
		}

		goalVector[0] = Vector2({ 600.0f,400.0f });
		goalVector[1] = Vector2({ 1000.0f,250.0f });
		goalVector[2] = Vector2({ 600.0f,250.0f });
		goalVector[3] = Vector2({ 1000.0f,400.0f });
		goalVector[4] = Vector2({ 800.0f,100.0f });
	}

	void BossMonster::ChenNomalAttack_A()
	{

		if (nomalAttackBools[0] != true)
			return;

		int a = 0;

		for (size_t i = 0; i < 6; i++)
		{
			if (i / 2 >= 1 && i % 2 == 1)
			{
				a++;
			}

			BgDanmakuSetting(pScene, fireAngle[0][i], a, 150);
			BgDanmakuSetting(pScene, fireAngle[1][i], a, 150);
			BgDanmakuSetting(pScene, fireAngle[2][i], a, 150);
		}


		nomalAttackCnt[0]--;

		if (nomalAttackCnt[0] <= 0)
			nomalAttackBools[0] = false;
	}
	void BossMonster::ChenNomalAttack_B()
	{
		if (nomalAttackBools[1] != true)
			return;

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				BgDanmakuSetting(pScene, fireAngle[3][j], i, 300);
			}
		}


		nomalAttackCnt[1]--;

		if (nomalAttackCnt[1] <= 0)
			nomalAttackBools[1] = false;
	}
	void BossMonster::ChenNomalAttack_C()
	{
		if (nomalAttackBools[2] != true)
			return;

		for (size_t i = 0; i < 18; i++)
		{
			RotFire(20, 50, 300, 1, true);
		}
		for (size_t i = 0; i < 27; i++)
		{
			RotFire(13.3, 75, 250, 1, true);
		}
		for (size_t i = 0; i < 34; i++)
		{
			RotFire(10.5, 100, 200, 1, true);
		}

		nomalAttackCnt[2]--;

		if (nomalAttackCnt[2] <= 0)
			nomalAttackBools[2] = false;
	}

	void BossMonster::ChenSpellAttack_A()
	{
		if (spellAttackBools[0] != true)
			return;

		for (size_t i = 0; i < 20; i++)
		{
			RotFire(18, 150, 250, 1, GetPlayerPos(), true);
		}
		for (size_t i = 0; i < 20; i++)
		{
			RotFire(18, 75, 350, 1, GetPlayerPos(), true);
		}

		for (size_t i = 0; i < 12; i++)
		{
			RotFire(30, 100, 150, 1, false);
		}
		for (size_t i = 0; i < 8; i++)
		{
			RotFire(45, 50, 200, 1, false);
		}

		spellAttackCnt[0]--;

		if (spellAttackCnt[0] <= 0)
			spellAttackBools[0] = false;
	}

	void BossMonster::ChenSpellAttack_B(bool leftorRight)
	{
		if (spellAttackBools[1] != true)
			return;

		for (size_t i = 0; i < 18; i++)
		{
			//10 , 5
			if (leftorRight == true)
				RotFire(10, 100);

			if (leftorRight == false)
				RotFire(-10, 100);
		}

		spellAttackCnt[1]--;

		if (spellAttackCnt[1] <= 0)
			spellAttackBools[1] = false;
	}

	void BossMonster::ChenSpellAttack_C()
	{
		if (spellAttackBools[2] != true)
			return;

		for (size_t i = 0; i < 12; i++)
		{
			RotFire(30, 200);
			RotFire(10.0f, 200);
		}
		for (size_t i = 0; i < 12; i++)
		{
			RotFire(30, 150);
			RotFire(10.0f, 150);
		}
		for (size_t i = 0; i < 4; i++)
		{
			RotFire(90.0f, 250);
		}

		spellAttackCnt[2]--;

		if (spellAttackCnt[2] <= 0)
			spellAttackBools[2] = false;
	}

	


	void BossMonster::ChenPatternSetting_C()
	{
		if (GetPatternHP() <= 0)
			SetPatternHP(100);

		SetEnemyMoveSpeed(2000.0f);
		SetTargetPos(goalVector[4]);
		SetCoordinateMove(true);
		SetPatternOn(false);
	}
	void BossMonster::ChenPattern_C(Vector2& enemyPos)
	{
		if (GetPatternOn() == false)
		{
			SetAttackTimeCnt(Time::DeltaTime());

			if (GetAttackTime() > 3.0f)
			{
				SetPatternOn(true);
				SetAttackTimeZero();
			}
		}

		if (GetPatternOn() == false)
			return;

		if (moveCnt >= 5 && GetCoordinateMoveOn() == false)
		{
			moveCnt = 0;
			SetPatternOn(false);
			return;
		}
		
		movePattern::CoordinateMove(GetMonsterSpeed(), GetTargetPos(), enemyPos, GetCoordinateMoveOn());
		if (GetCoordinateMoveOn() == false && moveCnt < 5)
		{
			FireSpellAttack_C(true);
			SetTargetPos(goalVector[moveCnt]);
			moveCnt++;
			CoordinateMoveOn();
		}
	}
}