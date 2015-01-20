#include "glwidget.h"
#include "infopanel.h"
#include <algorithm>
#include <GL/gl.h>
#include "GL/glext.h"
#include <QMouseEvent>

static const int MAX_FPS = 120;
#define STR( QSTR ) QSTR.toStdString().c_str()

#define SAFE_DELETE(MEM)                \
    {                                   \
        if ((MEM)) {                    \
            delete ((MEM));             \
            (MEM) = NULL;               \
        }                               \
    }


GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{// called once
    m_info = new InfoPanel(this);
    m_info->setInfo("FPS","XXXXX");
    setFocusPolicy(Qt::StrongFocus);
    connect(&m_ticker, SIGNAL(timeout()), this, SLOT(update()));
    m_shaderprogram = NULL;
}

void GLWidget::reset() {

    if ( !hasBuffers() ) buildBuffers(); // build the fullscreen quad

    if (m_shaderprogram != NULL) {
        // un-do the previous one
        delete m_shaderprogram;
    }

    m_timer.restart();

    m_globalTime = 0;
    m_mouseX = 0;
    m_mouseY = 0;
    m_mouseClickL=0;
    m_mouseClickR = 0;
    m_draw = true;
    m_fps = MAX_FPS;

    m_date = QDate::currentDate();

    compileShader();
}

void GLWidget::compileShader() {
    const QGLContext *context = QGLContext::currentContext();
    m_shaderprogram = new QGLShaderProgram(context);

    if (m_shaderprogram->addShaderFromSourceFile(QGLShader::Fragment, m_shaderfile.absoluteFilePath())) {
        if (!m_shaderprogram->link()) {
            qDebug() << "Link Error: " << m_shaderprogram->log().trimmed();
            SAFE_DELETE(m_shaderprogram);
        }
        qDebug() << "Shader " << m_shaderfile.absoluteFilePath() << " compiled.";
    } else {
        qDebug() << "Compile Error:" << m_shaderprogram->log().trimmed();
        SAFE_DELETE(m_shaderprogram);
    }
}




void GLWidget::setShaderFile(QString filename) {
    m_shaderfile = QFileInfo(filename);
    reset();
}

void GLWidget::updateCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // (-1,-1) = bottom left handed corner, (1,1) top right hand corner
    // near and far clipping = 0, 1 respectively
    glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 1.0);
}

GLWidget::~GLWidget()
{
    delete m_info;
}

void GLWidget::initializeGL() {
    QGLWidget::initializeGL();
    qDebug("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
    updateCamera();

    m_ticker.start( 1000/MAX_FPS );
    m_timer.start();

//    glDisable(GL_DEPTH_TEST);
//    glDepthFunc( GL_LESS );

    glEnable( GL_LINE_SMOOTH );
    glEnableClientState( GL_VERTEX_ARRAY );

    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );

    glClearColor(0.0f, 0.0f, 0.0f, 1.f);

    reset();
}

void GLWidget::paintGL() {
    // draw grey background
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if (m_shaderprogram != NULL) {

        m_shaderprogram->bind();
        m_shaderprogram->setUniformValue("iResolution", width(), height(), 1.f); // viewport resolution (in pixels)
        m_shaderprogram->setUniformValue("iGlobalTime", m_globalTime); // shader playback time (in seconds)
        m_shaderprogram->setUniformValue("iMouse", m_mouseX, m_mouseY, m_mouseClickL, m_mouseClickR); // mouse pixel coords. xy: current pixel coords. zw = click pixel
        QTime time = QTime::currentTime();
        m_shaderprogram->setUniformValue("iDate",
                                         m_date.year(),
                                         m_date.month(),
                                         m_date.day(),
                                         QTime(0,0).secsTo(time) );
        // (year, month, day, time in seconds)
    }
    // draw a quad

    glMatrixMode(GL_MODELVIEW);
    glColor3f(0.3, 0.3, 0.9);

    glBindBuffer( GL_ARRAY_BUFFER, m_glVBO );
    glVertexPointer( 2, GL_FLOAT, 2*sizeof(float), (void*)(0) );
    GLubyte indices[] = {0,1,2, // first triangle (bottom left - top left - top right)
                         0,2,3}; // second triangle (bottom left - top right - bottom right
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

    if (m_shaderprogram != NULL) {
        m_shaderprogram->release();
    }

    if (m_draw) {
        float elapsed = m_timer.restart();
        m_globalTime += elapsed/1000.f;

#if 0 // this doesn't seem to work at the moment - for some reason doesn't draw in front.
        m_fps = 1000.f/std::max(elapsed,1.f);
        m_info->setInfo( "FPS", QString::number(m_fps, 'f', 2), false );
        m_info->render();
#endif
    }


 }


bool GLWidget::hasBuffers() {
    return m_glVBO > 0 && glIsBuffer( m_glVBO );
}

void GLWidget::buildBuffers() {
    // builds the VBO needed to draw the fullscreen quad

    deleteBuffers();
    float data[8] = {
        -1.0f, -1.0f, // bottom left
        -1.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, -1.0f
    };
    glGenBuffers( 1, &m_glVBO ); // bind
    glBindBuffer( GL_ARRAY_BUFFER, m_glVBO );
    glBufferData( GL_ARRAY_BUFFER, 8*sizeof(float),
                  data, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 ); // unbind
}

void GLWidget::deleteBuffers() {
    if (hasBuffers()) {
        glDeleteBuffers(1, &m_glVBO);
    }
    m_glVBO=0;
}

void GLWidget::resizeGL(int width, int height) {
    // Set the viewport to fill the screen
    glViewport(0, 0, width, height);
    // Update the camera
    updateCamera();
}

void GLWidget::pauseDrawing()
{
    m_ticker.stop();
    m_draw = false;
}

void GLWidget::resumeDrawing()
{
    m_ticker.start( 1000/MAX_FPS );
    m_draw = true;
}



void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    m_mouseX = event->x();
    m_mouseY = event->y();
}

void GLWidget::leaveEvent(QMouseEvent *event) {
    m_mouseX = 0;
    m_mouseY = 0;
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        m_mouseClickL = 1.0f;
    if (event->button() == Qt::RightButton)
        m_mouseClickR = 1.0f;
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        m_mouseClickL = 0.0f;
    if (event->button() == Qt::RightButton)
        m_mouseClickR = 0.0f;
}


