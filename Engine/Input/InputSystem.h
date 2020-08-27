#pragma once
#include "Core/System.h"


namespace nc
{
	class InputSystem : public System
	{
public:
	enum class eButtonState
	{
	IDLE,
	PRESSED,
	HELD, 
	RELEASED
};
	public:

		virtual bool Startup() override;
		virtual void Shutdown() override;
		virtual void Update() override;

		eButtonState GetButtonState(int id);
		bool GetButtonDown(int id);
		bool GetPreviousButtonDown(int id);

	protected:
		int m_numKeys;
		Uint8* m_keystate; 
		Uint8* m_prevKeystate;
	};

}