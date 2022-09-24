#include "Platform/OpenAL/OpenALContext.h"

#include <AL/al.h>
#include <AL/alext.h>

namespace Hazel
{
    OpenALContext::OpenALContext()
    {
        m_Device = alcOpenDevice(NULL);
        m_Context = alcCreateContext(m_Device, NULL);
        Bind();
    }

    OpenALContext::~OpenALContext()
    {
        Unbind();
        if (m_Context == NULL)
            return;

        alcDestroyContext(m_Context);
        alcCloseDevice(m_Device);
    }

    void OpenALContext::Bind()
    {
        alcMakeContextCurrent(m_Context);
    }

    void OpenALContext::Unbind()
    {
        alcMakeContextCurrent(NULL);
    }

    void* OpenALContext::GetContext()
    {
        return m_Context;
    }

    void* OpenALContext::GetDevice()
    {
        return m_Device;
    }

    void OpenALContext::SetListenerVolume(float volume)
    {
        alListenerf(AL_GAIN, std::clamp(volume, 0.0f, 1.0f));
    }

    void OpenALContext::SetListenerPosition(float x, float y)
    {
        alListener3f(AL_POSITION, x, y, 0.0f);
    }
    
    void OpenALContext::SetListenerVelocity(float x, float y)
    {
        alListener3f(AL_VELOCITY, x, y, 0.0f);
    }

    void OpenALContext::SetListenerOrientation(float atX, float atY, float atZ, float upX, float upY, float upZ)
    {
        std::array<float, 6> va = { atX, atY, atZ, upX, upY, upZ };
        alListenerfv(AL_ORIENTATION, va.data());
    }

    float OpenALContext::GetListenerVolume()
    {
        float volume;
        alGetListenerf(AL_GAIN, &volume);
        return volume;
    }

    void OpenALContext::GetListenerPosition(float& x, float& y)
    {
        float z;
        alGetListener3f(AL_POSITION, &x, &y, &z);
    }

    void OpenALContext::GetListenerVelocity(float& x, float& y)
    {
        float z;
        alGetListener3f(AL_VELOCITY, &x, &y, &z);
    }

    void OpenALContext::GetListenerOrientation(float& atX, float& atY, float& atZ, float& upX, float& upY, float& upZ)
    {
        std::array<float, 6> va;
        alGetListenerfv(AL_ORIENTATION, va.data());
        atX = va[0];
        atY = va[1];
        atZ = va[2];
        upX = va[3];
        upY = va[4];
        upZ = va[5];
    }
}