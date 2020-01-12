#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "soundtable.h"
#include "player.h"

#include <QMainWindow>
#include <QPainter>
#include <QSlider>
#include <QSpinBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void Play();
    ~MainWindow();

    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;

    Player* player;
    QSlider *slider;
    QSpinBox *frequencyBox;

    QGroupBox *radioBox;

    QRadioButton *sineButton;
    QRadioButton *sawButton;

    QTimer *timer;
    float elapsed;

private slots:
    void handleFrequency(int value);
    void handleShapeChange();
};
#endif // MAINWINDOW_H
