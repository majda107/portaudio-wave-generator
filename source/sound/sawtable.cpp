#include "sawtable.h"
#include "soundtable.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

SawTable::SawTable():SoundTable(44100, 128, 0)
{
    this->current = 0;
    this->frequency = 0;
    this->harmonics = 0;

    this->data = nullptr;
}

void SawTable::generate(double frequency, int harmonics)
{
    this->frequency = frequency;
    this->harmonics = harmonics;

    this->size = this->SampleRate() / frequency;

    if(this->data != nullptr)
        free(this->data);
    this->data = (float*)malloc(sizeof(float) * this->size);

    double sign = 0;
    double x = 0;

    this->current %= this->size;
    for(unsigned long i = 0; i < this->size; i++)
    {
        sign = 1;
        this->data[i] = 0;
        for(int h = 1; h <= harmonics; h++)
        {
            x = sin(h * ((double)i / (double)this->size * 3.14 * 2));
            this->data[i] += sign * ((double)1/(double)h) * x;
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

QPolygonF* SawTable::plot(float width, float amp)
{
    QPolygonF *polyline = new QPolygonF();
    double wave_count = this->frequency /100;
    double val;
    double y;
    double sign;

    for(int x = 0; x < width; x++)
    {
        sign = 1;
        val = 0;
        y = 0;
        
        for(int h = 1; h <= this->harmonics; h++)
        {
            val = sin(h * ((double)x / (double)width * 3.14 * 2 * wave_count));
            y += sign * ((double)1/(double)h) * val;
            sign *= -1;
        }

        // val = sin((double)x/(double)width * 3.14 * 2);
        *polyline << QPointF(x, y*amp + 300);
    }

    return polyline;
}
