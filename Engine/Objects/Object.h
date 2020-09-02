#pragma once
#include "Core/Json.h"
#include "Core/EventManager.h"

namespace nc
{
	class Object
	{
	public:
		virtual void Create(void* data = nullptr) = 0;
		virtual void Destroy() = 0;
		virtual Object* Clone() const { return nullptr; }

		virtual void Read(const rapidjson::Value& value) {}

		virtual void Update() = 0;

		template <typename T>
		static T* Instantiate()
		{
			T* instance = new T;
			return instance;
		}
	};
}