#include "soundtable.h"

SoundTable::SoundTable(double sampleRate, unsigned long frameSize, unsigned long size)
{
    this->sampleRate = sampleRate;
    this->frameSize = frameSize;
    this->size = size;
}

SoundTable::~SoundTable()
{

}

double SoundTable::SampleRate()
{
    return this->sampleRate;
}

unsigned long SoundTable::Size()
{
    return this->size;
}

void SoundTable::SetSize(unsigned long value)
{
    this->size = value;
}


unsigned long SoundTable::FrameSize()
{
    return this->frameSize;
}

float SoundTable::GetValue()
{
    return 0;
}

void SoundTable::Next()
{

}

QPolygonF* SoundTable::plot(float width, float amp)
{
    return nullptr;
}