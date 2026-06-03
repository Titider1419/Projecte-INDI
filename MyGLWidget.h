// MyGLWidget.h
#include "BL2GLWidget.h"
#include "/home/andres/UNI/Q4/INDI/labs/projecte/Model/model.h"
#include <QKeyEvent>

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    GLuint vertexLoc, normalLoc, matambLoc, matdiffLoc, matspecLoc, matshinLoc;

    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    void initializeGL( )  override;
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    void paintGL( ) override;
    void carregaShaders() override;
    void projectTransform();
    void viewTransform();
    void resizeGL(int w, int h);
    GLuint VAO_Cub;
    void creaBuffersCub ();
    void modelTransformMorty(int fil, int col);
    void modelTransformFantasma(int fil, int col);
    void modelTransformMoneda(int fil, int col);
    void modelTransformTorre(int fil, int col);
    glm::vec3 puntMinMorty();
    glm::vec3 puntMinFantasma();
    glm::vec3 puntMinMoneda();
    glm::vec3 puntMinTorre();
    void dibujarPared(int col, int fila);
    void dibujarSuelo(int col, int fila);
    void crearBuffersModelo(Model& modelo, GLuint& VAO);
    void generarMonedes();
    virtual void keyPressEvent(QKeyEvent *e);

  private:
    GLuint projLoc;
    GLuint viewLoc;
    GLuint modelLoc;
    Model morty;
    Model fantasma;
    Model moneda;
    Model torre;
    int lab[10][15] = {
        {1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 3, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1},
        {1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {4, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
    GLuint VAO_Morty, VAO_Fantasma, VAO_Moneda, VAO_Torre;
    int numMorty, numFantasma, numMoneda, numTorre;
    bool camaraActiva = false;
};
