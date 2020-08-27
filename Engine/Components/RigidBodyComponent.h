#pragma once
#include "PhysicsComponent.h"

namespace nc
{
	class RigidBodyComponent : public PhysicsComponent
	{
	public:
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual RigidBodyComponent* Clone() const override { return new RigidBodyComponent{ *this }; }

		void Read(const rapidjson::Value& value) override;

		virtual void Update() override;

		virtual void SetForce(const Vector2& force) override;

	protected:
		PhysicsSystem::RigidBodyData m_data;
		b2Body* m_body{ nullptr };

	};
}