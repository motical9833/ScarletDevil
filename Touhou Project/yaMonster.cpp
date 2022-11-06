#include "yaMonster.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	Monster::Monster()
	{
		SetName(L"Monster");
		SetPos({ 1600 / 2, 900 / 2 });
		SetScale({ 3.0f,3.0f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Monster"
				,L"..\\Resources\\Image\\Enemys_Img\\Enemy.bmp");
		}

		AddComponent(new Animator());
		AddComponent(new Collider());
	}
	Monster::Monster(Vector2 position)
	{
		SetName(L"Monster");
		SetPos(position);
		SetScale({ 3.0f,3.0f });

		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"Monster"
				, L"..\\Resources\\Image\\Enemys_Img\\Enemy.bmp");
		}

		AddComponent(new Animator());
		AddComponent(new Collider());
	}
	void Monster::Tick()
	{
		GameObject::Tick();

		Vector2 pos = GetPos();

		SetPos(pos);
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
}