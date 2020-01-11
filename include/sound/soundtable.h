#ifndef SOUNDTABLE_H
#define SOUNDTABLE_H

#include <QPolygonF>

class SoundTable
{
public:
    SoundTable(double sampleRate, unsigned long frameSize, unsigned long size);
    ~SoundTable();

    double SampleRate();
    unsigned long Size();
    unsigned long FrameSize();

    void SetSize(unsigned long value);

    virtual float GetValue();
    virtual void Next();

    virtual QPolygonF* plot(float width, float amp); 
    virtual void generate(double frequency, int harmonics);

protected:
    double sampleRate;
    unsigned long size;
    unsigned long frameSize;
};

#endif // SOUNDTABLE_H
