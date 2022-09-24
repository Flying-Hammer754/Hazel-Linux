#include "Platform/OpenAL/OpenALSource.h"

#include <AL/al.h>
#include <AL/alext.h>

namespace Hazel
{
    OpenALSource::OpenALSource()
    {

    }

    OpenALSource::~OpenALSource()
    {
        if (!IsSourceValid())
            return;

        alDeleteSources(1, &m_Source);
    }

    uint32_t OpenALSource::GetSource()
    {
        return m_Source;
    }

    bool OpenALSource::IsSourceValid()
    {
        return alIsSource(m_Source);
    }

    void OpenALSource::SetData(uint32_t buffer)
    {
        if (!IsSourceValid())
        {
            alGenSources(1, &m_Source);
        }
        alSourcei(m_Source, AL_BUFFER, buffer);
        HZ_CORE_ASSERT(alGetError() == AL_NO_ERROR, "Failed to setup sound source");
    }

    void OpenALSource::Play()
    {
        alSourcePlay(m_Source);
    }

    void OpenALSource::Pause()
    {
        alSourcePause(m_Source);
    }

    void OpenALSource::Rewind()
    {
        alSourceRewind(m_Source);
    }

    void OpenALSource::Stop()
    {
        alSourceStop(m_Source);
    }

    void OpenALSource::SetSourcePosition(float x, float y)
    {
        alSource3f(m_Source, AL_POSITION, x, y, 0.0f);
    }

    void OpenALSource::SetSourceVelocity(float x, float y)
    {
        alSource3f(m_Source, AL_VELOCITY, x, y, 0.0f);
    }

    void OpenALSource::SetSourceDirection(float x, float y)
    {
        alSource3f(m_Source, AL_DIRECTION, x, y, 0.0f);
    }

    void OpenALSource::SetSourcePitch(float pitch)
    {
        alSourcef(m_Source, AL_PITCH, std::clamp(pitch, 0.0f, 2.0f));
    }

    void OpenALSource::SetSourceVolume(float volume)
    {
        alSourcef(m_Source, AL_GAIN, std::clamp(volume, GetSourceMinVolume(), GetSourceMaxVolume()));
    }

    void OpenALSource::SetSourceMinVolume(float minVolume)
    {
        alSourcef(m_Source, AL_MIN_GAIN, std::clamp(minVolume, 0.0f, 1.0f));
    }

    void OpenALSource::SetSourceMaxVolume(float maxVolume)
    {
        alSourcef(m_Source, AL_MAX_GAIN, std::clamp(maxVolume, 0.0f, 1.0f));
    }

    void OpenALSource::SetSourceMaxDistance(float maxDistance)
    {
        alSourcef(m_Source, AL_MAX_DISTANCE, std::clamp(maxDistance, 0.0f, 65000.0f));
    }

    void OpenALSource::SetSourceRolloffFactor(float rolloffFactor)
    {
        alSourcef(m_Source, AL_ROLLOFF_FACTOR, std::clamp(rolloffFactor, 0.0f, 10.0f));
    }

    void OpenALSource::SetSourceLooping(bool loop)
    {
        alSourcei(m_Source, AL_LOOPING, loop);
    }

    void OpenALSource::GetSourcePosition(float& x, float& y)
    {
        float z;
        alGetSource3f(m_Source, AL_POSITION, &x, &y, &z);
    }

    void OpenALSource::GetSourceVelocity(float& x, float& y)
    {
        float z;
        alGetSource3f(m_Source, AL_VELOCITY, &x, &y, &z);
    }

    void OpenALSource::GetSourceDirection(float& x, float& y)
    {
        float z;
        alGetSource3f(m_Source, AL_DIRECTION, &x, &y, &z);
    }

    float OpenALSource::GetSourcePitch()
    {
        float result;
        alGetSourcef(m_Source, AL_PITCH, &result);
        return result;
    }

    float OpenALSource::GetSourceVolume()
    {
        float result;
        alGetSourcef(m_Source, AL_GAIN, &result);
        return result;
    }

    float OpenALSource::GetSourceMinVolume()
    {
        float result;
        alGetSourcef(m_Source, AL_MIN_GAIN, &result);
        return result;
    }

    float OpenALSource::GetSourceMaxVolume()
    {
        float result;
        alGetSourcef(m_Source, AL_MAX_GAIN, &result);
        return result;
    }

    float OpenALSource::GetSourceMaxDistance()
    {
        float result;
        alGetSourcef(m_Source, AL_MAX_DISTANCE, &result);
        return result;
    }

    float OpenALSource::GetSourceRolloffFactor()
    {
        float result;
        alGetSourcef(m_Source, AL_ROLLOFF_FACTOR, &result);
        return result;
    }

    bool OpenALSource::GetSourceLooping()
    {
        int looping;
        alGetSourcei(m_Source, AL_LOOPING, &looping);
        return looping;
    }

    uint32_t OpenALSource::GetSourceType()
    {
        int type;
        alGetSourcei(m_Source, AL_SOURCE_TYPE, &type);
        return type;
    }

    uint32_t OpenALSource::GetSourceState()
    {
        int state;
        alGetSourcei(m_Source, AL_SOURCE_STATE, &state);
        return state;
    }

    float OpenALSource::GetSourceOffset()
    {
        float offset;
        alGetSourcef(m_Source, AL_SEC_OFFSET, &offset);
        return offset;
    }

    float OpenALSource::GetSourceLength()
    {
        float length;
        alGetSourcef(m_Source, AL_SEC_LENGTH_SOFT, &length);
        return length;
    }
}