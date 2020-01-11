#include "mainwindow.h"
#include "sinetable.h"
#include "player.h"
#include "portaudio.h"

#include <stdio.h>
#include <QApplication>
#include <QSlider>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto err = Pa_Initialize();
    printf("%s", Pa_GetErrorText(err));

    MainWindow *w = new MainWindow();
    w->show();

    w->Play();

    return a.exec();
}
