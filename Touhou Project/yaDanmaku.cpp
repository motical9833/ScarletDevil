#include "yaDanmaku.h"
#include "yaTime.h"
#include "yaCollider.h"

namespace ya
{
	Danmaku::Danmaku()
		:mSpeed(1.0f)
		,mTime(0.0f)
	{
		SetPos({ 100.0f, 100.0f });
		SetScale({ 20.0f, 20.0f });

		Collider* col = new Collider();
		col->SetScale(Vector2(20.0f, 20.0f));

		AddComponent(col);
	}
	Danmaku::~Danmaku()
	{

	}
	void Danmaku::Tick()
	{
		GameObject::Tick();

		Vector2 pos = GetPos();
		pos.y -= 500.0f * Time::DeltaTime();
		SetPos(pos);

		mTime += Time::DeltaTime();

		if (mTime > 1.0f)
		{
			mTime = 0;
			this->Death();
		}
	}
	void Danmaku::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Ellipse(hdc, pos.x - 10, pos.y - 10, pos.x + scale.x, pos.y + scale.y);

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
}