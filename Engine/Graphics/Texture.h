#pragma once
#include "../Math/Vector2.h"
#include "Resources/resource.h"
#include "SDL.h"
#include <string>

namespace nc
{
	class Texture : public Resource
	{
	public:
		bool Create(const std::string& name, void* renderer) override;
		void Destroy() override;

		void Draw(const Vector2& position, float angle = 0, const Vector2& scale = Vector2::one, const Vector2& origin = Vector2::zero);
		void Draw(const SDL_Rect& source, const Vector2& position, float angle = 0, const Vector2& scale = Vector2::one, const Vector2& origin = Vector2::zero);

		Vector2 GetSize() const;

	protected:
		SDL_Texture* m_texture;
		SDL_Renderer* m_renderer;
	};
}