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

#define ATTACKMAXCOUNT 3

namespace ya
{
	Monster::Monster()
		: attackTime(0.0f)
		,firePos({0.0f,0.0f})
		,pScene(nullptr)
		,attackDelayTime(0.0f)
		,attackCount(0)
		,dir({0.0f,0.0f})
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
	}

	Monster::~Monster()
	{

	}

	void Monster::Tick()
	{
		GameObject::Tick();

		Vector2 pos = GetPos();

		SetPos(pos);

		attackTime += Time::DeltaTime();


		if (attackTime > 1.0f)
		{
			attackDelayTime += Time::DeltaTime();

			if (attackCount == ATTACKMAXCOUNT)
			{
				attackTime = 0;
				attackCount = 0;

			}

			if (attackDelayTime > 0.1f)
			{
				NomalAttack();
				attackDelayTime = 0;
				attackCount++;
			}
		}

		//mTime += Time::DeltaTime();

		//if (mTime > 5.0f)
		//{
		//	pos.x -= 30;
		//	SetPos(pos);
		//	mTime = 0.0f;
		//}

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

	void Monster::NomalAttack()
	{

		for (size_t i = 0; i < 1024; i++)
		{
			if (pScene->danmaku[i]->IsDeath() == true)
			{
				DanmakuReset(pScene->danmaku[i], firePos);
				pScene->danmaku[i]->SetSpeed(300);
					break;
			}
		}
	}
	void Monster::DanmakuReset(Danmaku* danmaku, Vector2 pos)
	{
		Vector2 firePos = GetPos();
		Vector2 playerPos = GetTargetPos();

		Vector2 dir = GetPlayerDir(firePos, playerPos);


		danmaku->mDir = dir;
		Vector2 missileScale = danmaku->GetScale();
		danmaku->SetPos((firePos)-(missileScale / 2.0f));
		danmaku->Alive();
	}

	Vector2 Monster::GetPlayerDir(Vector2 firePos, Vector2 targetPos)
	{
		Vector2 dir = firePos - targetPos;
		dir.Normailize();
		dir = Vector2::MinusOne * dir;

		return dir;
	}
}