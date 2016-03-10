#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
 _createActions();
 _createMenus();
 _createToolbars();
 _connectActions();

  QGraphicsView *view = new QGraphicsView();
  _area= new PaintArea (0, 0, 600, 800, this);
  QGraphicsTextItem * text= _area->addText("Shake that... !");
  text->setPos(100,100);
  text->setVisible(true);
  view->setScene(_area);
  setCentralWidget(view);
  statusBar()->showMessage(tr("Ready"));

  _signalMapper = new QSignalMapper(this);
  _signalMapper->setMapping(_freehandAct, TOOLS_ID_FREEHAND);
  _signalMapper->setMapping(_lineAct, TOOLS_ID_LINE);
  _signalMapper->setMapping(_rectangleAct, TOOLS_ID_RECTANGLE);
  _signalMapper->setMapping(_ellipseAct, TOOLS_ID_CIRCLE);
  _signalMapper->setMapping(_polygonAct, TOOLS_ID_POLYGON);

  _connectSignals();
}

void MainWindow::_createMenus(void) {
 QMenuBar* menubar = menuBar();         // QMainWindow method
 _fileMenu = menubar->addMenu( tr("&File") );
 _toolMenu = menubar->addMenu("&Tool");
 _styleMenu = menubar->addMenu("&Style");
 _penSubMenu = _styleMenu->addMenu("&Pen");
 _penLineSubMenu = _penSubMenu->addMenu("&Line");
 _penWidthSubMenu = _penSubMenu->addMenu("&Width");
 _brushSubMenu = _styleMenu->addMenu("&Brush");
 _fontSubMenu = _styleMenu->addMenu("&Font");
 _helpMenu = menubar->addMenu( tr("&Help") );
}

void MainWindow::_createToolbars(void) {
  _toolBar = addToolBar( tr("File") );
}

void MainWindow::_createActions(void) {
 _newAction = new QAction( QIcon(":/Images/new.png"), tr("&New..."), this );
 _newAction->setShortcut( tr("Ctrl+N") );
 _newAction->setToolTip( tr("New file") );
 _newAction->setStatusTip( tr("New file") );
 _newAction->setData(QVariant("new Action data to process"));
 
 _openAction = new QAction(tr("&Open"), this); 
 _openAction->setToolTip( tr("Open file") );
 _openAction->setStatusTip( tr("Open file") );
 
 _saveAction = new QAction(tr("&Save"), this); 
 _saveAction->setToolTip( tr("Save file") );
 _saveAction->setStatusTip( tr("Save file") );
 
 _saveAsAction = new QAction(tr("&Save as..."), this); 
 _saveAsAction->setToolTip( tr("Save file as...") );
 _saveAsAction->setStatusTip( tr("Save file as ...") );

 _aboutAction = new QAction(tr("&About"), this);
 _aboutAction->setShortcut(tr("Ctrl+H"));
 _aboutAction->setStatusTip(tr("Khaaaaaa"));
 _aboutQtAction = new QAction(tr("&About Qt"), this);
 _aboutQtAction->setStatusTip(tr("So Qt !"));

 _toolsQag = new QActionGroup( this );
 _freehandAct = new QAction(tr("&Freehand"),  this);
 _lineAct = new QAction(tr("&Line"), this);
 _rectangleAct = new QAction(tr("&Rectangle"), this);
 _ellipseAct = new QAction(tr("&Ellipse"), this);
 _polygonAct = new QAction(tr("&Polygon"), this);

 _freehandAct->setCheckable(true);
 _lineAct->setCheckable(true);
 _rectangleAct->setCheckable(true);
 _ellipseAct->setCheckable(true);
 _polygonAct->setCheckable(true);
}

void MainWindow::_connectActions(void) {
 _fileMenu->addAction(_newAction);
 _fileMenu->addAction(_openAction);
 _fileMenu->addAction(_saveAction);
 _fileMenu->addAction(_saveAsAction);
 _helpMenu->addAction(_aboutAction);
 _helpMenu->addAction(_aboutQtAction);
 _toolBar->addAction(_newAction);

 _toolsQag->addAction(_freehandAct);
 _toolsQag->addAction(_lineAct);
 _toolsQag->addAction(_rectangleAct);
 _toolsQag->addAction(_ellipseAct);
 _toolsQag->addAction(_polygonAct);

 _toolMenu->addAction(_freehandAct);
 _toolMenu->addAction(_lineAct);
 _toolMenu->addAction(_rectangleAct);
 _toolMenu->addAction(_ellipseAct);
 _toolMenu->addAction(_polygonAct);
}

void MainWindow::_connectSignals(void) {
 connect( _newAction, SIGNAL(triggered( )), this, SLOT(_newFile( )) );
 connect(_aboutAction, SIGNAL(triggered()), this, SLOT(_about()));
 connect(_aboutQtAction, SIGNAL(triggered()), this, SLOT(_aboutQt()));

 connect(_freehandAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_lineAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_rectangleAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_ellipseAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_polygonAct,SIGNAL(activated()),_signalMapper, SLOT(map()));

 connect(_signalMapper,SIGNAL(mapped(int)), this, SIGNAL(toolMapped(int)));
 connect(this, SIGNAL(toolMapped(int)), _area, SLOT(setCurrentTool(int)) );
}

void MainWindow::_newFile(void) {
 qDebug() << "MainWindow::newFile(void)";
 qDebug() << "Date : " << QDate::currentDate();
 QString str = _newAction->data().toString();
 qDebug() << str ;
 statusBar()->showMessage(str);
}

void MainWindow::_exit(void) {
qDebug()<< "MainWindow::_exit(void)" ;
}

void MainWindow::_about() {
 qDebug()<< "MainWindow::_aboutUs()" ;
 QMessageBox::information( this,
                           "Editeur graphique Version 0.1 Bêta",
                           "ENIB module CAI \nAnthony Guillier \nCopyright 2015/2016",
                           "Ok");
}

void MainWindow::_aboutQt() {
 qDebug()<< "MainWindow::_aboutQt()" ;
 QMessageBox::aboutQt( this, "A propos de Qt");
 
}

