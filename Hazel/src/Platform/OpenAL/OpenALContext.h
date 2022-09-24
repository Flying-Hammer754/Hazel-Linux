#pragma once

#include "Hazel/Audio/AudioContext.h"

struct ALCcontext;
struct ALCdevice;

namespace Hazel
{
    class OpenALContext : public AudioContext
    {
    public:
        OpenALContext();
        virtual ~OpenALContext();

        virtual void Bind() override;
        virtual void Unbind() override;

        virtual void SetListenerVolume(float volume) override;
        virtual void SetListenerPosition(float x, float y) override;
        virtual void SetListenerVelocity(float x, float y) override;
        virtual void SetListenerOrientation(float atX, float atY, float atZ, float upX, float upY, float upZ) override;

        virtual float GetListenerVolume() override;
        virtual void GetListenerPosition(float& x, float& y) override;
        virtual void GetListenerVelocity(float& x, float& y) override;
        virtual void GetListenerOrientation(float& atX, float& atY, float& atZ, float& upX, float& upY, float& upZ) override;

        virtual void* GetContext() override;
        virtual void* GetDevice() override;
    private:
        ALCcontext* m_Context;
        ALCdevice* m_Device;
    };
}