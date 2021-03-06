// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Components/EnemyComponent.h"
#include "Core/Json.h"
#include "Objects/ObjectFactory.h"
#include "Core/EventManager.h"
#include <Objects\Scene.h>
#include "TileMap.h"

nc::Engine engine;
nc::Scene scene;

void OnPlayerDead(const nc::Event& event)
{
	int* pdata = static_cast<int*>(event.data);
	int score = *pdata;

	std::cout << "Player Dead: " << score << std::endl;
	
}
void OnBatDead(const nc::Event& event)
{
	int* pdata = static_cast<int*>(event.data);
	int score = *pdata;

	std::cout << "Bat Dead\n";

}
int main(int, char**)
{


	engine.Startup();

	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent,nc::Object>);
	nc::ObjectFactory::Instance().Register("EnemyComponent", new nc::Creator<nc::EnemyComponent,nc::Object>);

	nc::EventManager::Instance().Subscribe("PlayerDead", &OnPlayerDead);
	nc::EventManager::Instance().Subscribe("BatDead", &OnBatDead);

	rapidjson::Document document;
	nc::json::Load("scene/scene.txt", document);
	scene.Create(&engine);
	scene.Read(document);

	nc::json::Load("scene/tileMap.txt", document);
	nc::TileMap tileMap;
	tileMap.Read(document);
	tileMap.Create(&scene);

	//for (size_t i = 0; i < 10; i++)
	//{
	//	nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create <nc::GameObject>("ProtoCoin");
	//	gameObject->m_transform.position = { nc::random(0,800), nc::random(350, 400) };
	//	//gameObject->m_transform.angle =  nc::random(0, 360);

	//	scene.AddGameObject(gameObject);
	//}



	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		//update

		engine.Update();
		scene.Update();

		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}
		

	
		//draw
		engine.GetSystem<nc::Renderer>()->BeginFrame();

	
		scene.Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();
		
	}

	// wait for keyboard enter to exit
	scene.Destroy();
	engine.Shutdown();
	

	return 0;
}


