#pragma once
#include "Common.h"
#include "yaEntity.h"

namespace ya
{
	class GameObject;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		//�� Ŭ������ ��Ӹ��ް� �� Ŭ������ ��ü�� ����X
		//���� �����Լ�
		virtual void Initialize();  //�ʱ�ȭ
		virtual void Tick();  //������Ʈ
		virtual void Render(HDC hdc);  // ����

		void AddGameObject(GameObject* object); //������Ʈ �߰�

	private:
		std::vector<GameObject*> mObjects;
	};
}
