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
#include <cstdlib>




namespace ya
{
	Monster::Monster()
		: attackTime(0.0f)
		,pScene(nullptr)
		,attackDelayTime(0.0f)
		,attackCount(0)
		,mDanmakudir({1.0f,1.0f})
	{
		SetName(L"Monster");
		SetPos({ 1600 / 2, 300 / 2 });
		SetScale({ 3.0f, 3.0f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Monster"
				, L"..\\Resources\\Image\\Enemys_Img\\Enemy.bmp");
		}

		AddComponent(new Animator());
		AddComponent(new Collider());

		SetChanFireAngle();

		pScene = dynamic_cast<PlayScene*>(SceneManager::GetPlayScene());

	}

	Monster::Monster(Vector2 position)
		: attackTime(0.0f)
		, attackDelayTime(0.0f)
	{
		SetName(L"Monster");
		SetPos(position);
		SetScale({ 3.0f, 3.0f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Monster"
				, L"..\\Resources\\Image\\Enemys_Img\\Enemy.bmp");
		}

		AddComponent(new Animator());
		AddComponent(new Collider());

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				fireAngle[i][j] = Vector2::Zero;
			}
		}

		SetChanFireAngle();
	}

	Monster::~Monster()
	{
		
	}

	void Monster::Tick()
	{
		GameObject::Tick();

		Vector2 pos = GetPos();


		//pos.x += 50.0f * Time::DeltaTime();

		SetPos(pos);

		attackTime += Time::DeltaTime();


		if (attackTime > 2.0f)
		{
			ChenSPellCard_C();
			attackTime = 0;
		}


		if (KEY_DOWN(eKeyCode::T))
		{
			//NomalAttack_Three();
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

	void Monster::BgDanmakuSetting(PlayScene* scene,Vector2 dir,int speedMul,int speed)
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




	void Monster::NomalAttack_One()
	{
		Vector2 firePos = GetPos();
		Vector2 playerPos = GetTargetPos();
		Vector2 dir = GetPlayerDir(firePos, playerPos);

		for (size_t i = 0; i < 3; i++)
		{
			BgDanmakuSetting(pScene, dir, i,200);
		}
	}

	void Monster::NomalAttack_Two()
	{
		fireAngle[0][0] = Vector2(0.0f, 0.0f);
		fireAngle[0][1] = Vector2(0.1f, 0.0f);
		fireAngle[0][2] = Vector2(-0.1f, 0.0f);

		Vector2 firePos = GetPos();
		Vector2 playerPos = GetTargetPos();
		Vector2 dir = GetPlayerDir(firePos, playerPos);

		for (size_t i = 0; i < 3; i++)
		{
			BgDanmakuSetting(pScene, dir + fireAngle[0][i], 0,200);
		}
	}

	void Monster::NomalAttack_Three()
	{

		for (size_t i = 0; i < 9; i++)
		{
			BgDanmakuSetting(pScene, i);
		}
	}


	void Monster::ChenNomalAttack_A()
	{
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
	}

	void Monster::ChenNomalAttack_B()
	{

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				BgDanmakuSetting(pScene, fireAngle[3][j], i, 300);
			}
		}
	}

	void Monster::ChenNomalAttack_C()
	{

	}

	void Monster::ChenSpellCard_A()
	{
		for (size_t j = 0; j < 2; j++)
		{
			for (size_t i = 0; i < 10; i++)
			{
				ChenSpellCard_A_Setting(pScene, fireAngle[4][i], j, 50,1);
			}
		}
	}

	void Monster::ChenSpellCard_B()
	{
		for (size_t i = 0; i < 12; i++)
		{
			ChenSpellCard_B_Setting(pScene, i);
		}
	}

	void Monster::ChenSPellCard_C()
	{
		for (size_t i = 0; i < 9; i++)
		{
			BgDanmakuSetting(pScene, i);
		}
	}


	void Monster::ChenSpellCard_A_Setting(PlayScene* scene, Vector2 dir, int speedMul, int speed,float stopTime)
	{
		for (size_t j = 0; j < 1024; j++)
		{
			if (scene->danmaku[j]->IsDeath() == true)
			{
				DanmakuReset(scene->danmaku[j], dir);
				scene->danmaku[j]->SetSpeed(speed + (speedMul * 50));
				scene->danmaku[j]->SetStop(stopTime,100);
				scene->danmaku[j]->SetRemoveSpeed(100.0f);
				scene->danmaku[j]->SetPlusDir(Vector2(0.25f,1.0f));
				scene->danmaku[j]->SetRotBool(true);
				break;
			}
		}
	}

	void Monster::ChenSpellCard_B_Setting(PlayScene* scene,int cnt)
	{
		for (size_t i = 0; i < 1024; i++)
		{
			if (scene->danmaku[i]->IsDeath() == true)
			{
				Vector2 missileScale = scene->danmaku[i]->GetScale();
				scene->danmaku[i]->SetPos((GetPos()) - (missileScale / 2.0f));
				scene->danmaku[i]->mDestPos = Vector2::One;

				mDanmakudir = math::Rotate(mDanmakudir, static_cast<float>(cnt) - 30.0f);
				scene->danmaku[i]->mDir = mDanmakudir;
				scene->danmaku[i]->SetSpeed(300);
				scene->danmaku[i]->Alive();
				break;
			}
		}
	}

	void Monster::ChenSpellCard_C_Setting(PlayScene* scene, int cnt)
	{
	}



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
				scene->danmaku[i]->SetSpeed(300);
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

	 
	void Monster::SetChanFireAngle()
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
		fireAngle[4][3] = Vector2(0.6f, 0.2f);
		fireAngle[4][4] = Vector2(0.8f, 1.0f);
		fireAngle[4][5] = Vector2(0.0f, 1.0f);
		fireAngle[4][6] = Vector2(-0.8f, 1.0f);
		fireAngle[4][7] = Vector2(-0.6f, 0.2f);
		fireAngle[4][8] = Vector2(-0.4f, -0.1f);
		fireAngle[4][9] = Vector2(-0.2f, -0.25f);

	}

	Vector2 Monster::GetPlayerDir(Vector2 firePos, Vector2 targetPos)
	{
		Vector2 dir = firePos - targetPos;
		dir.Normailize();
		dir = Vector2::MinusOne * dir;

		return dir;
	}
}