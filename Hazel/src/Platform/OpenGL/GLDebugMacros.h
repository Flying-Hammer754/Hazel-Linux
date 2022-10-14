#pragma once

#if defined(HZ_DEBUG) && defined(HZ_USE_OPENGL_3_3)
#include <glad/glad.h>

#include "stdio.h"
#include "Hazel/Core/Assert.h"

#define GLASSERT(x) if(!(x)) { HZ_CORE_ASSERT(false); }
#define GL_CALL(x) Hazel::Utils::GLClearError();\
    x;\
    GLASSERT(Hazel::Utils::GLLogCall(#x, __FILE__, __LINE__))

#ifndef GLDEBUGMACROS_H_FUNCS_DEFINED
#define GLDEBUGMACROS_H_FUNCS_DEFINED
namespace Hazel::Utils
{
    inline void GLClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    inline bool GLLogCall(const char* function, const char* file, int line)
    {
        while (GLenum error = glGetError())
        {
            fprintf(stderr, "[OpenGL Error]: 0x0%x, [At: %s, %d:%s]", error, file, line, function);
            return false;
        }

        return true;
    }
}
#endif
#else
#define GL_CALL(x) x
#endif