#include "sawtable.h"
#include "../soundtable.h"

#include <stdlib.h>
#include <math.h>

SawTable::SawTable():SoundTable(44100, 128, 0)
{
    this->current = 0;
}

void SawTable::Generate(double frequency, int harmonics)
{
    this->size = this->SampleRate() / frequency;
    this->data = (float*)malloc(sizeof(float) * this->size);

    int sign = 0;
    this->current %= this->size;
    for(unsigned long i = 0; i < this->size; i++)
    {
        sign = 1;
        for(int h = 0; h < harmonics; h++)
        {
            this->data[i] += sign * (double)1/h * sin((double)h * ((double)i / (double)this->size * 3.14 * 2));
            sign *= -1;
        }
    }
}

float SawTable::GetValue()
{
    if(this->current < 0 || this->current >= this->size) return 0;
    return this->data[this->current];
}

void SawTable::Next()
{
    this->current ++;
    if(this->current >= this->size) this->current -= this->size;
}
