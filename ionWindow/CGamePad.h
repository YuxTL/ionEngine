
#pragma once

#include <ionMath.h>
#include <ionFramework.h>


namespace ion
{

	enum class EGamePadButton
	{
		A,
		B,
		X,
		Y,
		LeftShoulder,
		RightShoulder,
		DPadUp,
		DPadDown,
		DPadLeft,
		DPadRight,
		Start,
		Back,
		LeftThumb,
		RightThumb,
		Count
	};

	class CGamePad : public IEventListener, public Singleton<CGamePad>
	{

	protected:

		vec2f LeftStick;
		vec2f RightStick;
		f32 LeftTrigger;
		f32 RightTrigger;
		bool ButtonPressed[(int) EGamePadButton::Count];

	public:

		vec2f const & GetLeftStick() const;
		vec2f const & GetRightStick() const;
		f32 GetLeftTrigger() const;
		f32 GetRightTrigger() const;
		bool IsButtonPressed(EGamePadButton const Button);

		void UpdateState();


	private:

		friend class Singleton<CGamePad>;
		CGamePad();

	};

	struct SGamePadButtonEvent : public IEvent
	{
		bool Pressed = false;
		EGamePadButton Button;
		CGamePad * GamePad = nullptr;
	};

}
