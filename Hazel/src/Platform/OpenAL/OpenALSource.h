#pragma once

#include "Hazel/Audio/AudioSource.h"

namespace Hazel
{
    class OpenALSource : public AudioSource
    {
    public:
        OpenALSource();
        virtual ~OpenALSource();

        virtual void SetData(uint32_t buffer) override;

        virtual uint32_t GetSource() override;
        virtual bool IsSourceValid() override;

        virtual void Play() override;
        virtual void Pause() override;
        virtual void Rewind() override;
        virtual void Stop() override;

        virtual void SetSourcePosition(float x, float y) override;
        virtual void SetSourceVelocity(float x, float y) override;
        virtual void SetSourceDirection(float x, float y) override;
        virtual void SetSourcePitch(float pitch) override;
        virtual void SetSourceVolume(float volume) override;
        virtual void SetSourceMinVolume(float minVolume) override;
        virtual void SetSourceMaxVolume(float maxVolume) override;
        virtual void SetSourceMaxDistance(float maxDistance) override;
        virtual void SetSourceRolloffFactor(float rolloffFactor) override;
        virtual void SetSourceLooping(bool loop) override;

        virtual void GetSourcePosition(float& x, float& y) override;
        virtual void GetSourceVelocity(float& x, float& y) override;
        virtual void GetSourceDirection(float& x, float& y) override;
        virtual float GetSourcePitch() override;
        virtual float GetSourceVolume() override;
        virtual float GetSourceMinVolume() override;
        virtual float GetSourceMaxVolume() override;
        virtual float GetSourceMaxDistance() override;
        virtual float GetSourceRolloffFactor() override;
        virtual bool GetSourceLooping() override;
        virtual uint32_t GetSourceType() override;
        virtual uint32_t GetSourceState() override;
        virtual float GetSourceOffset() override;
        virtual float GetSourceLength() override;
    private:
        uint32_t m_Source;
    };
}