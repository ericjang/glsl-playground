
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLShaderProgram>
#include <QGLWidget>
#include <QFileInfo>
#include <QTimer>
#include <QElapsedTimer>
#include <QDateTime>

class InfoPanel;

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void setShaderFile(QString filename);
    void pauseDrawing();
    void resumeDrawing();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();


    // enter event
    void leaveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    // resets the glwidget, recompiles the shader
    void reset();

private:
    InfoPanel *m_info;

    QTimer m_ticker;
    QElapsedTimer m_timer;

    // VBO for the fullscreen quad
    GLuint m_glVBO;
    bool hasBuffers();
    void buildBuffers();
    void deleteBuffers();
    void compileShader();


    bool m_draw;
    float m_fps;
    void updateCamera();

    QFileInfo m_shaderfile;

    QGLShaderProgram *m_shaderprogram;

    // inputs to frag shader
    float m_globalTime; // shader playback time, in seconds
    int m_mouseX, m_mouseY; // location of mouse in pixels, relative to the window
    int m_mouseClickL, m_mouseClickR; // whether mouse is clicked or not

    QDate m_date;


    friend class InfoPanel; // infopanel has permission to call renderText
};



#endif // GLWIDGET_H

