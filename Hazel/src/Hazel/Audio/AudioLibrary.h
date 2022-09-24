#pragma once

#include "Hazel/Core/Base.h"

#include <glm/vec2.hpp>
#include <unordered_map>

namespace Hazel
{
    class AudioBuffer;
    class AudioSource;

    class AudioLibrary
    {
        AudioLibrary() = delete;
        AudioLibrary(AudioLibrary&&) = delete;
        AudioLibrary(const AudioLibrary&) = delete;
        AudioLibrary& operator=(const AudioLibrary&) = delete;
        AudioLibrary& operator=(AudioLibrary&&) = delete;
        ~AudioLibrary() = delete;
    public:
        enum class Type : uint8_t
        {
            STATIC, STREAMING, UNDETERMINED
        };
        enum class State : uint8_t
        {
            INITIAL, PLAYING, PAUSED, STOPPED
        };
        static void Init();
        static void Shutdown();

        static Ref<AudioBuffer>& GetSoundBuffer(uint16_t id);
        static Ref<AudioSource>& GetSoundSource(uint16_t id);

        static void CreateSoundBuffer(const std::string& filepath, uint16_t id);
        static int GetBufferFrequency(uint16_t id);
        static int GetBufferBits(uint16_t id);
        static int GetBufferChannels(uint16_t id);
        static int GetBufferSize(uint16_t id);

        static void CreateSoundSource(uint16_t bufferID, uint16_t id);
        static void PlaySource(uint16_t id);
        static void PauseSource(uint16_t id);
        static void RewindSource(uint16_t id);
        static void StopSource(uint16_t id);

        static void SetSourcePosition(uint16_t id, const glm::vec2& pos);
        static void SetSourceVelocity(uint16_t id, const glm::vec2& pos);
        static void SetSourceDirection(uint16_t id, const glm::vec2& pos);
        static void SetSourcePitch(uint16_t id, float pitch);
        static void SetSourceVolume(uint16_t id, float volume);
        static void SetSourceMinVolume(uint16_t id, float minVolume);
        static void SetSourceMaxVolume(uint16_t id, float maxVolume);
        static void SetSourceMaxDistance(uint16_t id, float maxDistance);
        static void SetSourceRolloffFactor(uint16_t id, float rolloffFactor);
        static void SetSourceLooping(uint16_t id, bool loop);
        
        static glm::vec2 GetSourcePosition(uint16_t id);
        static glm::vec2 GetSourceVelocity(uint16_t id);
        static glm::vec2 GetSourceDirection(uint16_t id);
        static float GetSourcePitch(uint16_t id);
        static float GetSourceVolume(uint16_t id);
        static float GetSourceMinVolume(uint16_t id);
        static float GetSourceMaxVolume(uint16_t id);
        static float GetSourceMaxDistance(uint16_t id);
        static float GetSourceRolloffFactor(uint16_t id);
        static bool GetSourceLooping(uint16_t id);
        static Type GetSourceType(uint16_t id);
        static State GetSourceState(uint16_t id);
        static float GetSourceOffset(uint16_t id);
        static float GetSourceLength(uint16_t id);

        static void SetListenerPosition(const glm::vec2& pos);
        static void SetListenerVelocity(const glm::vec2& vel);
        static void SetListenerVolume(float volume);
        static void SetListenerOrientation(const glm::vec3& atVector, const glm::vec3& upVector);

        static glm::vec2 GetListenerPosition();
        static glm::vec2 GetListenerVelocity();
        static float GetListenerVolume();
        static std::pair<glm::vec3, glm::vec3> GetListenerOrientation();
    private:
        static std::unordered_map<uint16_t, Ref<AudioBuffer>> s_BufferMap;
        static std::unordered_map<uint16_t, Ref<AudioSource>> s_SourceMap;
    };
}