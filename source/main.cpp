#include "mainwindow.h"
#include "waveglwidget.h"
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

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    WaveGLWidget *wgw = new WaveGLWidget(w);
    wgw->setGeometry(0, 140, w->width(), 300);

    w->show();
    w->Play();

    // WaveWindow *w = new WaveWindow();
    // w->setAnimating(true);

    // w->show();

    return a.exec();
}
