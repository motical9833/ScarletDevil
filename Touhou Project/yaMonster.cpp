#include "yaMonster.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaDanmaku.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaPlayScene.h"
#include "yaMovePattern.h"

#include <cstdlib>
#include <math.h>




namespace ya
{
	Monster::Monster()
		: attackTime(0.0f)
		,pScene(nullptr)
		,attackDelayTime(2.0f)
		,mDanmakudir({1.0f,1.0f})
		,enemyMoveSpeed(100.0f)
		,circleR(1.0f)
		,deg(0.0f)
		,enemyPattern(0)
		,spellPattern(ATTACKPATTERN::SPELLATTACK_C)
		,moveCnt(0)
		,patternOn(false)
		,enemyNomalHP(100)
		,enemyPatternHP(1000)
	{
		SetName(L"Monster");
		SetPos({ 800, 100  });
		SetScale({ 3.0f, 3.0f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Monster"
				, L"..\\Resources\\Image\\Enemys_Img\\Enemy.bmp");
		}

		AddComponent(new Animator());
		AddComponent(new Collider());

		//SetChanFireAngle();
		for (size_t i = 0; i < 3; i++)
		{
			nomalAttackBools[i] = false;
			nomalAttackCounts[i] = 0;
		}

		for (size_t i = 0; i < 4; i++)
		{
			moveBools[i] = false;
		}

		for (size_t i = 0; i < 5; i++)
		{
			goalVector[i] = Vector2::Zero;
		}

		goalVector[0] = Vector2({ 600.0f,400.0f });
		goalVector[1] = Vector2({ 1000.0f,250.0f });
		goalVector[2] = Vector2({ 600.0f,250.0f });
		goalVector[3] = Vector2({ 1000.0f,400.0f });
		goalVector[4] = Vector2({ 800.0f,100.0f });

		//CoordinateMoveOn();
		//FireNomalAttack_C(true);

		//moveBools[0] = true;

		pScene = dynamic_cast<PlayScene*>(SceneManager::GetPlayScene());
	}

	Monster::~Monster()
	{
		
	}

	void Monster::Tick()
	{
		GameObject::Tick();

		Vector2 pos = GetPos();

		//attackTime += Time::DeltaTime();

		//if (attackTime > 2)
		//{

		//	attackTime = 0;
		//}

		switch (spellPattern)
		{
		case ATTACKPATTERN::NMALMONSTER:

			break;
		case ATTACKPATTERN::NOMALATTACK_A:

			if (enemyNomalHP <= 0)
			{
				spellPattern = ATTACKPATTERN::DIE;
			}
			break;
		case ATTACKPATTERN::NOMALATTACK_B:
			if (enemyNomalHP <= 0)
			{
				spellPattern = ATTACKPATTERN::DIE;
			}
			break;
		case ATTACKPATTERN::NOMALATTACK_C:
			if (enemyNomalHP <= 0)
			{
				spellPattern = ATTACKPATTERN::DIE;
			}
			break;

		case ATTACKPATTERN::DIE:

			break;

		case ATTACKPATTERN::NONE:
			break;
		}

		SetPos(pos);


		if (KEY_DOWN(eKeyCode::T))
		{
			enemyNomalHP = 0;
		}
	}

	void Monster::Render(HDC hdc)
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
	void Monster::OnCollisionEnter(Collider* other)
	{
	}
	void Monster::OnCollisionStay(Collider* other)
	{
	}
	void Monster::OnCollisionExit(Collider* other)
	{
	}	

	void Monster::BgDanmakuSetting(PlayScene* scene,Vector2& dir,int speedMul,int speed)
	{
		for (size_t j = 0; j < 1024; j++)
		{
			if (scene->danmaku[j]->IsDeath() == true)
			{
				DanmakuReset(scene->danmaku[j],dir);
				scene->danmaku[j]->SetSpeed(speed + (speedMul * 20));
				break;
			}
		}
	}




	void Monster::NomalAttacks()
	{
			NomalAttack_One();
			NomalAttack_Two();
			NomalAttack_Three();
	}

	void Monster::NomalAttack_One()
	{
		if (nomalAttackBools[0] != true)
			return;

		Vector2 firePos = GetPos();
		Vector2 playerPos = GetPlayerPos();
		Vector2 dir = GetPlayerDir(firePos, playerPos);


		for (size_t i = 0; i < 3; i++)
		{
			BgDanmakuSetting(pScene, dir, i, 200);
		}
		nomalAttackCounts[0]--;

		if(nomalAttackCounts[0] <= 0)
		nomalAttackBools[0] = false;
	}

	void Monster::NomalAttack_Two()
	{
		if (nomalAttackBools[1] != true)
			return;

		fireAngle[0][0] = Vector2(0.0f, 0.0f);
		fireAngle[0][1] = Vector2(0.1f, 0.0f);
		fireAngle[0][2] = Vector2(-0.1f, 0.0f);

		Vector2 firePos = GetPos();
		Vector2 playerPos = GetPlayerPos();
		Vector2 dir = GetPlayerDir(firePos, playerPos);

		for (size_t i = 0; i < 3; i++)
		{
			fireAngle[0][i] += dir;
			BgDanmakuSetting(pScene, fireAngle[0][i], 0,200);
		}
		nomalAttackCounts[1]--;

		if (nomalAttackCounts[1] <= 0)
		nomalAttackBools[1] = false;
	}

	void Monster::NomalAttack_Three()
	{
		if (nomalAttackBools[2] != true)
			return;

		for (size_t i = 0; i < 9; i++)
		{
			BgDanmakuSetting(pScene, i);
		}

		if (nomalAttackCounts[2] <= 0)
		nomalAttackBools[2] = false;
	}


	//void Monster::ChenSpellCards()
	//{
	//	ChenSpellCard_A();
	//	ChenSpellCard_C();
	//}
	//void Monster::ChenSpellCard_A()
	//{
	//	if (bossSpellAttackBools[0] != true)
	//		return;
	//	for (size_t i = 0; i < 20; i++)
	//	{
	//		RotFire(18, 150,250, 1, GetPlayerPos(), true);
	//	}
	//	for (size_t i = 0; i < 20; i++)
	//	{
	//		RotFire(18, 75, 350, 1, GetPlayerPos(), true);
	//	}
	//	for (size_t i = 0; i < 12; i++)
	//	{
	//		RotFire(30, 100, 150, 1, false);
	//	}
	//	for (size_t i = 0; i < 8; i++)
	//	{
	//		RotFire(45, 50, 200, 1, false);
	//	}
	//	bossSpellAttackCnt[0]--;
	//	if (bossSpellAttackCnt[0] <= 0)
	//		bossSpellAttackBools[0] = false;
	//}
	//void Monster::ChenSpellCard_B(bool leftorRight)
	//{
	//	if (bossSpellAttackBools[1] != true)
	//		return;
	//	for (size_t i = 0; i < 18; i++)
	//	{
	//		//10 , 5
	//		if (leftorRight == true)
	//		RotFire(10, 100);
	//		if(leftorRight == false)
	//		RotFire(-10, 100);
	//	}
	//	bossSpellAttackCnt[1]--;
	//	if (bossSpellAttackCnt[1] <= 0)
	//		bossSpellAttackBools[1] = false;
	//}
	//void Monster::ChenSpellCard_C()
	//{
	//	if (bossSpellAttackBools[2] != true)
	//		return;
	//	for (size_t i = 0; i < 12; i++)
	//	{
	//		RotFire(30, 200);
	//		RotFire(10.0f, 200);
	//	}
	//	for (size_t i = 0; i < 12; i++)
	//	{
	//		RotFire(30, 150);
	//		RotFire(10.0f, 150);
	//	}
	//	for (size_t i = 0; i < 4; i++)
	//	{
	//		RotFire(90.0f, 250);
	//	}
	//	
	//	bossSpellAttackCnt[2]--;
	//	if (bossSpellAttackCnt[2] <= 0)
	//		bossSpellAttackBools[2] = false;
	//}
	//void Monster::ChenPatternSetting_A()
	//{
	//}
	//void Monster::ChenPatternSetting_B()
	//{
	//}
	//void Monster::ChenPatternSetting_C()
	//{
	//	enemyMoveSpeed = 2000.0f;
	//	targetPos = goalVector[4];
	//	moveBools[3] = true;
	//}
	//void Monster::ChenPattern_C(Vector2& enemyPos)
	//{
	//	if (patternOn == false)
	//	{
	//		attackTime += Time::DeltaTime();
	//		if (attackTime > 3.0f)
	//		{
	//			patternOn = true;
	//			attackTime = 0;
	//		}
	//	}
	//	if (patternOn == false)
	//		return;
	//	if (moveCnt >= 5 && moveBools[3] == false)
	//	{
	//		moveCnt = 0;
	//		patternOn = false;
	//		return;
	//	}
	//	movePattern::CoordinateMove(enemyMoveSpeed, targetPos, enemyPos, moveBools[3]);
	//	if (moveBools[3] == false && moveCnt < 5)
	//	{
	//		FireBossSpellAttack_C(true);
	//		targetPos = goalVector[moveCnt];
	//		moveCnt++;
	//		moveBools[3] = true;
	//	}
	//}
	//void Monster::ChenSpellCard_B_Setting(PlayScene* scene,int cnt)
	//{
	//	for (size_t i = 0; i < 1024; i++)
	//	{
	//		if (scene->danmaku[i]->IsDeath() == true)
	//		{
	//			Vector2 missileScale = scene->danmaku[i]->GetScale();
	//			scene->danmaku[i]->SetPos((GetPos()) - (missileScale / 2.0f));
	//			scene->danmaku[i]->mDestPos = Vector2::One;
	//			mDanmakudir = math::Rotate(mDanmakudir, static_cast<float>(cnt) - 30.0f);
	//			scene->danmaku[i]->mDir = mDanmakudir;
	//			scene->danmaku[i]->SetSpeed(300);
	//			scene->danmaku[i]->Alive();
	//			break;
	//		}
	//	}
	//}
	//void Monster::ChenSpellCard_C_Setting(PlayScene* scene, int cnt)
	//{
	//	for (size_t i = 0; i < 1024; i++)
	//	{
	//		if (scene->danmaku[i]->IsDeath() == true)
	//		{
	//			Vector2 missileScale = scene->danmaku[i]->GetScale();
	//			scene->danmaku[i]->SetPos((GetPos()) - (missileScale / 2.0f));
	//			scene->danmaku[i]->mDestPos = Vector2::One;
	//			mDanmakudir = math::Rotate(mDanmakudir, static_cast<float>(cnt) - 45.0f);
	//			scene->danmaku[i]->mDir = mDanmakudir;
	//			scene->danmaku[i]->SetSpeed(100);
	//			scene->danmaku[i]->Alive();
	//			break;
	//		}
	//	}
	//}
	//void Monster::SetChanFireAngle()
	//{
	//	fireAngle[0][0] = Vector2(0.0f, 1.0f);
	//	fireAngle[0][1] = Vector2(0.2f, 1.0f);
	//	fireAngle[0][2] = Vector2(-0.2f, 1.0f);
	//	fireAngle[0][3] = Vector2(-0.1f, 1.0f);
	//	fireAngle[0][4] = Vector2(0.1f, 1.0f);
	//	fireAngle[0][5] = Vector2(0.0f, 1.0f);
	//	fireAngle[1][0] = Vector2(0.75f, -0.75f);
	//	fireAngle[1][1] = Vector2(0.95f, -0.75f);
	//	fireAngle[1][2] = Vector2(0.60f, -0.75f);
	//	fireAngle[1][3] = Vector2(0.65f, -0.75f);
	//	fireAngle[1][4] = Vector2(0.85f, -0.75f);
	//	fireAngle[1][5] = Vector2(0.75f, -0.75f);
	//	fireAngle[2][0] = Vector2(-0.75f, -0.75f);
	//	fireAngle[2][1] = Vector2(-0.95f, -0.75f);
	//	fireAngle[2][2] = Vector2(-0.60f, -0.75f);
	//	fireAngle[2][3] = Vector2(-0.65f, -0.75f);
	//	fireAngle[2][4] = Vector2(-0.85f, -0.75f);
	//	fireAngle[2][5] = Vector2(-0.75f, -0.75f);
	//	//8각도
	//	fireAngle[3][0] = Vector2(0.75f, 0.75f);
	//	fireAngle[3][1] = Vector2(-0.75f, 0.75f);
	//	fireAngle[3][2] = Vector2(0.75f, -0.75f);
	//	fireAngle[3][3] = Vector2(-0.75f, -0.75f);
	//	fireAngle[3][4] = Vector2(0.0f, 1.0f);
	//	fireAngle[3][5] = Vector2(0.0f, -1.0f);
	//	fireAngle[3][6] = Vector2(0.5f, 0.0f);
	//	fireAngle[3][7] = Vector2(-0.5f, 0.0f);
	//	//10각도
	//	fireAngle[4][0] = Vector2(0.0f, -1.0f);
	//	fireAngle[4][1] = Vector2(0.2f, -0.25f);
	//	fireAngle[4][2] = Vector2(0.4f, -0.1f);
	//	fireAngle[4][3] = Vector2(0.6f, 0.3f);
	//	fireAngle[4][4] = Vector2(0.8f, 1.0f);
	//	fireAngle[4][5] = Vector2(0.0f, 1.0f);
	//	fireAngle[4][6] = Vector2(-0.8f, 1.0f);
	//	fireAngle[4][7] = Vector2(-0.6f, 0.2f);
	//	fireAngle[4][8] = Vector2(-0.4f, -0.1f);
	//	fireAngle[4][9] = Vector2(-0.2f, -0.25f);
	//	fireAngle[5][0] = Vector2(0.0f, -1.0f);
	//	fireAngle[5][1] = Vector2(0.2f, -0.25f);
	//	fireAngle[5][2] = Vector2(0.4f, -0.1f);
	//	fireAngle[5][3] = Vector2(0.6f, 0.3f);
	//	fireAngle[5][4] = Vector2(0.8f, 1.0f);
	//	fireAngle[5][5] = Vector2(0.0f, 1.0f);
	//	fireAngle[5][6] = Vector2(-0.8f, 1.0f);
	//	fireAngle[5][7] = Vector2(-0.6f, 0.2f);
	//	fireAngle[5][8] = Vector2(-0.4f, -0.1f);
	//	fireAngle[5][9] = Vector2(-0.2f, -0.25f);
	//}


	void Monster::BgDanmakuSetting(PlayScene* scene,int cnt)
	{
		for (size_t i = 0; i < 1024; i++)
		{
			if (scene->danmaku[i]->IsDeath() == true)
			{
				Vector2 missileScale = scene->danmaku[i]->GetScale();
				scene->danmaku[i]->SetPos((GetPos()) - (missileScale / 2.0f));
				scene->danmaku[i]->mDestPos = Vector2::One;

				mDanmakudir = math::Rotate(mDanmakudir, static_cast<float>(cnt) - 45.0f);
				scene->danmaku[i]->mDir = mDanmakudir;
				scene->danmaku[i]->SetSpeed(200);
				scene->danmaku[i]->Alive();
				break;
			}
		}
	}


	void Monster::DanmakuReset(Danmaku* danmaku, Vector2 dir)
	{
		danmaku->mDir = dir;
		Vector2 missileScale = danmaku->GetScale();
		danmaku->SetPos((GetPos())-(missileScale / 2.0f));
		danmaku->Alive();
	}


	/// <summary>
	/// Rotate로 작동하는 탄막발사 로직으로 OnOff를 통해 탄막이 멈춘 후 탄막이 target의 방향으로 이동한다.
	/// </summary>
	/// <param name="angle">각도</param>
	/// <param name="speed">탄막속도</param>
	/// <param name="reMoveSpeed">다시 움직였을 때 속도</param>
	/// <param name="stopTime">탄막이 멈추는 시간</param>
	/// <param name="target">탄막이 향하는 방향</param>
	/// <param name="targetChangeOnOff">조건</param>
	void Monster::RotFire(float angle,float speed,float reMoveSpeed,float stopTime,Vector2 target,bool targetChangeOnOff)
	{
		for (size_t i = 0; i < 1024; i++)
		{
			if (pScene->danmaku[i]->IsDeath() == true)
			{
				if(targetChangeOnOff == true)
					pScene->danmaku[i]->SetTargetPos(target);

				pScene->danmaku[i]->SetPos(GetPos());
				pScene->danmaku[i]->SetSpeed(speed);
				mDanmakudir = math::Rotate(mDanmakudir, angle);
				DanmakuReset(pScene->danmaku[i], mDanmakudir);

				pScene->danmaku[i]->SetStop(stopTime, speed);
				pScene->danmaku[i]->SetRemoveSpeed(reMoveSpeed);
				pScene->danmaku[i]->SetRotBool(targetChangeOnOff);
				break;
			}
		}
	}

	/// <summary>
	/// Rotate로 작동하는 탄막발사 로직으로 OnOff를 통해 탄막이 멈춘 후 몬스터방향으로 탄막의 방향을 바꿀 수 있다.
	/// </summary>
	/// <param name="angle">각도</param>
	/// <param name="speed">탄막속도</param>
	/// <param name="reMoveSpeed">다시 움직였을 때 속도</param>
	/// <param name="stopTime">탄막이 멈추는 시간</param>
	/// <param name="backMoveOnOff">조건</param>
	void Monster::RotFire(float angle, float speed,float reMoveSpeed, float stopTime,bool backMoveOnOff)
	{
		for (size_t i = 0; i < 1024; i++)
		{
			if (pScene->danmaku[i]->IsDeath() == true)
			{
				if (backMoveOnOff == true)
					pScene->danmaku[i]->SetTargetPos(GetPos());

				pScene->danmaku[i]->SetPos(GetPos());
				pScene->danmaku[i]->SetSpeed(speed);
				mDanmakudir = math::Rotate(mDanmakudir, angle);
				DanmakuReset(pScene->danmaku[i], mDanmakudir);

				pScene->danmaku[i]->SetStop(stopTime, speed);
				pScene->danmaku[i]->SetRemoveSpeed(reMoveSpeed);
				pScene->danmaku[i]->SetRotBool(backMoveOnOff);
				break;
			}
		}
	}

	/// <summary>
    /// Roate로 작동하는 탄막발사 로직
    /// </summary>
	/// <param name="angle">각도</param>
    /// <param name="speed">탄막 속도</param>
	void Monster::RotFire(float angle, float speed)
	{
		for (size_t i = 0; i < 1024; i++)
		{
			if (pScene->danmaku[i]->IsDeath() == true)
			{
				pScene->danmaku[i]->SetPos(GetPos());
				pScene->danmaku[i]->mDestPos = Vector2::One;
				mDanmakudir = math::Rotate(mDanmakudir, angle);
				pScene->danmaku[i]->SetSpeed(speed);
				DanmakuReset(pScene->danmaku[i], mDanmakudir);
				break;
			}
		}
	}

	Vector2 Monster::GetPlayerDir(Vector2 firePos, Vector2 targetPos)
	{
		Vector2 dir = firePos - targetPos;
		dir.Normailize();
		dir = Vector2::MinusOne * dir;

		return dir;
	}
}