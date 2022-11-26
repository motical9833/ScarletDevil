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
		,aliveTime(2.0f)
		,mImage(nullptr)
		,wSrc(0)
		,hSrc(0)
	{
		SetPos({ 100.0f, 100.0f });
		SetScale({ 20.0f, 20.0f });

		Collider* col = new Collider();
		col->SetScale(Vector2(20.0f, 20.0f));

		AddComponent(col);

		mDir += Vector2(0.0f, 0.0f);

		/*if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>
				(L"EnemyDanmaku", L"..\\Resources\\Image\\Enemys_Img\\Enemy_Danmaku.bmp");
		}*/

		//AddComponent(new Animator());

		//Animator* ani = new Animator();
		//ani->CreateAnimation(L"Idle", mImage
		//	, Vector2(0.0f, 0.0f), Vector2(31.75f, 50.5f)
		//	, Vector2(0.0f, 0.0f), 4, 0.1f);

		//ani->Play(L"Idle", true);

		//AddComponent(ani);
	}
	Danmaku::~Danmaku()
	{

	}
	void Danmaku::Tick()
	{
		GameObject::Tick();

		if (mTime > aliveTime)
		{
			mTime = 0;
			mDir += Vector2(0.0f, 0.0f);
			this->Death();
		}

		float radian = math::DegreeToRadian(90.0f);
		float degree = math::RadianToDegree(2 * PI);

		Vector2 pos = GetPos();

		//pos.y -= speed * Time::DeltaTime();

		// 삼각함수를 이용한 회전
		//mDir = PI / 2.0f;
		//pos.x += speed * cosf(mDir) * Time::DeltaTime();
		//pos.y -= speed * sinf(mDir) * Time::DeltaTime();
		//Vector2 mousPos = Input::GetMousePos();

		// 벡터를 이용한 회전
		pos.y += mDir.y * mSpeed * Time::DeltaTime();
		pos.x += mDir.x * mSpeed * Time::DeltaTime();
		mDir.Normailize();


		SetPos(pos);

		mTime += Time::DeltaTime();
	}
	void Danmaku::Render(HDC hdc)
	{
		//if (mImage != nullptr)
		//{
		//	GameObject::Render(hdc);
		//	return;
		//}

		//Vector2 pos = GetPos();
		//Vector2 scale = GetScale();
		//Ellipse(hdc, pos.x - 10, pos.y - 10, pos.x + scale.x, pos.y + scale.y);

		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		Vector2 finalPos;
		finalPos.x = (pos.x - mImage->GetWidth());// * (scale.x / 2.0f));
		finalPos.y = (pos.y - mImage->GetHeight());// * (scale.y / 2.0f));

		Vector2 rect;
		rect.x = mImage->GetWidth() * 2;// * scale.x;
		rect.y = mImage->GetHeight() * 2;// * scale.y;


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
}