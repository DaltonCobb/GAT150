#pragma once
#include "Components/Component.h"

namespace nc
{
	class EnemyComponent : public Component
	{
	public:
		//EnemyComponent(const EnemyComponent& other);
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() const override { return new EnemyComponent{ *this }; }

		void Read(const rapidjson::Value& value) override;

		virtual void Update() override;

		void OnCollisionEnter(const Event& event);
		void OnCollisionExit(const Event& event);
protected:
	float m_speed = 0;
	};

}