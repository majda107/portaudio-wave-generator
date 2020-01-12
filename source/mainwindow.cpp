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
    this->slider->setGeometry(10, 80, this->width()-20, 20);

    this->frequencyBox = new QSpinBox(this);
    this->frequencyBox->setMinimum(this->slider->minimum());
    this->frequencyBox->setMaximum(this->slider->maximum());
    this->frequencyBox->setGeometry(10, 120, 200, 20);
    this->frequencyBox->setSuffix("Hz");

    QObject::connect(this->slider, SIGNAL(valueChanged(int)), this, SLOT(handleFrequency(int)));
    QObject::connect(this->frequencyBox, SIGNAL(valueChanged(int)), this, SLOT(handleFrequency(int)));

    this->radioBox = new QGroupBox("Shapes", this);
    this->radioBox->setGeometry(10, 500, 200, 100);

    this->sineButton = new QRadioButton("Sine wave", this->radioBox);
    this->sineButton->setChecked(true);

    this->sawButton = new QRadioButton("Saw wave", this->radioBox);

    auto layout = new QVBoxLayout;
    layout->addWidget(sineButton);
    layout->addWidget(sawButton);

    radioBox->setLayout(layout);

    QObject::connect(this->sawButton, SIGNAL(clicked(bool)), this, SLOT(handleShapeChange()));
    QObject::connect(this->sineButton, SIGNAL(clicked(bool)), this, SLOT(handleShapeChange()));

    this->canvas = new Canvas(this);
    this->canvas->setGeometry(10, 200, this->width() - 20, 300);

    this->timer = new QTimer();
    this->timer->setInterval(10);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(call_update()));

    this->elapsed = 0;

    this->player = new Player();
}

MainWindow::~MainWindow()
{
    delete ui;
    Pa_Terminate();
}

void MainWindow::Play()
{
    this->player->data = new SineTable();

    this->player->Open();
    this->player->Play();

    this->slider->setValue(600);
    this->timer->start();
}

void MainWindow::call_update()
{

    this->canvas->setPolyline(this->player->data->plot(this->canvas->width(), this->canvas->height()/3, elapsed));
    this->canvas->update();

    this->elapsed += 0.1f;
}

void MainWindow::handleFrequency(int value)
{
    qDebug("%s - %d", "Slider value has changed!", value);

    this->frequencyBox->blockSignals(true);
    this->slider->blockSignals(true);

    this->frequencyBox->setValue(value);
    this->slider->setValue(value);

    this->frequencyBox->blockSignals(false);
    this->slider->blockSignals(false);

    this->player->data->generate(value, 10);
    this->update();
}

void MainWindow::handleShapeChange()
{
    auto old_table = this->player->data;

    this->player->Stop();
    this->player->Close();

    if(this->sineButton->isChecked())
        this->player->data = new SineTable();

    if(this->sawButton->isChecked())
        this->player->data = new SawTable();

    delete old_table;
    old_table = nullptr;
    this->handleFrequency(this->slider->value());

    this->player->Open();
    this->player->Play();
}
