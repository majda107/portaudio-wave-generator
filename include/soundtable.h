#ifndef SOUNDTABLE_H
#define SOUNDTABLE_H

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

protected:
    double sampleRate;
    unsigned long size;
    unsigned long frameSize;
};

#endif // SOUNDTABLE_H
