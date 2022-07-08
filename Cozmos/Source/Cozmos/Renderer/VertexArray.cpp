#include "cozpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Cozmos
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			COZ_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}

		COZ_CORE_ASSERT(false, "Unknown RendererAPI!")
			return nullptr;
	}
}