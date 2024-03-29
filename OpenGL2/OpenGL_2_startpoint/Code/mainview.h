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

  QOpenGLShaderProgram normalShaderProgram;
  GLint normalUniformModelViewTransform;
  GLint normalUniformProjectionTransform;
  GLint normalUniformNormalTransform;

  QOpenGLShaderProgram phongShaderProgram;
  GLint phongUniformModelViewTransform;
  GLint phongUniformProjectionTransform;
  GLint phongUniformNormalTransform;
  GLint phongUniformMaterial;
  GLint phongUniformLightPosition;
  GLint phongUniformLightColor;
  GLint phongUniformTexture;
  GLint phongUniformTextureSampler;

  QOpenGLShaderProgram gouraudShaderProgram;
  GLint gouraudUniformModelViewTransform;
  GLint gouraudUniformProjectionTransform;
  GLint gouraudUniformNormalTransform;
  GLint gouraudUniformMaterial;
  GLint gouraudUniformLightPosition;
  GLint gouraudUniformLightColor;
  GLint gouraudUniformTexture;
  GLint gouraudUniformTextureSampler;

  // Rendering Constants
  const QVector<float> material = {0.2f, 0.6f, 0.3f, 32}; // kA, kD, kS, n
  const QVector<float> lightPosition = {0, 200, 200};    // 3D Coordinates
  const QVector<float> lightColor = {1.0, 1.0, 1.0};     // RGB

  // Mesh values
  GLuint meshVAO;
  GLuint meshVBO;
  GLuint meshSize;
  GLuint texutrePtr;
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
  // The active shader program
  ShadingMode activeShader = ShadingMode::PHONG;

  void createShaderProgram();
  void loadMesh();
  void createTexture();

  void destroyModelBuffers();

  void updateProjectionTransform();
  void updateModelTransforms();
  void loadTexture(QString file, GLuint texturePtr);

  QVector<quint8> imageToBytes(QImage image);
};

#endif // MAINVIEW_H
