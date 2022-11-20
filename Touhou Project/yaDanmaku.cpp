#include "yaDanmaku.h"
#include "yaTime.h"
#include "yaCollider.h"

namespace ya
{
	Danmaku::Danmaku()
		:mSpeed(1.0f)
		,mTime(0.0f)
		,mDir({0.0f,0.0f})
	{
		SetPos({ 100.0f, 100.0f });
		SetScale({ 20.0f, 20.0f });

		Collider* col = new Collider();
		col->SetScale(Vector2(20.0f, 20.0f));

		AddComponent(col);

		mDir += Vector2(0.0f, 0.0f);
	}
	Danmaku::~Danmaku()
	{

	}
	void Danmaku::Tick()
	{
		GameObject::Tick();

		if (mTime > 2.0f)
		{
			mTime = 0;
			mDir += Vector2(0.0f, 0.0f);
			this->Death();
		}

		float radian = math::DegreeToRadian(90.0f);
		float degree = math::RadianToDegree(2 * PI);

		float speed = 800.0f;
		Vector2 pos = GetPos();

		//pos.y -= speed * Time::DeltaTime();

		// 삼각함수를 이용한 회전
		//mDir = PI / 2.0f;
		//pos.x += speed * cosf(mDir) * Time::DeltaTime();
		//pos.y -= speed * sinf(mDir) * Time::DeltaTime();
		//Vector2 mousPos = Input::GetMousePos();

		mDir.Normailize();
		// 벡터를 이용한 회전
		pos.y += mDir.y * speed * Time::DeltaTime();
		pos.x += mDir.x * speed * Time::DeltaTime();

		SetPos(pos);

		mTime += Time::DeltaTime();
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