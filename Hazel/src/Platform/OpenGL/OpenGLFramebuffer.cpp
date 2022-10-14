#include "hzpch.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

#include <glad/glad.h>

#include "Platform/OpenGL/GLDebugMacros.h"

namespace Hazel {

	static const uint32_t s_MaxFramebufferSize = 8192;

	namespace Utils {

		static GLenum TextureTarget(bool multisampled)
		{
			return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
		{
			#ifdef HZ_USE_OPENGL_3_3
			GL_CALL(glGenTextures(count, outID));
			for (int i = 0; i < count; ++i)
			{
				GL_CALL(glBindTexture(TextureTarget(multisampled), outID[i]));
			}
			GL_CALL(glBindTexture(TextureTarget(multisampled), 0));
			#elif HZ_USE_OPENGL_4_5
			glCreateTextures(TextureTarget(multisampled), count, outID);
			#endif
		}

		static void BindTexture(bool multisampled, uint32_t id)
		{
			GL_CALL(glBindTexture(TextureTarget(multisampled), id));
		}

		static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				GL_CALL(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE));
			}
			else
			{
				GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr));

				GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
				GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
				GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
				GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
				GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
			}

			GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0));
		}

		static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				GL_CALL(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE));
			}
			else
			{
				#ifdef HZ_USE_OPENGL_4_5
				glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
				#endif

				GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
				GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
				GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
				GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
				GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
			}

			GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0));
		}

		static bool IsDepthFormat(FramebufferTextureFormat format)
		{
			switch (format)
			{
				case FramebufferTextureFormat::DEPTH24STENCIL8:  return true;
			}

			return false;
		}

		static GLenum HazelFBTextureFormatToGL(FramebufferTextureFormat format)
		{
			switch (format)
			{
				case FramebufferTextureFormat::RGBA8:       return GL_RGBA8;
				case FramebufferTextureFormat::RED_INTEGER: return GL_RED_INTEGER;
			}

			HZ_CORE_ASSERT(false);
			return 0;
		}

	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: m_Specification(spec)
	{
		for (auto spec : m_Specification.Attachments.Attachments)
		{
			if (!Utils::IsDepthFormat(spec.TextureFormat))
				m_ColorAttachmentSpecifications.emplace_back(spec);
			else
				m_DepthAttachmentSpecification = spec;
		}

		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		GL_CALL(glDeleteFramebuffers(1, &m_RendererID));
		GL_CALL(glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data()));
		GL_CALL(glDeleteTextures(1, &m_DepthAttachment));
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (m_RendererID)
		{
			GL_CALL(glDeleteFramebuffers(1, &m_RendererID));
			GL_CALL(glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data()));
			GL_CALL(glDeleteTextures(1, &m_DepthAttachment));
			
			m_ColorAttachments.clear();
			m_DepthAttachment = 0;
		}

		#ifdef HZ_USE_OPENGL_3_3
		GL_CALL(glGenFramebuffers(1, &m_RendererID));
		#elif HZ_USE_OPENGL_4_5
		glCreateFramebuffers(1, &m_RendererID);
		#endif
		GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));

		bool multisample = m_Specification.Samples > 1;

		// Attachments
		if (m_ColorAttachmentSpecifications.size())
		{
			m_ColorAttachments.resize(m_ColorAttachmentSpecifications.size());
			Utils::CreateTextures(multisample, m_ColorAttachments.data(), m_ColorAttachments.size());

			for (size_t i = 0; i < m_ColorAttachments.size(); i++)
			{
				Utils::BindTexture(multisample, m_ColorAttachments[i]);
				switch (m_ColorAttachmentSpecifications[i].TextureFormat)
				{
					case FramebufferTextureFormat::RGBA8:
						Utils::AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_RGBA8, GL_RGBA, m_Specification.Width, m_Specification.Height, i);
						break;
					case FramebufferTextureFormat::RED_INTEGER:
						Utils::AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_R32I, GL_RED_INTEGER, m_Specification.Width, m_Specification.Height, i);
						break;
				}
			}
		}

		if (m_DepthAttachmentSpecification.TextureFormat != FramebufferTextureFormat::None)
		{
			Utils::CreateTextures(multisample, &m_DepthAttachment, 1);
			Utils::BindTexture(multisample, m_DepthAttachment);
			switch (m_DepthAttachmentSpecification.TextureFormat)
			{
				case FramebufferTextureFormat::DEPTH24STENCIL8:
					Utils::AttachDepthTexture(m_DepthAttachment, m_Specification.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specification.Width, m_Specification.Height);
					break;
			}
		}

		if (m_ColorAttachments.size() > 1)
		{
			HZ_CORE_ASSERT(m_ColorAttachments.size() <= 4);
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			GL_CALL(glDrawBuffers(m_ColorAttachments.size(), buffers));
		}
		else if (m_ColorAttachments.empty())
		{
			// Only depth-pass
			GL_CALL(glDrawBuffer(GL_NONE));
		}

		GLenum err = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (err != GL_FRAMEBUFFER_COMPLETE)
		{
			HZ_CORE_ERROR("Framebuffer error: {0:x}", err);
			HZ_CORE_ASSERT(false);
		}

		GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void OpenGLFramebuffer::Bind()
	{
		GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
		GL_CALL(glViewport(0, 0, m_Specification.Width, m_Specification.Height));
	}

	void OpenGLFramebuffer::Unbind()
	{
		GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize)
		{
			HZ_CORE_WARN("Attempted to rezize framebuffer to {0}, {1}", width, height);
			return;
		}
		m_Specification.Width = width;
		m_Specification.Height = height;
		
		Invalidate();
	}

	int OpenGLFramebuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
	{
		HZ_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size());

		GL_CALL(glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex));
		int pixelData;
		GL_CALL(glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData));
		return pixelData;

	}

	void OpenGLFramebuffer::ClearAttachment(uint32_t attachmentIndex, int value)
	{
		HZ_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size());

		auto& spec = m_ColorAttachmentSpecifications[attachmentIndex];
		#ifdef HZ_USE_OPENGL_3_3
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_ColorAttachments[attachmentIndex]));
		int width, height, internalFormat;
		GL_CALL(glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width));
		GL_CALL(glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height));
		GL_CALL(glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat));
		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0,
		(Utils::HazelFBTextureFormatToGL(spec.TextureFormat) == GL_RGBA8 ? GL_RGBA : GL_RED), GL_INT, &value));
		#elif HZ_USE_OPENGL_4_5
		glClearTexImage(m_ColorAttachments[attachmentIndex], 0,
			Utils::HazelFBTextureFormatToGL(spec.TextureFormat), GL_INT, &value);
		#endif
	}

}
