#include "Hazel/Audio/AudioLibrary.h"

#include "Hazel/Audio/AudioContext.h"
#include "Hazel/Audio/AudioBuffer.h"
#include "Hazel/Audio/AudioSource.h"

namespace Hazel
{
    static AudioContext* s_Context = nullptr;
    std::unordered_map<uint16_t, Ref<AudioBuffer>> AudioLibrary::s_BufferMap = std::unordered_map<uint16_t, Ref<AudioBuffer>>();
    std::unordered_map<uint16_t, Ref<AudioSource>> AudioLibrary::s_SourceMap = std::unordered_map<uint16_t, Ref<AudioSource>>();

    void AudioLibrary::Init()
    {
        s_Context = AudioContext::CreatePtr();
    }

    void AudioLibrary::Shutdown()
    {
        delete s_Context;
    }

    void AudioLibrary::CreateSoundBuffer(const std::string& filepath, uint16_t id)
    {
        s_BufferMap[id] = AudioBuffer::Create();
        s_BufferMap[id]->LoadSound(filepath);
    }

    void AudioLibrary::CreateSoundSource(uint16_t bufferID, uint16_t id)
    {
        s_SourceMap[id] = AudioSource::Create();
        s_SourceMap[id]->SetData(GetSoundBuffer(bufferID)->GetBuffer());
    }

    Ref<AudioBuffer>& AudioLibrary::GetSoundBuffer(uint16_t id)
    {
        return s_BufferMap[id];
    }

    Ref<AudioSource>& AudioLibrary::GetSoundSource(uint16_t id)
    {
        return s_SourceMap[id];
    }

    int AudioLibrary::GetBufferFrequency(uint16_t id)
    {
        return GetSoundBuffer(id)->GetBufferFrequency();
    }

    int AudioLibrary::GetBufferBits(uint16_t id)
    {
        return GetSoundBuffer(id)->GetBufferBits();
    }

    int AudioLibrary::GetBufferChannels(uint16_t id)
    {
        return GetSoundBuffer(id)->GetBufferChannels();
    }

    int AudioLibrary::GetBufferSize(uint16_t id)
    {
        return GetSoundBuffer(id)->GetBufferSize();
    }

    void AudioLibrary::PlaySource(uint16_t id)
    {
        GetSoundSource(id)->Play();
    }

    void AudioLibrary::PauseSource(uint16_t id)
    {
        GetSoundSource(id)->Pause();
    }

    void AudioLibrary::RewindSource(uint16_t id)
    {
        GetSoundSource(id)->Rewind();
    }

    void AudioLibrary::StopSource(uint16_t id)
    {
        GetSoundSource(id)->Stop();
    }

    void AudioLibrary::SetSourcePosition(uint16_t id, const glm::vec2& pos)
    {
        GetSoundSource(id)->SetSourcePosition(pos.x, pos.y);
    }

    void AudioLibrary::SetSourceVelocity(uint16_t id, const glm::vec2& pos)
    {
        GetSoundSource(id)->SetSourceVelocity(pos.x, pos.y);
    }

    void AudioLibrary::SetSourceDirection(uint16_t id, const glm::vec2& pos)
    {
        GetSoundSource(id)->SetSourceDirection(pos.x, pos.y);
    }

    void AudioLibrary::SetSourcePitch(uint16_t id, float pitch)
    {
        GetSoundSource(id)->SetSourcePitch(pitch);
    }

    void AudioLibrary::SetSourceVolume(uint16_t id, float volume)
    {
        GetSoundSource(id)->SetSourceVolume(volume);
    }

    void AudioLibrary::SetSourceMinVolume(uint16_t id, float minVolume)
    {
        GetSoundSource(id)->SetSourceMinVolume(minVolume);
    }

    void AudioLibrary::SetSourceMaxVolume(uint16_t id, float maxVolume)
    {
        GetSoundSource(id)->SetSourceMaxVolume(maxVolume);
    }

    void AudioLibrary::SetSourceMaxDistance(uint16_t id, float maxDistance)
    {
        GetSoundSource(id)->SetSourceMaxDistance(maxDistance);
    }

    void AudioLibrary::SetSourceRolloffFactor(uint16_t id, float rolloffFactor)
    {
        GetSoundSource(id)->SetSourceRolloffFactor(rolloffFactor);
    }

    void AudioLibrary::SetSourceLooping(uint16_t id, bool loop)
    {
        GetSoundSource(id)->SetSourceLooping(loop);
    }

    glm::vec2 AudioLibrary::GetSourcePosition(uint16_t id)
    {
        glm::vec2 value;
        GetSoundSource(id)->GetSourcePosition(value.x, value.y);
        return value;
    }

    glm::vec2 AudioLibrary::GetSourceVelocity(uint16_t id)
    {
        glm::vec2 value;
        GetSoundSource(id)->GetSourceVelocity(value.x, value.y);
        return value;
    }

    glm::vec2 AudioLibrary::GetSourceDirection(uint16_t id)
    {
        glm::vec2 value;
        GetSoundSource(id)->GetSourceDirection(value.x, value.y);
        return value;
    }

    float AudioLibrary::GetSourcePitch(uint16_t id)
    {
        return GetSoundSource(id)->GetSourcePitch();
    }

    float AudioLibrary::GetSourceVolume(uint16_t id)
    {
        return GetSoundSource(id)->GetSourceVolume();
    }

    float AudioLibrary::GetSourceMinVolume(uint16_t id)
    {
        return GetSoundSource(id)->GetSourceMinVolume();
    }

    float AudioLibrary::GetSourceMaxVolume(uint16_t id)
    {
        return GetSoundSource(id)->GetSourceMaxVolume();
    }

    float AudioLibrary::GetSourceMaxDistance(uint16_t id)
    {
        return GetSoundSource(id)->GetSourceMaxDistance();
    }

    float AudioLibrary::GetSourceRolloffFactor(uint16_t id)
    {
        return GetSoundSource(id)->GetSourceRolloffFactor();
    }

    bool AudioLibrary::GetSourceLooping(uint16_t id)
    {
        return GetSoundSource(id)->GetSourceLooping();
    }

    AudioLibrary::Type AudioLibrary::GetSourceType(uint16_t id)
    {
        switch (GetSoundSource(id)->GetSourceType())
        {
        case 0x1028: return Type::STATIC;
        case 0x1029: return Type::STREAMING;
        case 0x1030: return Type::UNDETERMINED;
        default: { HZ_CORE_ASSERT(false, "Unknown Source type"); return Type::UNDETERMINED; }
        }
    }

    AudioLibrary::State AudioLibrary::GetSourceState(uint16_t id)
    {
        switch (GetSoundSource(id)->GetSourceState())
        {
        case 0x1011: return State::INITIAL;
        case 0x1012: return State::PLAYING;
        case 0x1013: return State::PAUSED;
        case 0x1014: return State::STOPPED;
        default: { HZ_CORE_ASSERT(false, "Unknown Source state"); return State::INITIAL; }
        }
    }

    float AudioLibrary::GetSourceOffset(uint16_t id)
    {
        return GetSoundSource(id)->GetSourceOffset();
    }

    float AudioLibrary::GetSourceLength(uint16_t id)
    {
        return GetSoundSource(id)->GetSourceLength();
    }

    void AudioLibrary::SetListenerPosition(const glm::vec2& pos)
    {
        s_Context->SetListenerPosition(pos.x, pos.y);
    }

    void AudioLibrary::SetListenerVelocity(const glm::vec2& vel)
    {
        s_Context->SetListenerVelocity(vel.x, vel.y);
    }

    void AudioLibrary::SetListenerVolume(float volume)
    {
        s_Context->SetListenerVolume(volume);
    }

    void AudioLibrary::SetListenerOrientation(const glm::vec3& atVector, const glm::vec3& upVector)
    {
        s_Context->SetListenerOrientation(atVector.x, atVector.y, atVector.z, upVector.x, upVector.y, upVector.z);
    }

    glm::vec2 AudioLibrary::GetListenerPosition()
    {
        glm::vec2 value;
        s_Context->GetListenerPosition(value.x, value.y);
        return value;
    }

    glm::vec2 AudioLibrary::GetListenerVelocity()
    {
        glm::vec2 value;
        s_Context->GetListenerVelocity(value.x, value.y);
        return value;
    }

    float AudioLibrary::GetListenerVolume()
    {
        return s_Context->GetListenerVolume();
    }

    std::pair<glm::vec3, glm::vec3> AudioLibrary::GetListenerOrientation()
    {
        float atX, atY, atZ, upX, upY, upZ;
        s_Context->GetListenerOrientation(atX, atY, atZ, upX, upY, upZ);
        return std::make_pair<glm::vec3, glm::vec3>({ atX, atY, atZ }, { upX, upY, upZ });
    }
}