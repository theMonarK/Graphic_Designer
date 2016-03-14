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
#include <QFileDialog>
#include <QSpinBox>
#include <QFontDialog>
#include <QColorDialog>
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
   QMenu *_penSubMenu, *_brushSubMenu, *_fontSubMenu, *_brushFillSubMenu;
   QMenu *_penLineSubMenu, *_penWidthSubMenu;
   QToolBar *_toolBar;
   QAction *_newAction,*_openAction, *_exitAction, *_saveAction, *_saveAsAction;
   QAction *_aboutAction, *_aboutQtAction;
   QAction *_freehandAct, *_lineAct, *_rectangleAct, *_ellipseAct, *_polygonAct, *_textAct;
   QAction *_penColorAct, *_penWidthAct;
   QAction *_penNoneAct,*_penSolidAct,*_penDashAct,*_penDotAct,*_penDashDotAct,*_penDashDotDotAct;
   QAction *_brushColorAct, *_brushFillAct;
   QAction *_brushLinearAct, *_brushRadialAct, *_brushConicalAct, *_brushTextureAct,*_brushSolidAct,
            *_brushHorAct, *_brushVerAct, *_brushCrossAct, *_brushBDAct, *_brushFDAct, *_brushDiagAct,
            *_brushDense1Act, *_brushDense2Act, *_brushDense3Act, *_brushDense4Act, *_brushDense5Act,
            *_brushDense6Act, *_brushDense7Act, *_brushNoneAct;
   QAction *_fontAct;
   QActionGroup *_toolsQag, *_penStylesQag, *_brushStylesQag;
   QSignalMapper *_signalMapper;
  private slots :
     void _newFile();
     void _saveFile();
     void _openFile();
     void _exit();
     void _about();
     void _aboutQt();
     void _penColor();
     void _penWidth();
     void _brushColor();
     void _brushFill();
     void _font();
  signals:
   void toolMapped(int digit);
};
#endif

