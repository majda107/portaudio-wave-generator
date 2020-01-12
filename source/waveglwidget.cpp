#include "waveglwidget.h"
#include <QOpenGLBuffer>


WaveGLWidget::WaveGLWidget(QWidget *parent):QOpenGLWidget(parent)
{
    this->m_projection = new QMatrix4x4();
    this->program = 0;
    this->model = 0;
    this->elapsed = 0;

    this->setUpdateBehavior(QOpenGLWidget::UpdateBehavior::PartialUpdate);
}

void WaveGLWidget::initializeGL()
{
    QOpenGLFunctions_4_2_Core *func = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_2_Core>();


    GLfloat vertices[] = 
    {
        -1.0f, 1.0f, 0,
        -1.0f, -1.0, 0,
        1.0f, -1.0f, 0,
        -1.0f, 1.0f, 0,
        1.0f, -1.0f, 0,
        1.0f, 1.0f, 0
    };

    this->model = new QOpenGLVertexArrayObject();
    this->model->create();
    this->model->bind();

    QOpenGLBuffer buffer;
    buffer.create();
    buffer.bind();
    buffer.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    buffer.allocate(18 * sizeof(float));
    buffer.write(0, vertices, 18 * sizeof(float));
    func->glVertexAttribPointer(0, 3, GL_FLOAT, false, false, 0);
    buffer.release();

    this->model->release();


        this->program = new QOpenGLShaderProgram();
        this->program->addShaderFromSourceFile(QOpenGLShader::Vertex, "source/shaders/VertexShader.glsl");
        this->program->addShaderFromSourceFile(QOpenGLShader::Fragment, "source/shaders/FragmentShader.glsl");
        this->program->link();

        this->program->bindAttributeLocation("position", 0);
        elapsed_location = this->program->uniformLocation("elapsed");

        func->glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    }

void WaveGLWidget::resizeGL(int w, int h)
{
    this->m_projection->setToIdentity();
    this->m_projection->perspective(45.0f, (double)w/(double)h, 0.01f, 10.0f);
}

void WaveGLWidget::paintGL()
{
    QOpenGLFunctions_4_2_Core *func = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_2_Core>();
    func->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    qDebug("%f", this->elapsed);


    this->program->bind();
    func->glUniform1f(this->elapsed_location, elapsed);

    this->model->bind();

    func->glEnable(GL_MULTISAMPLE);

    func->glEnableVertexAttribArray(0);
    func->glDrawArrays(GL_TRIANGLES, 0, 18);
    func->glDisableVertexAttribArray(0);

    this->model->release();

    this->program->release();

    this->elapsed += 0.1f;
}