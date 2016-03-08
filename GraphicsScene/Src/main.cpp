#include <QApplication>
#include <QGraphicsEllipseItem>
#include "mainWindow.h"

int main(int argc, char* argv[]) {
 
 
     QApplication app(argc, argv);

/*     QGraphicsScene scene;
     QGraphicsEllipseItem* ellipse=scene.addEllipse(-10, -10, 50, 50);
     ellipse->setFlag(QGraphicsItem::ItemIsMovable);
     QGraphicsView view(&scene);
     view.show();
     */
     MainWindow mw;
     mw.show();

    return app.exec();
}
