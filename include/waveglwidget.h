#ifndef WAVEGLWIDGET_H
#define WAVEGLWIDGET_H

#include <QOpenGLFunctions_4_2_Core>
#include <QWidget>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShader>
#include <QOpenGLWidget>

class WaveGLWidget: public QOpenGLWidget, protected QOpenGLFunctions_4_2_Core
{
public:
    WaveGLWidget(QWidget *parent);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QMatrix4x4 *m_projection;
    QOpenGLVertexArrayObject *model;
    QOpenGLShaderProgram *program;
};

#endif