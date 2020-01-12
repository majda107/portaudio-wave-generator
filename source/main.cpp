#include "mainwindow.h"
#include "waveglwidget.h"
#include "sinetable.h"
#include "player.h"
#include "portaudio.h"

#include <stdio.h>
#include <QApplication>
#include <QSlider>
#include <QTimer>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    printf("%d", a.applicationPid());

    auto err = Pa_Initialize();
    printf("%s", Pa_GetErrorText(err));


    MainWindow *w = new MainWindow();

    // QSurfaceFormat format;
    // format.setDepthBufferSize(24);
    // format.setStencilBufferSize(8);
    // format.setVersion(4, 2);
    // format.setSamples(10);
    // format.setProfile(QSurfaceFormat::CoreProfile);
    // QSurfaceFormat::setDefaultFormat(format);

    // WaveGLWidget *wgw = new WaveGLWidget(w);
    // wgw->setGeometry(10, 140, w->width()-20, 300);

    // auto timer = new QTimer();
    // timer->setInterval(10);
    // QObject::connect(timer, SIGNAL(timeout()), wgw, SLOT(update()));
    // timer->start();

    w->show();
    w->Play();

    // WaveWindow *w = new WaveWindow();
    // w->setAnimating(true);

    // w->show();

    return a.exec();
}
