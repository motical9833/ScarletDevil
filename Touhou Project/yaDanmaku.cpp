#include "yaDanmaku.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaAnimator.h"

namespace ya
{
	Danmaku::Danmaku()
		:mSpeed(800.0f)
		,mTime(0.0f)
		,mDir({0.0f,0.0f})
		,aliveTime(10.0f)
		,mImage(nullptr)
		,wSrc(0)
		,hSrc(0)
		,stopTime(0.0f)
		,slowSpeed(0.0f)
		,nextMoveTime(0.0f)
		,stopBool(false)
		,a(0)
		,reMoveTime(2.0f)
		,reMoveSPeed(100.0f)
		,plusDir({0.0f,0.0f})
		,rotBool(false)
		, targetPos({0.0f,0.0f})
	{
		SetPos({ 100.0f, 100.0f });
		SetScale({ 20.0f, 20.0f });
																																									  
		Collider* col = new Collider();
		col->SetScale(Vector2(20.0f, 20.0f));

		AddComponent(col);

		mDir += Vector2(0.0f, 0.0f);
		
		//state = STATE::End;

	}
	Danmaku::~Danmaku()
	{

	}
	void Danmaku::Tick()
	{
		GameObject::Tick();


		DanmakuDeath();

		DanmakuStopMove(stopBool);

		RemoveDanmaku(reMoveSPeed,rotBool);

		float radian = math::DegreeToRadian(90.0f);
		float degree = math::RadianToDegree(2 * PI);

		Vector2 pos = GetPos();


		pos.x += mDir.x * mSpeed * Time::DeltaTime();
		pos.y += mDir.y * mSpeed * Time::DeltaTime();
		mDir.Normailize();

		SetPos(pos);

		mTime += Time::DeltaTime();
	}
	void Danmaku::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		Vector2 finalPos;
		finalPos.x = (pos.x - mImage->GetWidth());
		finalPos.y = (pos.y - mImage->GetHeight());

		Vector2 rect;
		rect.x = mImage->GetWidth() * 2;
		rect.y = mImage->GetHeight() * 2;


		TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
			, mImage->GetDC(), 0, 0, wSrc, hSrc
			, RGB(255, 0, 255));

		GameObject::Render(hdc);
	}
	

	void Danmaku::OnCollisionEnter(Collider* other)
	{
		GameObject* gameObj = other->GetOwner();
		gameObj->Death();
		this->Death();
	}
	void Danmaku::OnCollisionStay(Collider* other)
	{

	}
	void Danmaku::OnCollisionExit(Collider* other)
	{

	}
	void Danmaku::DanmakuDeath()
	{
		if (mTime > aliveTime)
		{
			mTime = 0;
			mDir += Vector2(0.0f, 0.0f);
			this->Death();
		}
	}
	void Danmaku::DanmakuStopMove(bool stop)
	{
		if (stop == true)
		{
			if (mTime > stopTime)
			{
				mSpeed -= slowSpeed * Time::DeltaTime();
				if (mSpeed <= 0)
				{
					mSpeed = 0;
					stopBool = false;
				}
			}
		}
	}
	void Danmaku::RemoveDanmaku(float speed,bool cnt)
	{
		if (mSpeed == 0 && reMoveTime < mTime)
		{
			mSpeed = reMoveSPeed;

			if (cnt == true)
			{
				SetDir();
			}
		}
	}
	void Danmaku::RotationDanmaku()
	{
		//mDir.x += 100* Time::DeltaTime();
		//mDir.y += 100 * Time::DeltaTime();
	}


	void Danmaku::SetDir()
	{
		if (targetPos == Vector2::Zero)
		{
			return;
		}
		Vector2 dir = GetPos() - targetPos;
		dir.Normailize();
		dir = Vector2::MinusOne * dir;
		mDir = dir;
	}
	//void Danmaku::TargetToMove(Vector2 target)
	//{
	//	Vector2 dir = GetPos() - target;
	//	dir.Normailize();
	//	dir = Vector2::MinusOne * dir;
	//	mDir = dir;
	//}
}