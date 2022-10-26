#pragma once
#include "Common.h"
#include "yaEntity.h"

namespace ya
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

		void SetPos(Vector2 pos) { mPos = pos; }
		Vector2 GetPos() { return mPos; }
		void SetScale(Vector2 pos) { mScale = pos; }
		Vector2 GetScale() { return mScale; }

	private:
		//ȭ�鿡 �׷��� ��ġ��ǥ
		Vector2 mPos;
		Vector2 mScale;
	};
}