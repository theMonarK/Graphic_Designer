#include "paintArea.h"
#include <QGraphicsRectItem>
#include <QGraphicsEffect>

PaintArea::PaintArea(qreal x, qreal y, qreal width, qreal height, QObject * parent = 0) : QGraphicsScene(x, y, width, height, parent) {
  qDebug() << "PaintArea::PaintArea(void)";
  _startPoint = _endPoint = _offset = QPointF(0,0);
  addRect(QRectF(100,100,200,300));
  _item=NULL;
//  this->show();
}

void PaintArea::mousePressEvent(QGraphicsSceneMouseEvent* evt) {
  qDebug() << "PaintArea::mousePressEvent(void)";
  qDebug() <<  "evt->pos()" << evt->pos(); 
  qDebug() <<  "evt->scenePos()" <<  evt->scenePos(); 

 for (int i =0; i<items().size();i++) {
    items().value(i)->show();
    qDebug() << "item number" << i;
  }

 _startPoint = _endPoint = evt->scenePos();
  _item=itemAt(_startPoint);
  if (_item) {
    QList<QGraphicsItem *>   items = collidingItems(_item);
    for (int i =0; i< items.size();i++) {
     items.value(i)->hide();
    }
    _offset =  _startPoint - _item->pos();
//    _item->setPos(_startPoint - _offset );
//    _item->setPos( _item->pos());
    _item->grabMouse();
  }
 
}

void PaintArea::mouseMoveEvent(QGraphicsSceneMouseEvent* evt) 
{
  if (_item) {
  qDebug() << "PaintArea::mouseMoveEvent(void)";
     _item->setPos(evt->scenePos() - _offset);
  }
  _endPoint = evt->scenePos(); 
}

void PaintArea::mouseReleaseEvent(QGraphicsSceneMouseEvent* evt) 
{
  qDebug() << "PaintArea::mouseReleaseEvent(void)";
  if (_item) {
    _item->setPos(evt->scenePos() - _offset);
    _item->ungrabMouse();
    _item=NULL;
  }
  else if (_startPoint != _endPoint) {
//    addLine( _startPoint.x(), _startPoint.y(), _endPoint.x(), _endPoint.y() );

    QGraphicsRectItem *rect = addRect(_startPoint.x(), _startPoint.y(), _endPoint.x() - _startPoint.x(), _endPoint.y() - _startPoint.y());
    rect->setFlag(QGraphicsItem::ItemIsMovable);
 }
 _endPoint = evt->scenePos();
  qDebug() << items().size();
}

void PaintArea::setCurrentTool(int tool) {
  _currentTool = tool;
  qDebug () << _currentTool;
}
