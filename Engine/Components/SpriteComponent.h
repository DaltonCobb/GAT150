#pragma once
#include "RenderComponent.h"

namespace nc
{
	class SpriteComponent : public RenderComponent
	{
	public:

		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() const override { return new SpriteComponent{ *this }; }

		void Read(const rapidjson::Value& value) override;

		virtual void Update() override;
		virtual void Draw() override;

		void Flip(bool flip = true) { m_flip = flip;  }

	protected:
		std::string m_textureName;
		Vector2 m_origin;
		SDL_Rect m_rect{ 0, 0, 0 };
		bool m_flip{ false };
	};
}