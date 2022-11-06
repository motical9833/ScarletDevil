#pragma once
#include "Common.h"
#include "yaEntity.h"
#include "yaComponent.h"

namespace ya
{
	class Collider;
	class GameObject : public Entity
	{
	public:
		GameObject();
		GameObject(Vector2 position);
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetPos(Vector2 pos) { mPos = pos; }
		Vector2 GetPos() { return mPos; }
		void SetScale(Vector2 pos) { mScale = pos; }
		Vector2 GetScale() { return mScale; }
		void SetHp(int hp) { mHp = hp; }
		int GetHp() { return mHp; }


		void Death() { mDead = true; }
		bool IsDeath() { return mDead; }

		void AddComponent(Component* component);

		template <typename T>
		__forceinline T* GetComponent()
		{
			T* component;
			for (Component* c : mComponents)
			{
				//�θ� �ڽİ��� ����ȯ (dynamic_cast)
				//���� Ÿ���̸�true,Ÿ���� �ٸ��� false�� ��ȯ
				component = dynamic_cast<T*>(c);
				if (component != nullptr)
				return component;
			}
			return nullptr;
		}

	private:
		std::vector<Component*> mComponents;
		//ȭ�鿡 �׷��� ��ġ��ǥ
		Vector2 mPos;
		Vector2 mScale;
		//HDC mHdc;
		bool mDead;
		int mHp;
	};
}