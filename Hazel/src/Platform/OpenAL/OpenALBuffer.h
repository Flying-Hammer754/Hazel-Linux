#pragma once

#include "Hazel/Audio/AudioBuffer.h"

namespace Hazel
{
    class OpenALBuffer : public AudioBuffer
    {
    public:
        OpenALBuffer();
        virtual ~OpenALBuffer();

        virtual void LoadSound(const std::string& filepath) override;

        virtual uint32_t GetBuffer() override;
        virtual bool IsBufferValid() override;

        virtual int GetBufferFrequency() override;
        virtual int GetBufferBits() override;
        virtual int GetBufferChannels() override;
        virtual int GetBufferSize() override;
    private:
        uint32_t m_Buffer;
    };
}