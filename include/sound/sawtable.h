#ifndef SAWTABLE_H
#define SAWTABLE_H

#include "../soundtable.h"

class SawTable: public SoundTable
{
public:
    SawTable();
    ~SawTable();
    void Generate(double frequency, int harmonics);

    float GetValue();
    void Next();

    QPolygonF* plot(float width, float amp);

private:
    float *data;
    unsigned long current;
    float frequency;
    float harmonics;
};

#endif // SAWTABLE_H
