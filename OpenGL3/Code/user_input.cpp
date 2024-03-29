#include "mainview.h"

#include <QDebug>

// Triggered by pressing a key
void MainView::keyPressEvent(QKeyEvent *ev) {
  switch (ev->key()) {
  case 'A':
    qDebug() << "A pressed";
    movementFactor.setX(-0.1f);
    break;
  case 'D':
    qDebug() << "D pressed";
    movementFactor.setX(0.1f);
    break;
  case 'W':
    qDebug() << "W pressed";
    movementFactor.setZ(0.1f);
    break;
  case 'S':
    qDebug() << "S pressed";
    movementFactor.setZ(-0.1f);
    break;
  default:
    // ev->key() is an integer. For alpha numeric characters keys it equivalent
    // with the char value ('A' == 65, '1' == 49) Alternatively, you could use
    // Qt Key enums, see http://doc.qt.io/qt-5/qt.html#Key-enum
    qDebug() << ev->key() << "pressed";
    break;
  }

  // Used to update the screen after changes
  update();
}

// Triggered by releasing a key
void MainView::keyReleaseEvent(QKeyEvent *ev) {
  switch (ev->key()) {
  case 'A':
    qDebug() << "A released";
    movementFactor.setX(0.0f);
    break;
  case 'D':
    qDebug() << "D released";
    movementFactor.setX(0.0f);
    break;
  case 'W':
    qDebug() << "W released";
    movementFactor.setZ(0.0f);
    break;
  case 'S':
    qDebug() << "W released";
    movementFactor.setZ(0.0f);
    break;
  default:
    qDebug() << ev->key() << "released";
    break;
  }

  update();
}

// Triggered by clicking two subsequent times on any mouse button
// It also fires two mousePress and mouseRelease events!
void MainView::mouseDoubleClickEvent(QMouseEvent *ev) {
  qDebug() << "Mouse double clicked:" << ev->button();

  update();
}

// Triggered when moving the mouse inside the window (only when the mouse is
// clicked!)
void MainView::mouseMoveEvent(QMouseEvent *ev) {
  qDebug() << "x" << ev->x() << "y" << ev->y();

  if (ev->x() > mouseX){
      cameraFactor.setY(cameraFactor.y() - 0.5f);
      mouseX = ev->x();
  } else {
      cameraFactor.setY(cameraFactor.y() + 0.5f);
      mouseX = ev->x();
  }

  if (ev->y() > mouseY){
      cameraFactor.setX(cameraFactor.x() - 0.5f);
      mouseY = ev->y();
  } else {
      cameraFactor.setX(cameraFactor.x() + 0.5f);
      mouseY = ev->y();
  }
  update();
}

// Triggered when pressing any mouse button
void MainView::mousePressEvent(QMouseEvent *ev) {
  qDebug() << "Mouse button pressed:" << ev->button();

  update();
  // Do not remove the line below, clicking must focus on this widget!
  this->setFocus();
}

// Triggered when releasing any mouse button
void MainView::mouseReleaseEvent(QMouseEvent *ev) {
  qDebug() << "Mouse button released" << ev->button();

  update();
}

// Triggered when clicking scrolling with the scroll wheel on the mouse
void MainView::wheelEvent(QWheelEvent *ev) {
  // Implement something
  qDebug() << "Mouse wheel:" << ev->delta();

  update();
}
