// MyGLWidget.h
#include "BL2GLWidget.h"

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    void initializeGL( )  override;
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    void paintGL( ) override;
    void carregaShaders() override;
    void projectTransform();
    void viewTransform();
  private:
    GLuint projLoc;
    GLuint viewLoc;
};
