#ifndef MyGL_H
#define MyGL_H


#include <QtWidgets>
#include <QtOpenGL>
#include <glfw3.h>
//#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <QOpenGLWidget>

class MyGL : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit MyGL(QWidget *parent = 0);

    void setRotation(float x, float y, float z);
    void setTranslation(float x, float y, float z);
    void effectY(float y);
    void effectX(float x);
    void effectZero();
    void rotEffectY(float y);
    void rotEffectX(float x);
    void Jump(float y);
    void Crouch(float y);
    void MoveAlongX(float x);
    void sinkDown();
    bool checkGround();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

signals:

public slots:

private:

public:
    float xrot,yrot,zrot;
    float xtran, ytran, ztran;
    float xkey, ykey;
    float xkeyR, ykeyR;

};

#endif // QGLBEGIN_H
