#include "sinetable.h"
#include "soundtable.h"
#include "math.h"

#define PI 3.14159

SineTable::SineTable():SoundTable(44100, 128, 0)
{
    this->data = (float*)malloc(sizeof(float)*this->size);
    this->current = 0;
}

SineTable::~SineTable()
{
    free(this->data);
}

void SineTable::Generate(double frequency)
{
    this->size = this->SampleRate() / frequency;
    free(this->data);
    this->data = (float*)malloc(sizeof(float)*this->size);
    this->current = this->current % this->size;

    for(unsigned long i = 0; i < this->size; i++)
    {
        this->data[i] = (float)sin((double)i / (double)this->size * (double)PI * 2);
    }
}

float SineTable::GetValue()
{
    if(this->current < 0 || this->current >= this->size) return 0;
    return this->data[this->current];
}

void SineTable::Next()
{
    this->current++;
    if(this->current >= this->size) this->current -= this->size;
}
