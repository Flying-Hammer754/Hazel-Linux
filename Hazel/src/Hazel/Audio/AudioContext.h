#pragma once

#include "Hazel/Core/Base.h"

namespace Hazel
{
    class AudioContext
    {
    public:
        virtual ~AudioContext() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetListenerVolume(float volume) = 0;
        virtual void SetListenerPosition(float x, float y) = 0;
        virtual void SetListenerVelocity(float x, float y) = 0;
        virtual void SetListenerOrientation(float atX, float atY, float atZ, float upX, float upY, float upZ) = 0;

        virtual float GetListenerVolume() = 0;
        virtual void GetListenerPosition(float& x, float& y) = 0;
        virtual void GetListenerVelocity(float& x, float& y) = 0;
        virtual void GetListenerOrientation(float& atX, float& atY, float& atZ, float& upX, float& upY, float& upZ) = 0;

        virtual void* GetContext() = 0;
        virtual void* GetDevice() = 0;

        static Ref<AudioContext> Create();
        static AudioContext* CreatePtr();
    };
}