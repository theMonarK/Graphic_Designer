#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    _createActions();
    _createMenus();
    _createToolbars();
    _connectActions();

    QGraphicsView *view = new QGraphicsView();
    _area= new PaintArea (0, 0, 600, 800, this);
    view->setScene(_area);
    setCentralWidget(view);
    statusBar()->showMessage(tr("Ready"));

    _signalMapper = new QSignalMapper(this);
    _signalMapper->setMapping(_freehandAct, TOOLS_ID_FREEHAND);
    _signalMapper->setMapping(_lineAct, TOOLS_ID_LINE);
    _signalMapper->setMapping(_rectangleAct, TOOLS_ID_RECTANGLE);
    _signalMapper->setMapping(_ellipseAct, TOOLS_ID_CIRCLE);
    _signalMapper->setMapping(_polygonAct, TOOLS_ID_POLYGON);
    _signalMapper->setMapping(_textAct, TOOLS_ID_TEXT);

    _signalMapper->setMapping(_penSolidAct, STYLE_PEN_ID_SOLID);
    _signalMapper->setMapping(_penDashAct, STYLE_PEN_ID_DASH);
    _signalMapper->setMapping(_penDotAct, STYLE_PEN_ID_DOT);
    _signalMapper->setMapping(_penDashDotAct, STYLE_PEN_ID_DASHDOT);
    _signalMapper->setMapping(_penDashDotDotAct,  STYLE_PEN_ID_DASHDOTDOT);
    _signalMapper->setMapping(_penNoneAct, STYLE_PEN_ID_NONE);

    _signalMapper->setMapping(_penNoneAct, STYLE_BRUSH_ID_NONE);
    _signalMapper->setMapping(_brushSolidAct,  STYLE_BRUSH_ID_SOLID);
    _signalMapper->setMapping(_brushBDAct, STYLE_BRUSH_ID_BDIAGONAL);
    _signalMapper->setMapping(_brushFDAct, STYLE_BRUSH_ID_FDIAGONAL);
    _signalMapper->setMapping(_brushDense3Act, STYLE_BRUSH_ID_DENSE3);
    _signalMapper->setMapping(_brushDense4Act, STYLE_BRUSH_ID_DENSE4);
    _signalMapper->setMapping(_brushDense5Act, STYLE_BRUSH_ID_DENSE5);
    _signalMapper->setMapping(_brushDense6Act, STYLE_BRUSH_ID_DENSE6);


    _connectSignals();
}

void MainWindow::_createMenus(void) {
 QMenuBar* menubar = menuBar();         // QMainWindow method
 _fileMenu = menubar->addMenu( tr("&File") );
 _toolMenu = menubar->addMenu("&Tool");
 _styleMenu = menubar->addMenu("&Style");
 _penSubMenu = _styleMenu->addMenu("&Pen");
 _penLineSubMenu = _penSubMenu->addMenu("&Line");
 _brushSubMenu = _styleMenu->addMenu("&Brush");
 _brushFillSubMenu=  _brushSubMenu->addMenu("&Fill");
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
 
 _openAction = new QAction(QIcon(":/Images/open.png"), tr("&Open..."), this);
 _openAction->setShortcut( tr("Ctrl+O") );
 _openAction->setToolTip( tr("Open file") );
 _openAction->setStatusTip( tr("Open file") );
 
 _saveAction = new QAction(QIcon(":/Images/save.png"), tr("&Save..."), this);
 _saveAction->setShortcut( tr("Ctrl+S") );
 _saveAction->setToolTip( tr("Save file") );
 _saveAction->setStatusTip( tr("Save file") );
 
 _saveAsAction = new QAction(tr("&Save as..."), this); 
 _saveAsAction->setToolTip( tr("Save file as...") );
 _saveAsAction->setStatusTip( tr("Save file as ...") );

 _exitAction = new QAction(tr("&Exit"), this);
 _exitAction->setShortcut( tr("Ctrl+Q") );
 _exitAction->setToolTip( tr("Exit application") );
 _exitAction->setStatusTip( tr("Exit application") );

 _aboutAction = new QAction(tr("&About"), this);
 _aboutAction->setShortcut(tr("Ctrl+H"));
 _aboutAction->setStatusTip(tr("Khaaaaaa"));
 _aboutQtAction = new QAction(tr("&About Qt"), this);
 _aboutQtAction->setStatusTip(tr("So Qt !"));

 _penColorAct = new QAction(tr("&Color"),  this);
 _penWidthAct = new QAction(tr("&Width"),  this);
 _penStylesQag = new QActionGroup( this );
 _penNoneAct = new QAction(tr("&None"),  this);
 _penSolidAct = new QAction(tr("&Solid"),  this);
 _penDashAct = new QAction(tr("&Dash"),  this);
 _penDotAct = new QAction(tr("&Dot"),  this);
 _penDashDotAct = new QAction(tr("&Dash Dot"),  this);
 _penDashDotDotAct = new QAction(tr("&Dash Dot Dot"),  this);

 _penNoneAct->setCheckable(true);
 _penNoneAct->setChecked(true);
 _penSolidAct->setCheckable(true);
 _penDashAct->setCheckable(true);
 _penDotAct->setCheckable(true);
 _penDashDotAct->setCheckable(true);
 _penDashDotDotAct->setChecked(true);

 _brushColorAct = new QAction(tr("&Color"),  this);
 _brushFillAct = new QAction(tr("&Fill"),  this);
 _brushStylesQag = new QActionGroup( this );
 _brushNoneAct = new QAction(tr("&None"),  this);
 _brushSolidAct = new QAction(tr("&Solid"),  this);
 _brushBDAct = new QAction(tr("&B Diagonal"),  this);
 _brushFDAct = new QAction(tr("&F Diagonal"),  this);
 _brushDense3Act = new QAction(tr("&Dense 3"),  this);
 _brushDense4Act = new QAction(tr("&Dense 4"),  this);
 _brushDense5Act = new QAction(tr("&Dense 5"),  this);
 _brushDense6Act = new QAction(tr("&Dense 6"),  this);

 _brushNoneAct->setCheckable(true);
 _brushNoneAct->setChecked(true);
 _brushSolidAct->setCheckable(true);
 _brushBDAct->setCheckable(true);
 _brushFDAct->setCheckable(true);
 _brushDense3Act->setCheckable(true);
 _brushDense4Act->setChecked(true);
 _brushDense5Act->setCheckable(true);
 _brushDense6Act->setCheckable(true);

 _fontAct = new QAction(tr("&Font"),  this);

 _toolsQag = new QActionGroup( this );
 _freehandAct = new QAction(tr("&Freehand"),  this);
 _lineAct = new QAction(tr("&Line"), this);
 _rectangleAct = new QAction(tr("&Rectangle"), this);
 _ellipseAct = new QAction(tr("&Ellipse"), this);
 _polygonAct = new QAction(tr("&Polygon"), this);
 _textAct = new QAction(tr("&Text"), this);

 _freehandAct->setCheckable(true);
 _freehandAct->setChecked(true);
 _lineAct->setCheckable(true);
 _rectangleAct->setCheckable(true);
 _ellipseAct->setCheckable(true);
 _polygonAct->setCheckable(true);
 _textAct->setCheckable(true);
 _penNoneAct->setChecked(true);
}

void MainWindow::_connectActions(void) {
 _fileMenu->addAction(_newAction);
 _fileMenu->addSeparator();
 _fileMenu->addAction(_openAction);
 _fileMenu->addAction(_saveAction);
 _fileMenu->addAction(_saveAsAction);
 _fileMenu->addSeparator();
 _fileMenu->addAction(_exitAction);

 _helpMenu->addAction(_aboutAction);
 _helpMenu->addAction(_aboutQtAction);

 _toolBar->addAction(_newAction);
 _toolBar->addAction(_openAction);
 _toolBar->addAction(_saveAction);

 _toolsQag->addAction(_freehandAct);
 _toolsQag->addAction(_lineAct);
 _toolsQag->addAction(_rectangleAct);
 _toolsQag->addAction(_ellipseAct);
 _toolsQag->addAction(_polygonAct);
 _toolsQag->addAction(_textAct);

 _toolMenu->addAction(_freehandAct);
 _toolMenu->addAction(_lineAct);
 _toolMenu->addAction(_rectangleAct);
 _toolMenu->addAction(_ellipseAct);
 _toolMenu->addAction(_polygonAct);
 _toolMenu->addSeparator();
 _toolMenu->addAction(_textAct);

 _styleMenu->addAction(_fontAct);

 _penSubMenu->addAction(_penColorAct);
 _penSubMenu->addAction(_penWidthAct);
 _penStylesQag->addAction(_penNoneAct);
 _penStylesQag->addAction(_penSolidAct);
 _penStylesQag->addAction(_penDashAct);
 _penStylesQag->addAction(_penDotAct);
 _penStylesQag->addAction(_penDashDotAct);
 _penStylesQag->addAction(_penDashDotDotAct);

 _penLineSubMenu->addAction(_penNoneAct);
 _penLineSubMenu->addAction(_penSolidAct);
 _penLineSubMenu->addAction(_penDashAct);
 _penLineSubMenu->addAction(_penDotAct);
 _penLineSubMenu->addAction(_penDashDotAct);
 _penLineSubMenu->addAction(_penDashDotDotAct);


 _brushSubMenu->addAction(_brushColorAct);
 _brushStylesQag->addAction(_brushNoneAct);
 _brushStylesQag->addAction(_brushSolidAct);
 _brushStylesQag->addAction(_brushBDAct);
 _brushStylesQag->addAction(_brushFDAct);
 _brushStylesQag->addAction(_brushDense3Act);
 _brushStylesQag->addAction(_brushDense4Act);
 _brushStylesQag->addAction(_brushDense5Act);
 _brushStylesQag->addAction(_brushDense6Act);

 _brushFillSubMenu->addAction(_brushNoneAct);
 _brushFillSubMenu->addAction(_brushSolidAct);
 _brushFillSubMenu->addAction(_brushBDAct);
 _brushFillSubMenu->addAction(_brushFDAct);
 _brushFillSubMenu->addAction(_brushDense3Act);
 _brushFillSubMenu->addAction(_brushDense4Act);
 _brushFillSubMenu->addAction(_brushDense5Act);
 _brushFillSubMenu->addAction(_brushDense6Act);
}

void MainWindow::_connectSignals(void) {
 connect( _newAction, SIGNAL(triggered( )), this, SLOT(_newFile( )));
 connect( _openAction, SIGNAL(triggered( )), this, SLOT(_openFile( )));
 connect( _saveAction, SIGNAL(triggered( )), this, SLOT(_saveFile( )));
 connect( _exitAction, SIGNAL(triggered( )), this, SLOT(_exit( )));
 connect(_aboutAction, SIGNAL(triggered()), this, SLOT(_about()));
 connect(_aboutQtAction, SIGNAL(triggered()), this, SLOT(_aboutQt()));

 connect(_penColorAct, SIGNAL(triggered()), this, SLOT(_penColor()));
 connect(_penWidthAct, SIGNAL(triggered()), this, SLOT(_penWidth()));
 connect(_penNoneAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_penSolidAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_penDashAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_penDotAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_penDashDotAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_penDashDotDotAct,SIGNAL(activated()),_signalMapper, SLOT(map()));

 connect(_brushColorAct, SIGNAL(triggered()), this, SLOT(_brushColor()));
 connect(_brushNoneAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_brushSolidAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_brushBDAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_brushFDAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_brushDense3Act,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_brushDense4Act,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_brushDense5Act,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_brushDense6Act,SIGNAL(activated()),_signalMapper, SLOT(map()));

 connect(_fontAct, SIGNAL(triggered()), this, SLOT(_font()));

 connect(_freehandAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_lineAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_rectangleAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_ellipseAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_polygonAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_textAct,SIGNAL(activated()),_signalMapper, SLOT(map()));

 connect(_signalMapper,SIGNAL(mapped(int)), this, SIGNAL(toolMapped(int)));
 connect(this, SIGNAL(toolMapped(int)), _area, SLOT(setCurrentTool(int)) );
}

void MainWindow::_newFile(void) {
 qDebug() << "MainWindow::newFile(void)";
 qDebug() << "Date : " << QDate::currentDate();
 QString str = _newAction->data().toString();
 qDebug() << str ;
 statusBar()->showMessage(str);
 int ret = QMessageBox::warning(this, tr("New File"),
                                tr("New File.\n\n"
                                   "You are opening a new file. \n Save your current work?"),
                                QMessageBox::Save | QMessageBox::Discard
                                | QMessageBox::Cancel,
                                QMessageBox::Save);
 switch (ret) {
   case QMessageBox::Save:{
       _saveFile();
       break;
     }
   case QMessageBox::Discard:{
       _area->clear();
       break;
    }
   case QMessageBox::Cancel:{
       break;
    }
 }
}

void MainWindow::_openFile(void) {
 qDebug() << "MainWindow::openFile(void)";
  QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
  if (fileName!=NULL){

  }
}

void MainWindow::_saveFile(void) {
 qDebug() << "MainWindow::saveFile(void)";
 QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),".png",  tr("Image Files (*.png *.jpg *.bmp)"));
 if(fileName!=NULL){

 }
}

void MainWindow::_exit(void) {
qDebug()<< "MainWindow::_exit(void)" ;
int ret = QMessageBox::warning(this, tr("Quit"),
                               tr("Quit.\n\n"
                                  "You are about to quit the application. \n Save your current work?"),
                               QMessageBox::Save | QMessageBox::Discard
                               | QMessageBox::Cancel,
                               QMessageBox::Save);
switch (ret) {
  case QMessageBox::Save:{
      _saveFile();
      break;
    }
  case QMessageBox::Discard:{
      qDebug()<< "Close()";
      close();
      break;
   }
  case QMessageBox::Cancel:{
      break;
   }
}
}

void MainWindow::_about() {
 qDebug()<< "MainWindow::_aboutUs()" ;
 QMessageBox::information( this,
                           "Editeur graphique Version 0.1 Bêta \n\n",
                           "ENIB module CAI \nAnthony Guillier \nCopyright 2015/2016",
                           "Ok");
}

void MainWindow::_aboutQt() {
 qDebug()<< "MainWindow::_aboutQt()" ;
 QMessageBox::aboutQt( this, "A propos de Qt");
 
}

void MainWindow::_penColor() {
 qDebug()<< "MainWindow::_penColor()" ;
 QColor color = QColorDialog::getColor(_area->getCurrentPen().color());
 if(color.isValid()){
 _area->setCurrentPenColor(color);
 }
}

void MainWindow::_penWidth() {
 qDebug()<< "MainWindow::_penWidth()" ;
 QSpinBox* penWidthSpin = new QSpinBox();
     penWidthSpin->setWindowTitle("Pen Width");
     penWidthSpin->setFixedSize(150,50);

     QFont* font = new QFont();
     font->setBold(true);
     font->setPixelSize(25);

     penWidthSpin->setFont(*font);
     penWidthSpin->setValue(_area->getCurrentPen().width());
     penWidthSpin->show();
     connect(penWidthSpin,SIGNAL(valueChanged(int)),_area,SLOT(setCurrentPenWidth(int)));
}

void MainWindow::_brushColor() {
 qDebug()<< "MainWindow::_brushColor()" ;
 QColor color = QColorDialog::getColor(_area->getCurrentBrush().color());
 if(color.isValid()){
     _area->setCurrentBrushColor(color);
     qDebug()<<_area->getCurrentBrush().color();
 }
}

void MainWindow::_font() {
 qDebug()<< "MainWindow::_font()" ;
 bool ok;
 QFont font = QFontDialog::getFont(
                 &ok, _area->getCurrentFont(), this);

 if (ok) {
     _area->setCurrentFont(font);
 }
}


