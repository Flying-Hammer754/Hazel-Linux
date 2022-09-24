#pragma once

#include "Hazel/Core/Base.h"

namespace Hazel
{
    class AudioSource
    {
    public:
        virtual ~AudioSource() = default;

        virtual void SetData(uint32_t buffer) = 0;

        virtual void Play() = 0;
        virtual void Pause() = 0;
        virtual void Rewind() = 0;
        virtual void Stop() = 0;

        virtual void SetSourcePosition(float x, float y) = 0;
        virtual void SetSourceVelocity(float x, float y) = 0;
        virtual void SetSourceDirection(float x, float y) = 0;
        virtual void SetSourcePitch(float pitch) = 0;
        virtual void SetSourceVolume(float volume) = 0;
        virtual void SetSourceMinVolume(float minVolume) = 0;
        virtual void SetSourceMaxVolume(float maxVolume) = 0;
        virtual void SetSourceMaxDistance(float maxDistance) = 0;
        virtual void SetSourceRolloffFactor(float rolloffFactor) = 0;
        virtual void SetSourceLooping(bool loop) = 0;

        virtual void GetSourcePosition(float& x, float& y) = 0;
        virtual void GetSourceVelocity(float& x, float& y) = 0;
        virtual void GetSourceDirection(float& x, float& y) = 0;
        virtual float GetSourcePitch() = 0;
        virtual float GetSourceVolume() = 0;
        virtual float GetSourceMinVolume() = 0;
        virtual float GetSourceMaxVolume() = 0;
        virtual float GetSourceMaxDistance() = 0;
        virtual float GetSourceRolloffFactor() = 0;
        virtual bool GetSourceLooping() = 0;
        virtual uint32_t GetSourceType() = 0;
        virtual uint32_t GetSourceState() = 0;
        virtual float GetSourceOffset() = 0;
        virtual float GetSourceLength() = 0;

        virtual uint32_t GetSource() = 0;
        virtual bool IsSourceValid() = 0;

        static Ref<AudioSource> Create();
    };
}