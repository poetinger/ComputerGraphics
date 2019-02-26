#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "model.h"

#include <QKeyEvent>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QTimer>
#include <QVector3D>
#include <memory>

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
  Q_OBJECT

  QOpenGLDebugLogger *debugLogger;
  QTimer timer; // timer used for animation

  QOpenGLShaderProgram shaderProgram;
  GLint uniformModelViewTransform;
  GLint uniformProjectionTransform;
  GLint uniformNormalTransform;

  // Mesh values
  GLuint meshVAO;
  GLuint meshVBO;
  GLuint meshSize;
  QMatrix4x4 meshTransform;

  // Transforms
  float scale = 1.f;
  QVector3D rotation;
  QMatrix4x4 projectionTransform;
  QMatrix3x3 normalTransform;

public:
  enum ShadingMode : GLuint { PHONG = 0, NORMAL, GOURAUD };

  MainView(QWidget *parent = 0);
  ~MainView();

  // Functions for widget input events
  void setRotation(int rotateX, int rotateY, int rotateZ);
  void setScale(int scale);
  void setShadingMode(ShadingMode shading);

protected:
  void initializeGL();
  void resizeGL(int newWidth, int newHeight);
  void paintGL();

  // Functions for keyboard input events
  void keyPressEvent(QKeyEvent *ev);
  void keyReleaseEvent(QKeyEvent *ev);

  // Function for mouse input events
  void mouseDoubleClickEvent(QMouseEvent *ev);
  void mouseMoveEvent(QMouseEvent *ev);
  void mousePressEvent(QMouseEvent *ev);
  void mouseReleaseEvent(QMouseEvent *ev);
  void wheelEvent(QWheelEvent *ev);

private slots:
  void onMessageLogged(QOpenGLDebugMessage Message);

private:
  void createShaderProgram();
  void loadMesh();

  void destroyModelBuffers();

  void updateProjectionTransform();
  void updateModelTransforms();
};

#endif // MAINVIEW_H