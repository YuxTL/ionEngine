
#include "CWindow.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


void CWindow::MakeContextCurrent()
{
	glfwMakeContextCurrent(WindowHandle);
}

bool CWindow::ShouldClose() const
{
	return glfwWindowShouldClose(WindowHandle) != 0;
}

vec2i const & CWindow::GetSize() const
{
	return Size;
}

f32 CWindow::GetAspectRatio() const
{
	return (f32) Size.X / (f32) Size.Y;
}

void CWindow::SwapBuffers()
{
	glfwSwapBuffers(WindowHandle);
}

bool CWindow::IsKeyDown(EKey const Key)
{
	return KeyStates[(int) Key];
}

bool CWindow::IsMouseDown(SMouseEvent::EButton const Button)
{
	return MouseStates[(int) Button];
}

vec2f const & CWindow::GetCursorLocation()
{
	return CursorLocation;
}

CWindow::CWindow(GLFWwindow * windowHandle)
	: WindowHandle(windowHandle)
{
	for (unsigned int i = 0; i < (int) EKey::Count; ++ i)
        KeyStates[i] = false;

    for (unsigned int i = 0; i < (int) SMouseEvent::EButton::Count; ++ i)
        MouseStates[i] = false;
	
	KeyboardEvent.AddTrigger(SEvent<SKeyboardEvent>::ITrigger::shared_from_this());
	MouseEvent.AddTrigger(SEvent<SMouseEvent>::ITrigger::shared_from_this());
	WindowResizedEvent.AddTrigger(SEvent<SWindowResizedEvent>::ITrigger::shared_from_this());
}