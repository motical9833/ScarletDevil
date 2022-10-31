#pragma once
#include "Common.h"
#include "yaEntity.h"
#include "yaComponent.h"
namespace ya
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

		void SetPos(Vector2 pos) { mPos = pos; }
		Vector2 GetPos() { return mPos; }
		void SetScale(Vector2 pos) { mScale = pos; }
		Vector2 GetScale() { return mScale; }

		void AddComponent(Component* component);

	private:
		std::vector<Component*> mComponents;
		//화면에 그려질 위치좌표
		Vector2 mPos;
		Vector2 mScale;
		//HDC mHdc;
	};
}