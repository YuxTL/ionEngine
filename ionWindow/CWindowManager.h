
#pragma once

#include <ionMath.h>

#include "CWindow.h"


class CWindowManager : public Singleton<CWindowManager>
{

public:

	void Init();

	CWindow * CreateWindow(vec2i const & Size, std::string const & Title);

protected:

	std::map<GLFWwindow *, CWindow *> Windows;

	static void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
	static void MouseScrollCallback(GLFWwindow * window, double xoffset, double yoffset);
	static void MouseCursorCallback(GLFWwindow * window, double xpos, double ypos);

private:
	
	friend class Singleton<CWindowManager>;
	CWindowManager();

};