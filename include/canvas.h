#include <QWidget>
#include <QPaintEvent>

#include <QPolygonF>

class Canvas: public QWidget
{
public:
    explicit Canvas(QWidget *parent);
    virtual void paintEvent(QPaintEvent *event);
    
    QPolygonF* polyline();
    void setPolyline(QPolygonF *polyline);

private:
    QPolygonF *line;
};