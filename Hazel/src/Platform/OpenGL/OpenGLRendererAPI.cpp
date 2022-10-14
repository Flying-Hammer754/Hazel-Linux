#include "hzpch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

#include "Platform/OpenGL/GLDebugMacros.h"

namespace Hazel {
	
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
			#ifdef HZ_USE_OPENGL_4_5
			case GL_DEBUG_SEVERITY_HIGH:         HZ_CORE_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       HZ_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          HZ_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: HZ_CORE_TRACE(message); return;
			#elif HZ_USE_OPENGL_3_3
			default: HZ_CORE_ERROR(std::string("GLMessageCallback: ") + message); return;
			#endif
		}
		
		HZ_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRendererAPI::Init()
	{
		HZ_PROFILE_FUNCTION();

	#if defined(HZ_DEBUG) && defined(HZ_USE_OPENGL_4_5)
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
	#endif

		GL_CALL(glEnable(GL_BLEND));
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		GL_CALL(glEnable(GL_DEPTH_TEST));
		GL_CALL(glEnable(GL_LINE_SMOOTH));
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		GL_CALL(glViewport(x, y, width, height));
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		GL_CALL(glClearColor(color.r, color.g, color.b, color.a));
	}

	void OpenGLRendererAPI::Clear()
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		vertexArray->Bind();
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		GL_CALL(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
	}

	void OpenGLRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		vertexArray->Bind();
		GL_CALL(glDrawArrays(GL_LINES, 0, vertexCount));
	}

	void OpenGLRendererAPI::SetLineWidth(float width)
	{
		float localWidth = width;
		int* values = new int[4];
		bool antialiased;
		glGetIntegerv(GL_LINE_WIDTH, &values[0]);
		glGetIntegerv(GL_ALIASED_LINE_WIDTH_RANGE, &values[1]);
		glGetIntegerv(GL_SMOOTH_LINE_WIDTH_RANGE, &values[2]);
		glGetIntegerv(GL_SMOOTH_LINE_WIDTH_GRANULARITY, &values[3]);
		antialiased = glIsEnabled(GL_LINE_SMOOTH);
		if (antialiased && values[2] < localWidth)
		{
			localWidth = static_cast<float>(values[2]);
		}
		else if (!antialiased && values[1] < localWidth)
		{
			localWidth = static_cast<float>(values[1]);
		}
		//HZ_CORE_TRACE("Line info: width={5} GL_LINE_WIDTH={0}, GL_ALIASED_LINE_WIDTH_RANGE={1}, GL_SMOOTH_LINE_WIDTH_RANGE={2}, GL_SMOOTH_LINE_WIDTH_GRANULARITY={3}, GL_LINE_SMOOTH={4}", values[0], values[1], values[2], values[3], antialiased, width);
		delete[] values;
		GL_CALL(glLineWidth(localWidth));
	}

}
