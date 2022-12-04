#pragma once
#include "yaEntity.h"
#include "Common.h"
namespace ya
{
	class GameObject;
	class Component : public Entity
	{
	public:
		friend class GameObject;
		Component(eComponentType type);
		//기본 생성자 차단
		 Component() = delete;
		 virtual ~Component();

		virtual void Tick();
		virtual void Render(HDC hdc);
		virtual void Initialize();

		GameObject* GetOwner() { return mOwner; }

	private:
		const eComponentType mType;
		GameObject* mOwner;
	};
}

