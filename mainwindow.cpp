#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QShortcut *shortcut_reload = new QShortcut(QKeySequence(tr("Ctrl+R","File|Reload")), this);
    shortcut_reload->setContext(Qt::ApplicationShortcut);
    connect(shortcut_reload, SIGNAL(activated()), ui->myGLWidget, SLOT(reset()));
    connect(ui->actionReload_Shader, SIGNAL(triggered()), ui->myGLWidget, SLOT(reset()));
    // open
    QShortcut *shortcut_open = new QShortcut(QKeySequence(tr("Ctrl+O","File|Open")), this);
    shortcut_open->setContext(Qt::ApplicationShortcut);
    connect(shortcut_open, SIGNAL(activated()), this, SLOT(openFile()));
    connect(ui->actionOpen_Shader, SIGNAL(triggered()), this, SLOT(openFile()));
}

void MainWindow::openFile() {
    // opens a dialog for the user to select a shader
    ui->myGLWidget->pauseDrawing();
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open Fragment Shader"), QDir::homePath(),tr("All Files (*)"));
    setFile(fileName);
    ui->myGLWidget->resumeDrawing();
}

void MainWindow::setFile(QString filename) {
    ui->myGLWidget->setShaderFile(filename);
}


MainWindow::~MainWindow()
{
    delete ui;
}
