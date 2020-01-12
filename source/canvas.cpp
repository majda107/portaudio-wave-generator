#include "canvas.h"

#include <QPainter>

Canvas::Canvas(QWidget *parent): QWidget(parent)
{
    this->line = nullptr;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);

    // qDebug("%s %s", "REDRAWING CANVAS!", typeid(this->line).name());

    if(this->line != nullptr)
    {
        painter.drawPolyline(*this->line);
        delete this->line;
        this->line = nullptr;
    }
}

QPolygonF* Canvas::polyline()
{
    return this->line;
}

void Canvas::setPolyline(QPolygonF *polyline)
{
    this->line = polyline;
}

