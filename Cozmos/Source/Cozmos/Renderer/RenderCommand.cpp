#include "cozpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Cozmos
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}