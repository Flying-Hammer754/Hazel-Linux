#include "Hazel/Audio/AudioContext.h"

#include "Platform/OpenAL/OpenALContext.h"

namespace Hazel
{
    Ref<AudioContext> AudioContext::Create()
    {
        return CreateRef<OpenALContext>();
    }

    AudioContext* AudioContext::CreatePtr()
    {
        return new OpenALContext();
    }
}