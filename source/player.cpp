#include <stdio.h>

#include "portaudio.h"
#include "player.h"

int Player::StreamCallback(const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    auto data = (SoundTable*)userData;
    float *out = (float*)output;

    float value = 0;
    for(unsigned long i = 0; i < frameCount; i++)
    {
        value = data->GetValue();
        *out++ = value; // left channel
        *out++ = value; // right channel

        data->Next();
    }

    return paContinue;
}

Player::Player()
{
    this->params = new PaStreamParameters();

    this->params->device = Pa_GetDefaultOutputDevice();
    this->params->channelCount = 2;
    this->params->suggestedLatency = Pa_GetDeviceInfo(this->params->device)->defaultLowOutputLatency;
    this->params->sampleFormat = paFloat32;
    this->params->hostApiSpecificStreamInfo = nullptr;
}

void Player::Open()
{
    Pa_OpenStream(&this->stream, nullptr, this->params, this->data->SampleRate(), this->data->FrameSize(), paClipOff, Player::StreamCallback, this->data);
}

void Player::Close()
{
    Pa_CloseStream(this->stream);
}

void Player::Play()
{
    Pa_StartStream(this->stream);
}

void Player::Stop()
{
    Pa_StopStream(this->stream);
}

