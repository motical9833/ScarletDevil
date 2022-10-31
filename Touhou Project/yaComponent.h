#pragma once
#include "yaEntity.h"

namespace ya
{
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		//기본 생성자 차단
		 Component() = delete;
		 virtual ~Component();

		virtual void Tick() = 0;
		virtual void Render(HDC hdc);


	private:
		const eComponentType mType;

	};
}

