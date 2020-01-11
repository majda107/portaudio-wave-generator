#ifndef PLAYER_H
#define PLAYER_H

#include "portaudio.h"
#include "soundtable.h"

class Player
{
public:
    Player();

    void Open();
    void Close();

    void Play();
    void Stop();

    SoundTable *data;

private:
    static int StreamCallback(const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

    PaStream *stream;
    PaStreamParameters *params;
};

#endif // PLAYER_H
