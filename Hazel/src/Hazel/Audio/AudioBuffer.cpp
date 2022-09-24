#include "Hazel/Audio/AudioBuffer.h"

#include "Platform/OpenAL/OpenALBuffer.h"

namespace Hazel
{
    Ref<AudioBuffer> AudioBuffer::Create()
    {
        return CreateRef<OpenALBuffer>();
    }
}