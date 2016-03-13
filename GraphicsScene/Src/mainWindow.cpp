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

 _brushColorAct = new QAction(tr("&Color"),  this);
 _brushFillAct = new QAction(tr("&Fill"),  this);
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

 _brushSubMenu->addAction(_brushColorAct);
 _brushSubMenu->addAction(_brushFillAct);
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

 connect(_brushColorAct, SIGNAL(triggered()), this, SLOT(_brushColor()));
 connect(_brushFillAct, SIGNAL(triggered()), this, SLOT(_brushFill()));

 connect(_fontAct, SIGNAL(triggered()), this, SLOT(_font()));

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
 int ret = QMessageBox::warning(this, tr("New File"),
                                tr("New File.\n"
                                   "Do you want to save your changes?"),
                                QMessageBox::Save | QMessageBox::Discard
                                | QMessageBox::Cancel,
                                QMessageBox::Save);
}

void MainWindow::_openFile(void) {
 qDebug() << "MainWindow::openFile(void)";
  QString filename =  QFileDialog::getOpenFileName(this,tr("Open Image"), tr("Image Files (*.png *.jpg *.bmp)"));
}

void MainWindow::_saveFile(void) {
 qDebug() << "MainWindow::saveFile(void)";
 QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"));
}

void MainWindow::_exit(void) {
qDebug()<< "MainWindow::_exit(void)" ;
QMessageBox msgBox;
msgBox.setText("You are about to quit the application");
msgBox.setInformativeText("Do you want to save your changes?");
msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
msgBox.setDefaultButton(QMessageBox::Save);
int ret = msgBox.exec();
}

void MainWindow::_about() {
 qDebug()<< "MainWindow::_aboutUs()" ;
 QMessageBox::information( this,
                           "Editeur graphique Version 0.1 Bêta \n",
                           "ENIB module CAI \nAnthony Guillier \nCopyright 2015/2016",
                           "Ok");
}

void MainWindow::_aboutQt() {
 qDebug()<< "MainWindow::_aboutQt()" ;
 QMessageBox::aboutQt( this, "A propos de Qt");
 
}

void MainWindow::_penColor() {
 qDebug()<< "MainWindow::_penColor()" ;
 QColor color = QColorDialog::getColor();
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
     penWidthSpin->show();
}

void MainWindow::_brushColor() {
 qDebug()<< "MainWindow::_brushColor()" ;
 QColor color = QColorDialog::getColor();
}

void MainWindow::_brushFill() {
 qDebug()<< "MainWindow::_brushFill()" ;
 QSpinBox* _brushFillSpin = new QSpinBox();
     _brushFillSpin->setWindowTitle("Brush Fill");
     _brushFillSpin->setFixedSize(150,50);

     QFont* font = new QFont();
     font->setBold(true);
     font->setPixelSize(25);

     _brushFillSpin->setFont(*font);
     _brushFillSpin->show();
}

void MainWindow::_font() {
 qDebug()<< "MainWindow::_font()" ;
 bool ok;
 QFont font = QFontDialog::getFont(
                 &ok, QFont("Helvetica [Cronyx]", 10), this);
 if (ok) {
     // the user clicked OK and font is set to the font the user selected
 } else {
     // the user canceled the dialog; font is set to the initial
     // value, in this case Helvetica [Cronyx], 10
 }
}


