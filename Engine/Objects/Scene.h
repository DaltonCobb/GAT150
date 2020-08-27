#pragma once
#include "Objects/Object.h"

namespace nc
{
	class Engine;
	class GameObject;

	class Scene : public Object
	{
	public:
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;

		void Read(const rapidjson::Value& vale) override;
		void ReadGameObjects(const rapidjson::Value& value);
		void ReadPrototypes(const rapidjson::Value& value);

		virtual void Update() override;
		void Draw();

		GameObject* Find(const std::string& name);
		std::vector<GameObject*>FindGameObjectWithTag(const std::string& tag);

		void AddGameObject(GameObject* gameObject);
		void RemoveGameObject(GameObject* gameObject);
		void RemoveAllGameObjects();

	protected:
		Engine* m_engine{ nullptr };
		std::list<GameObject*> m_gameObjects;
	};
}