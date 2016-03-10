#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paintArea.h"

#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QAction>
#include <QActionGroup>
#include <QToolBar>
#include <QMessageBox>
#include <QDate>
#include <QSignalMapper>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "enums.h"

class MainWindow : public QMainWindow
{
Q_OBJECT
  public:
   MainWindow(QWidget *parent = 0);
  private:
   PaintArea* _area; 
   void _createMenus(void);
   void _createToolbars(void);
   void _createActions(void);
   void _connectActions(void);
   void _connectSignals(void);

   QMenu *_fileMenu, *_toolMenu, *_styleMenu, *_helpMenu;
   QMenu *_penSubMenu, *_brushSubMenu, *_fontSubMenu;
   QMenu *_penLineSubMenu, *_penWidthSubMenu;
   QToolBar *_toolBar;
   QAction *_newAction,*_openAction, *_exitAction, *_saveAction, *_saveAsAction;
   QAction *_aboutAction, *_aboutQtAction;
   QAction *_freehandAct, *_lineAct, *_rectangleAct, *_ellipseAct, *_polygonAct;
   QAction *_penColorAct;
   QActionGroup *_toolsQag;
   QSignalMapper *_signalMapper;
  private slots :
     void _newFile();
     void _exit();
     void _about();
     void _aboutQt();
  signals:
   void toolMapped(int digit);
};
#endif

