#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>

class PaintArea : public QGraphicsScene
{
  Q_OBJECT  

  public:
   PaintArea( qreal x, qreal y, qreal width, qreal height, QObject * parent);
//   PaintArea(QWidget *parent = 0);
  public slots:
    void setCurrentTool(int);
  protected :
    void mousePressEvent(QGraphicsSceneMouseEvent* );
    void mouseMoveEvent(QGraphicsSceneMouseEvent* );
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* );
  private :
   int _currentTool;
   QPointF  _startPoint,_endPoint, _offset;
   QGraphicsItem * _item;
   QPolygon _polygon;
};
#endif

