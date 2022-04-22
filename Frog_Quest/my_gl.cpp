#include "my_gl.h"
#include <QOpenGLWidget>
#include <QPixmap>

MyGL::MyGL(QWidget *parent) : QOpenGLWidget(parent)
{
    xrot = yrot = zrot = 0.0;
    xtran = ytran = ztran = 0.0;
    xkey = ykey = 0.0;
    xkeyR = ykeyR = 0.0;
}

void MyGL::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
}

void MyGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    glTranslatef(xtran, ytran, (ztran -5.0));
    glRotatef(xrot, 1.5, 0.0, 0.0);
    glRotatef(yrot, 0.0, 1.0, 0.0);
    glRotatef(zrot, 0.0, 0.0, 1.0);

    glTranslatef(0,0,0);

    glBegin(GL_POLYGON);
         glColor3f(0.0f, 0.0f, 1.0f);
         //loadTexture("link");
         glVertex3f(-0.5f, -0.5f, 0.0f);
         glVertex3f(-0.5f, 0.5f, 0.0f);
         glVertex3f(0.5f, 0.5f, 0.0f);
         glVertex3f(0.5f, -0.5f, 0.0f);
    glEnd();



    glFlush();

}

void MyGL::resizeGL(int w, int h)
{
    //set viewport
    glViewport(0,0,w,h);

    //initialize projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* multiply the current matrix by a perspective matrix
     * void glFrustum(GLdouble left, GLdouble right,GLdouble bottom,GLdouble top,GLdouble nearVal,GLdouble farVal);
     * left, right: Specify the coordinates for the left and right vertical clipping planes.
     * bottom, top: Specify the coordinates for the bottom and top horizontal clipping planes.
     * nearVal, farVal: Specify the distances to the near and far depth clipping planes. Both distances must be positive.
     */
    glFrustum(-2, +2, -2, +2, 4.0, 10.0);

    //initialize modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void MyGL::setRotation(float x, float y, float z)
{
    xrot = x;
    yrot = y;
    zrot = z;
    update();
}

void MyGL::effectY(float y){
    ykey = y;
    xkey = 0.0f;
    //ytran = ytran + y;
    //update();
    setTranslation(xtran, ytran, ztran);
}

void MyGL::effectX(float x){
    xkey = x;
    ykey = 0.0f;
    //xtran = xtran + x;
    //update();
    setTranslation(xtran, ytran, ztran);
}

void MyGL::rotEffectY(float y){
    ykeyR = y;
    //xkey = 0.0f;
    //ytran = ytran + y;
    //update();
    setRotation(xrot, yrot + ykeyR, zrot);
}

void MyGL::rotEffectX(float x){
    xkeyR = x;
    //ykey = 0.0f;
    //xtran = xtran + x;
    //update();
    setRotation(xrot + xkeyR, yrot, zrot);
}

void MyGL::MoveAlongX(float x){
    xtran = xtran + x;
    update();
}

void MyGL::Crouch(float y){
    ytran = ytran + y;
    update();
}

void MyGL::Jump(float y){
    ytran = ytran + y;
    update();
}

void MyGL::effectZero(){
    xkey = 0.0f;
    ykey = 0.0f;
}

void MyGL::sinkDown(){
    ytran = ytran - .05f;
    update();
}

bool MyGL::checkGround(){
    if(xtran > 0){
        return true;
    }
    return false;
}

void MyGL::setTranslation(float x, float y, float z)
{
    xtran = x + xkey;
    ytran = y + ykey;
    ztran = z;
    update();
}

