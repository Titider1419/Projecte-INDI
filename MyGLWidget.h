// MyGLWidget.h
#include "BL2GLWidget.h"
#include "Models3D/model.h"
#include <QKeyEvent>
#include <QTimer>

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
  MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent){
      timer = new QTimer(this);
      connect(timer, &QTimer::timeout, this, &MyGLWidget::rotateCoins);
      timer->start(16);
      timerActiu = true;
  }
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
    glm::vec3 puntBaseModel(Model& modelo);
    void dibujarPared(int col, int fila);
    void dibujarSuelo(int col, int fila);
    void crearBuffersModelo(Model& modelo, GLuint& VAO);
    void generarMonedes();
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    glm::vec3 tamanyTorre();
    void calcularCapsaContenidora();
    void movimentMorty(std::string dir);
    void movimentFantasma();
    void renderScene();
    void viewTransformMiniMap();
    void projectTransformMiniMap();
    void reinici();
    void psiCalcul(float psiNou);
    void thetaCalcul(float thetaNou);
    void zoomCalcul(float zoomNou);

  public slots:
    void rotateCoins();
    void startGame();
    void reiniciar();
    void psiObtingut(float psiNou);
    void thetaObtingut(float thetaNou);
    void zoomObtingut(float zoomNou);
    void camaraGen();
    void primeraPers();
    void rotMonedes();
    void estMonedes();

  signals:
    void comptadorMonedes(int actuals, int totals);
    void guanyat();
    void perdut();
    void psiEnviat(float psiNou);
    void thetaEnviat(float thetaNou);
    void zoomEnviat(float zoomNou);
    void alternarCamara(bool primeraPers);
    void alternarRotacioMoneda(bool timerActiu);

  private:
    static const int N = 10;
    static const int M = 15;
    GLuint projLoc;
    GLuint viewLoc;
    GLuint modelLoc;
    Model morty;
    Model fantasma;
    Model moneda;
    Model torre;
    int lab[N][M] = {
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
    glm::vec3 ubiCamara = glm::vec3(7.5f, 12.0f, 8.0f);
    glm::vec3 pMax;
    glm::vec3 pMin;
    glm::vec3 centre;
    float radi;
    float angleIni;
    float angle;
    int xAntMorty, zAntMorty, xMorty, zMorty, xPredMorty, zPredMorty;
    float rotMorty;
    int xAntFantasma, zAntFantasma, xFantasma, zFantasma, xPredFantasma, zPredFantasma;
    float rotFantasma;
    int monedesRecollides = 0;
    int monedesTotals = 10;
    float rotMoneda = 0.0f;
    float d = 15, theta, psi;
    float xAnt = 0.0f, yAnt = 0.0f;
    float factorGiro = 0.005f, factorZoom = 0.1f;
    bool start = false;
    QTimer *timer;
    bool timerActiu;
};
