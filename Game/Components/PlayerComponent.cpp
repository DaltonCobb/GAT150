#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include <Components\AudioComponent.h>

namespace nc
{

void PlayerComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);
}

void PlayerComponent::Destroy()
{
}

void PlayerComponent::Update()
{
	auto contacts = m_owner-> GetContactsWithTag("Floor");
	bool onGround = !contacts.empty();

	nc::Vector2 force{ 0,0 };
	//player controller
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
	{
		force.x = -100;
		//m_owner->m_transform.angle = m_owner->m_transform.angle - 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
	}
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
	{
		force.x = 100;
		//m_owner->m_transform.angle = m_owner->m_transform.angle + 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
	}
	if (onGround && m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
	{
		force.y = -1500;
		AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
		if (audioComponent)
		{
			audioComponent->Play();
		}

	}
	
	PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
	if (component)
	{
		component->SetForce(force);
	}

	//check collision
	auto coinContacts = m_owner->GetContactsWithTag("Coin");
	for (auto contact : coinContacts)
	{
		contact->m_flags[GameObject::eFlags::DESTROY] = true;
	}
}
}
