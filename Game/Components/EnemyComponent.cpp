#include "pch.h"
#include "EnemyComponent.h"
#include "Components/PhysicsComponent.h"
#include "Objects/Scene.h"
#include <Components\AudioComponent.h>

namespace nc
{
	//EnemyComponent::EnemyComponent(const EnemyComponent& other)
	//{
	//	//m_owner = 
	//}
	void EnemyComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);
	EventManager::Instance().Subscribe("CollisionEnter", std::bind(&EnemyComponent::OnCollisionEnter, this, std::placeholders::_1), m_owner);
	EventManager::Instance().Subscribe("CollisionExit", std::bind(&EnemyComponent::OnCollisionExit, this, std::placeholders::_1), m_owner);
}

void EnemyComponent::Destroy()
{
}

void EnemyComponent::Read(const rapidjson::Value& value)
{
	json::Get(value, "speed", m_speed);
}

void EnemyComponent::Update()
{
	GameObject* player = m_owner->m_scene->Find("Player");
	if (player)
	{
		Vector2 direction = player->m_transform.position - m_owner->m_transform.position;
		Vector2 force = direction.Normalized() * m_speed;

		PhysicsComponent* physicComponent = m_owner->GetComponent<PhysicsComponent>();
		physicComponent->ApplyForce(force);
	}
}
void EnemyComponent::OnCollisionEnter(const Event& event)
{
	GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);

	if (gameObject->m_name == "ProtoBox")
	{
		AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
		audioComponent->SetSoundName("audio/Bat.wav");
		audioComponent->Play();

		m_owner->m_flags[GameObject::eFlags::DESTROY] = true;

		Event event;
		event.type = "BatDead";
		int score = 300;
		event.data = &score;
		EventManager::Instance().Notify(event);
	}
		std::cout << "cllision enter: " << gameObject->m_name << std::endl;
	}
	void EnemyComponent::OnCollisionExit(const Event& event)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);

		std::cout << "cllision exit: " << gameObject->m_name << std::endl;
	}
}
