#ifndef SINETABLE_H
#define SINETABLE_H

#include "soundtable.h"

class SineTable: public SoundTable
{
public:
    SineTable();
    ~SineTable();

    void Generate(double frequency);

    float GetValue();
    void Next();

private:
    unsigned long current;
    float *data;
};

#endif // SINETABLE_H
