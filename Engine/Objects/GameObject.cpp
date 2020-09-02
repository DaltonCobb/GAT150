#include "pch.h"
#include "GameObject.h"
#include "Scene.h"
#include "Components/Component.h"
#include "Components/RenderComponent.h"
#include <Objects\ObjectFactory.h>

namespace nc
{
	GameObject::GameObject(const GameObject& other)
	{
		m_name = other.m_name;
		m_tag = other.m_tag;
		m_flags = other.m_flags;
		m_lifetime = other.m_lifetime;

		m_transform = other.m_transform;
		m_engine = other.m_engine;
		m_scene = other.m_scene;

		for (auto component : other.m_components)
		{
			Component* clone = static_cast<Component*>(component->Clone());
			clone->Create(this);
			AddComponent(clone);
		}
	}
	void GameObject::Create(void* data)
{
	m_scene = static_cast<Scene*>(data);
	m_engine = m_scene->m_engine;
}

void GameObject::Destroy()
{
	RemoveAllComponents();
}

void GameObject::Read(const rapidjson::Value& value)
{
	json::Get(value, "name", m_name);
	json::Get(value, "tag", m_tag);

	bool transient = m_flags[eFlags::TRANSIENT];
	json::Get(value, "transient", transient);
	m_flags[eFlags::TRANSIENT] = transient;

	json::Get(value, "lifetime", m_lifetime);

	json::Get(value, "position", m_transform.position);
	json::Get(value, "scale", m_transform.scale);
	json::Get(value, "angle", m_transform.angle);

	if (value.HasMember("Components"))
	{
	const rapidjson::Value& componentsValue = value["Components"];
	if (componentsValue.IsArray())
	{
		ReadComponents(componentsValue);
	}

	}
}

void GameObject::ReadComponents(const rapidjson::Value& value)
{
	for (rapidjson::SizeType i = 0; i < value.Size(); i++)
	{
		const rapidjson::Value& componentValue = value[i];
		if (componentValue.IsObject())
		{
			std::string typeName;
			// read component “type” name from json (Get)
			json::Get(componentValue, "type", typeName);

			Component* component = ObjectFactory::Instance().Create<Component>(typeName);// create component from object factory
			if (component)
			{
				//call component create, pass in gameobject(this)
				component->Create(this);
				// call component read
				component->Read(componentValue);
				// add component to game object
				m_components.push_back(component);
			}
		}
	}
}



void GameObject::Update()
{
	for (auto component : m_components)
	{
		component->Update();
	}
	if (m_flags[eFlags::TRANSIENT])
	{
		m_lifetime = m_lifetime - m_engine->GetTimer().DeltaTime();
		m_flags[eFlags::DESTROY] = (m_lifetime <= 0);
	
	}
}

void GameObject::Draw()
{
	RenderComponent* component = GetComponent<RenderComponent>();
	if (component)
	{
		component->Draw();
	}
}

void GameObject::BeginContact(GameObject* other)
{
	m_contacts.push_back(other);

	Event event;
	event.sender = other;
	event.receiver = this;
	event.type = "CollisionEnter";

	EventManager::Instance().Notify(event);
}

void GameObject::EndContact(GameObject* other)
{
	m_contacts.remove(other);

	Event event;
	event.sender = other;
	event.receiver = this;
	event.type = "CollisionExit";

	EventManager::Instance().Notify(event);
}

std::vector<GameObject*> GameObject::GetContactsWithTag(const std::string& tag)
{
	std::vector<GameObject*> contacts;
	for (auto contact : m_contacts)
	{
		if (contact->m_tag == tag)
		{
			contacts.push_back(contact);
		}
	}
	return contacts;
}

void GameObject::AddComponent(Component* component)
{
	m_components.push_back(component);
}

void GameObject::RemoveComponent(Component* component)
{
	auto iter = std::find(m_components.begin(), m_components.end(), component);
	if (iter != m_components.end())
	{
		(*iter)->Destroy();
		delete (*iter);
	}
}

void GameObject::RemoveAllComponents()
{
	for (auto component : m_components)
	{
		component->Destroy();
		delete component;
	}
	m_components.clear();
}


}
