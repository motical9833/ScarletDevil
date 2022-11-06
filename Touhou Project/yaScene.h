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

		//이 클래스는 상속만받고 이 클래스로 객체를 생성X
		//순수 가상함수
		virtual void Initialize();  //초기화
		virtual void Tick();  //업데이트
		virtual void Render(HDC hdc);  // 랜더

		virtual void Enter();
		virtual void Exit();

		void AddGameObject(GameObject* object, eColliderLayer type); //오브젝트 추가

		std::vector<GameObject*>& GetGameObjects(eColliderLayer type) { return mObjects[(UINT)type]; }
		std::vector<std::vector<GameObject*>>& GetGameObjects() { return mObjects; }

	private:
		std::vector<std::vector<GameObject*>> mObjects;

		//typedef std::vector<std::vector<GameObject*>> GameObjects;
		//typedef std::vector<GameObject*> LayerObjects;
	};
}
