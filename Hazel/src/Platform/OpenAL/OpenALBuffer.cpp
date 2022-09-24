#include "Platform/OpenAL/OpenALBuffer.h"

#include <AL/al.h>
#include <AL/alext.h>

#include <sndfile.h>

namespace Hazel
{
    OpenALBuffer::OpenALBuffer()
    {

    }

    OpenALBuffer::~OpenALBuffer()
    {
        if (!IsBufferValid())
            return;

        alDeleteBuffers(1, &m_Buffer);
    }

    uint32_t OpenALBuffer::GetBuffer()
    {
        return m_Buffer;
    }

    bool OpenALBuffer::IsBufferValid()
    {
        return !alIsBuffer(m_Buffer);
    }

    void OpenALBuffer::LoadSound(const std::string& filepath)
    {
        ALenum err, format;
        SNDFILE *sndfile;
        SF_INFO sfinfo;
        short *membuf;
        sf_count_t num_frames;
        ALsizei num_bytes;

        /* Open the audio file and check that it's usable. */
        sndfile = sf_open(filepath.c_str(), SFM_READ, &sfinfo);
        HZ_CORE_ASSERT(sndfile, "Could not open audio file");
        if(sfinfo.frames < 1 || sfinfo.frames > (sf_count_t)(INT_MAX/sizeof(short))/sfinfo.channels)
        {
            sf_close(sndfile);
            HZ_CORE_ASSERT(false, "Bad sample count in audio file");
        }

        /* Get the sound format, and figure out the OpenAL format */
        format = AL_NONE;
        switch (sfinfo.channels)
        {
        case 1: format = AL_FORMAT_MONO16; break;
        case 2: format = AL_FORMAT_STEREO16; break;
        case 3: { if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) { format = AL_FORMAT_BFORMAT2D_16; break; } }
        case 4: { if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) { format = AL_FORMAT_BFORMAT3D_16; break; } }
        default: { sf_close(sndfile); HZ_CORE_ASSERT(false, "Unsupported channel count in audio file"); }
        }

        /* Decode the whole audio file to a buffer. */
        membuf = reinterpret_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

        num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
        if(num_frames < 1)
        {
            free(membuf);
            sf_close(sndfile);
            HZ_CORE_ASSERT(false, "Failed to read samples in audio file");
        }
        num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

        /* Buffer the audio data into a new buffer object, then free the data and
        * close the file.
        */
        if (!IsBufferValid())
        {
            alGenBuffers(1, &m_Buffer);
        }
        alBufferData(m_Buffer, format, membuf, num_bytes, sfinfo.samplerate);

        free(membuf);
        sf_close(sndfile);

        /* Check if an error occured, and clean up if so. */
        err = alGetError();
        if(err != AL_NO_ERROR)
        {
            HZ_CORE_ERROR("OpenAL Error: {0} | {1}.", alGetString(err), err);
            if(m_Buffer && alIsBuffer(m_Buffer))
                alDeleteBuffers(1, &m_Buffer);

            HZ_CORE_ASSERT(false, "OpenAL Error");
        }
    }

    int OpenALBuffer::GetBufferFrequency()
    {
        int result;
        alGetBufferi(m_Buffer, AL_FREQUENCY, &result);
        return result;
    }

    int OpenALBuffer::GetBufferBits()
    {
        int result;
        alGetBufferi(m_Buffer, AL_BITS, &result);
        return result;
    }

    int OpenALBuffer::GetBufferChannels()
    {
        int result;
        alGetBufferi(m_Buffer, AL_CHANNELS, &result);
        return result;
    }

    int OpenALBuffer::GetBufferSize()
    {
        int result;
        alGetBufferi(m_Buffer, AL_SIZE, &result);
        return result;
    }
}