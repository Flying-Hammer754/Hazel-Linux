#include "hzpch.h"
#include "OpenGLUniformBuffer.h"

#include <glad/glad.h>

#include "Platform/OpenGL/GLDebugMacros.h"

namespace Hazel {

	OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding)
	{
		#ifdef HZ_USE_OPENGL_3_3
		GL_CALL(glGenBuffers(1, &m_RendererID));
		GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID));
		GL_CALL(glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
		#elif HZ_USE_OPENGL_4_5
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, nullptr, GL_DYNAMIC_DRAW); // TODO: investigate usage hint
		#endif
		GL_CALL(glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID));
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		GL_CALL(glDeleteBuffers(1, &m_RendererID));
	}


	void OpenGLUniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
	{
		#ifdef HZ_USE_OPENGL_3_3
		GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID));
		GL_CALL(glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data));
		#elif HZ_USE_OPENGL_4_5
		glNamedBufferSubData(m_RendererID, offset, size, data);
		#endif
	}

}
