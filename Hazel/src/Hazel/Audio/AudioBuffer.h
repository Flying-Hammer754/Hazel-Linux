#pragma once

#include "Hazel/Core/Base.h"

namespace Hazel
{
    class AudioBuffer
    {
    public:
        virtual ~AudioBuffer() = default;

        virtual void LoadSound(const std::string& filepath) = 0;

        virtual uint32_t GetBuffer() = 0;
        virtual bool IsBufferValid() = 0;

        virtual int GetBufferFrequency() = 0;
        virtual int GetBufferBits() = 0;
        virtual int GetBufferChannels() = 0;
        virtual int GetBufferSize() = 0;

        static Ref<AudioBuffer> Create();
    };
}