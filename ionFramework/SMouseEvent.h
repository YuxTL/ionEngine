
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "IEvent.h"


class CWindow;

struct SMouseEvent : public IEvent
{
    enum class EButton
    {
        Left,
        Right,
        Middle,
        Count
    };

    enum class EType
    {
        Move,
        Click,
		Scroll
	};

    vec2f Location, Movement;
    EButton Button;
    EType Type;
    bool Pressed;
	CWindow * Window;

	SMouseEvent()
		: Window()
	{}
};
