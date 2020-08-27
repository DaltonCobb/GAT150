#pragma once
#include "Resources/ResourceManager.h"
#include "Graphics/Renderer.h"
#include "Input/InputSystem.h"
#include "Physics/PhysicsSystem.h"
#include "Audio/AudioSystem.h"
#include "Core/Timer.h"
#include <vector>

namespace nc
{
	class System;

	class Engine
	{
	public:
		bool Startup();
		void Shutdown();

		void Update();

		template<typename T>
		T* GetSystem();

		FrameTimer& GetTimer() { return m_timer; }
	protected:
		std::vector<System*>m_systems;
		FrameTimer m_timer;
	};

	template<typename T>
	T* Engine::GetSystem()
	{
		T* result{ nullptr };
		

		for (auto system : m_systems)
		{
			result = dynamic_cast<T*> (system);
			if (result) break;
		}
		return result;
	}
	
}