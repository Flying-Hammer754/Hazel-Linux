#include "Hazel/Audio/AudioSource.h"

#include "Platform/OpenAL/OpenALSource.h"

namespace Hazel
{
    Ref<AudioSource> AudioSource::Create()
    {
        return CreateRef<OpenALSource>();
    }
}