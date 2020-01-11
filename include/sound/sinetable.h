#ifndef SINETABLE_H
#define SINETABLE_H

#include "soundtable.h"
#include <QPolygonF>

class SineTable: public SoundTable
{
public:
    SineTable();
    ~SineTable();

    void generate(double frequency, int harmonics = 0);

    float GetValue();
    void Next();
    
    QPolygonF* plot(float width, float amp);

private:
    unsigned long current;
    float frequency;
    float *data;
};

#endif // SINETABLE_H
