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
#include "enums.h"

class PaintArea : public QGraphicsScene
{
  Q_OBJECT  

  public:
   PaintArea( qreal x, qreal y, qreal width, qreal height, QObject * parent);
//   PaintArea(QWidget *parent = 0);
  public slots:
    void setCurrentTool(int);
    void setCurrentPenStyle(int);
    void setCurrentBrushFill(int);
    void setCurrentFont(QFont);
    void setCurrentBrushColor(QColor);
    void setCurrentPenColor(QColor);
    void setCurrentPenWidth(int);
    QPen getCurrentPen(void);
    QBrush getCurrentBrush(void);
    QFont getCurrentFont(void);
    QGraphicsItem * getItem(void);
  protected :
    void mousePressEvent(QGraphicsSceneMouseEvent* );
    void mouseMoveEvent(QGraphicsSceneMouseEvent* );
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* );
  private :
   int _currentTool;
   QFont _currentFont;
   QPen _currentPen;
   QBrush _currentBrush;
   QColor _currentBrushColor, _currentPenColor;
   int _currentBrushWidth, _currentPenWidth;
   QPointF  _startPoint,_endPoint, _offset;
   QGraphicsItem * _item;
   QPolygon _polygon;
};
#endif

