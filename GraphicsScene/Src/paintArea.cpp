#include "paintArea.h"
#include <QGraphicsRectItem>
#include <QGraphicsEffect>

PaintArea::PaintArea(qreal x, qreal y, qreal width, qreal height, QObject * parent = 0) : QGraphicsScene(x, y, width, height, parent) {
  qDebug() << "PaintArea::PaintArea(void)";

  _startPoint = _endPoint = _offset = QPointF(0,0);
  addRect(QRectF(100,100,200,300));
  _item=NULL;
  _currentPen.setStyle(Qt::SolidLine);
  _currentPen.setColor(Qt::black);
  _currentPen.setWidth(10);
  _currentBrush = Qt::SolidPattern;
  _currentBrush.setColor(Qt::black);
  setCurrentFont(QFont("Helvetica [Cronyx]", 10));
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
    qDebug() <<  "item->" <<  _item->type();
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
      switch(_currentTool){
      case TOOLS_ID_FREEHAND:
      {
          break;
      }
      case TOOLS_ID_LINE:
      {
          QGraphicsLineItem *line = addLine( _startPoint.x(), _startPoint.y(), _endPoint.x(), _endPoint.y() );
          line->setFlag(QGraphicsItem::ItemIsMovable);
          line->setPen(_currentPen);
          break;
      }      
      case TOOLS_ID_RECTANGLE:
      {
          QGraphicsRectItem *rect = addRect(_startPoint.x(), _startPoint.y(), _endPoint.x() - _startPoint.x(), _endPoint.y() - _startPoint.y());
          rect->setFlag(QGraphicsItem::ItemIsMovable);
          rect->setPen(_currentPen);
          break;
      }      
      case TOOLS_ID_CIRCLE:
      {
          QGraphicsEllipseItem *ellipse = addEllipse(_startPoint.x(), _startPoint.y(), _endPoint.x() - _startPoint.x(), _endPoint.y() - _startPoint.y());
          ellipse->setFlag(QGraphicsItem::ItemIsMovable);
          ellipse->setPen(_currentPen);
          break;
      }
      case TOOLS_ID_POLYGON:
      {
          break;
      }
      case TOOLS_ID_TEXT:
      {
          QGraphicsTextItem *text = addText("Text");
          text->setPos(_startPoint.x(), _startPoint.y());
          text->setVisible(true);
          text->setFont(_currentFont);
          text->setFlag(QGraphicsItem::ItemIsMovable);
          break;
      }
    }
 }
 _endPoint = evt->scenePos();
  qDebug() << items().size();
}

void PaintArea::setCurrentTool(int tool) {
  _currentTool = tool;
  qDebug () << _currentTool;
}

void PaintArea::setCurrentPenStyle(int stylePen) {
    switch(stylePen) {
        case STYLE_PEN_ID_SOLID :{
            _currentPen.setStyle(Qt::SolidLine);
            break;
        }
        case STYLE_PEN_ID_DASH :{
            _currentPen.setStyle(Qt::DashLine);
            break;
        }
        case STYLE_PEN_ID_DOT :{
            _currentPen.setStyle(Qt::DotLine);
            break;
        }
        case STYLE_PEN_ID_DASHDOT :{
            _currentPen.setStyle(Qt::DashDotLine);
            break;
        }
        case STYLE_PEN_ID_DASHDOTDOT :{
            _currentPen.setStyle(Qt::DashDotDotLine);
            break;
        }
        case STYLE_PEN_ID_NONE :{
            _currentPen.setStyle(Qt::NoPen);
            break;
        }
    }
}


void PaintArea::setCurrentBrushFill(int styleBrush) {
    switch(styleBrush) {
        case STYLE_BRUSH_ID_SOLID :{
            _currentBrush = Qt::SolidPattern;
            _currentPen.setBrush(_currentBrush);
            break;
        }
        case STYLE_BRUSH_ID_BDIAGONAL :{
            _currentBrush = Qt::BDiagPattern;
            _currentPen.setBrush(_currentBrush);
            break;
        }
        case STYLE_BRUSH_ID_FDIAGONAL :{
            _currentBrush = Qt::BDiagPattern;
            _currentPen.setBrush(_currentBrush);
            break;
        }
        case STYLE_BRUSH_ID_DENSE3 :{
            _currentBrush = Qt::BDiagPattern;
            _currentPen.setBrush(_currentBrush);
            break;
        }
        case STYLE_BRUSH_ID_DENSE4 :{
            _currentBrush = Qt::BDiagPattern;
            _currentPen.setBrush(_currentBrush);
            break;
        }
        case STYLE_BRUSH_ID_DENSE5 :{
            _currentBrush = Qt::BDiagPattern;
            _currentPen.setBrush(_currentBrush);
            break;
        }
        case STYLE_BRUSH_ID_DENSE6 :{
            _currentBrush = Qt::BDiagPattern;
            _currentPen.setBrush(_currentBrush);
            break;
        }
        case STYLE_BRUSH_ID_NONE :{
            _currentBrush = Qt::BDiagPattern;
            _currentPen.setBrush(_currentBrush);
            break;
        }
    }
}

void PaintArea::setCurrentFont(QFont font) {
    _currentFont = font;
}

void PaintArea::setCurrentPenColor(QColor color) {
    _currentPen.setColor(color);
}

void PaintArea::setCurrentPenWidth(int width) {
    _currentPen.setWidth(width);
}

void PaintArea::setCurrentBrushColor(QColor color) {
    _currentBrush.setColor(color);
}


 QGraphicsItem *PaintArea::getItem(void){
     return _item;
 }

 QFont PaintArea::getCurrentFont(void){
     return _currentFont;
 }

 QPen PaintArea::getCurrentPen(void){
     return _currentPen;
 }

 QBrush PaintArea::getCurrentBrush(void){
     return _currentBrush;
 }

