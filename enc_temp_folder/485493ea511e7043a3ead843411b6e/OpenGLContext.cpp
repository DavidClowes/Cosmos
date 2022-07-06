#include "cozpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Cozmos
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		COZ_CORE_ASSERT(windowHandle, "Window Handle is null!");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		COZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		COZ_CORE_INFO("OpenGL Info:");
		COZ_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		COZ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		COZ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}