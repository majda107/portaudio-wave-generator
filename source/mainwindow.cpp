#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sinetable.h"
#include "soundtable.h"
#include "sound/sawtable.h"
#include "math.h"

#include <QPainter>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->slider = new QSlider(Qt::Orientation::Horizontal, this);
    this->slider->setRange(100, 2000);
    this->slider->setValue(600);
    this->slider->setGeometry(10, 80, this->width()-20, 20);
    this->slider->show();

    QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(handleSlider(int)));

    this->player = new Player();
}

MainWindow::~MainWindow()
{
    delete ui;
    Pa_Terminate();
}

void MainWindow::Play()
{
    this->player->data = new SawTable();
    // this->player->data = new SineTable();
    this->generate();

    this->player->Open();
    this->player->Play();
}

void MainWindow::generate()
{
    ((SawTable*)this->player->data)->Generate(this->slider->value(), 10);
    // ((SineTable*)this->player->data)->Generate(this->slider->value());
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::HighQualityAntialiasing);

    double width = this->width();
    int step = 1;

    double y = 0;

    auto polyline = this->player->data->plot(this->width(), 30);
    painter.drawPolyline(*polyline);
    delete polyline;
}

void MainWindow::handleSlider(int value)
{
    qDebug("%s - %d\n", "Slider value has changed!", value);
    // ((SineTable*)this->player->data)->Generate(value);

    this->generate();
    this->update();
}

