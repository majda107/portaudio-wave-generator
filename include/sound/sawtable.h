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

private:
    float *data;
    unsigned long current;
};

#endif // SAWTABLE_H
