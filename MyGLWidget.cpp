// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>
#include<utility>
#include <QRandomGenerator>
#include <QVector>

#define CHECK() printOglError(__FILE__, __LINE__, __FUNCTION__)
#define DEBUG(text) std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << ":"<<text<<std::endl;

MyGLWidget::~MyGLWidget() {}


void MyGLWidget::initializeGL ( ){
    initializeOpenGLFunctions();
    glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
    carregaShaders();
    glEnable (GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    morty.load("../../Models3D/Morty.obj");
    fantasma.load("../../Models3D/Fantasma.obj");
    moneda.load("../../Models3D/Coin.obj");
    torre.load("../../Models3D/tower.obj");
    crearBuffersModelo(morty, VAO_Morty);
    crearBuffersModelo(fantasma, VAO_Fantasma);
    crearBuffersModelo(moneda, VAO_Moneda);
    crearBuffersModelo(torre, VAO_Torre);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(lab[i][j] == 2){
                xMorty = i, xPredMorty = i;
                zMorty = j, zPredMorty = j-1;
            }
            else if(lab[i][j] == 3){
                xFantasma = i, xPredFantasma = i;
                zFantasma = j, zPredFantasma = j-1;
            }
        }
    }
    rotMorty = 0.0f, rotFantasma = 0.0f;
    creaBuffersCub();
    generarMonedes();
    escala = 1.0f;
    calcularCapsaContenidora();
    angle = angleIni;
    projectTransform();
    viewTransform();
    DEBUG("InitializeGL");
}

void MyGLWidget::paintGL ( ){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program->bind();
    glViewport(0,0, width(), height());
    viewTransform();
    projectTransform();
    renderScene();

    int xTamany = 300, yTamany = 200;
    glViewport(width()-xTamany-20, 20, xTamany, yTamany);
    viewTransformMiniMap();
    projectTransformMiniMap();
    renderScene();
}

void MyGLWidget::carregaShaders(){
    BL2GLWidget::carregaShaders();
    projLoc = glGetUniformLocation(program->programId(), "proj");
    viewLoc = glGetUniformLocation(program->programId(), "view");
    vertexLoc = glGetAttribLocation(program->programId(), "vertex");
    modelLoc = glGetUniformLocation(program->programId(), "model");
    normalLoc = glGetAttribLocation(program->programId(), "normal");
    matambLoc = glGetAttribLocation(program->programId(), "matamb");
    matdiffLoc = glGetAttribLocation(program->programId(), "matdiff");
    matspecLoc = glGetAttribLocation(program->programId(), "matspec");
    matshinLoc = glGetAttribLocation(program->programId(), "matshin");
}

void MyGLWidget::renderScene(){
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL Error: " << err << std::endl;
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(lab[i][j] == 1) dibujarPared(j, i);
            else dibujarSuelo(j, i);
            if(lab[i][j] == 4){
                modelTransformTorre(i, j);
                glBindVertexArray(VAO_Torre);
                glDrawArrays(GL_TRIANGLES, 0, numTorre);
            }
            else if(lab[i][j] == 5){
                modelTransformMoneda(i, j);
                glBindVertexArray(VAO_Moneda);
                glDrawArrays(GL_TRIANGLES, 0, numMoneda);
            }
        }
    }
    modelTransformMorty(xMorty, zMorty);
    glBindVertexArray(VAO_Morty);
    glDrawArrays(GL_TRIANGLES, 0, numMorty);
    modelTransformFantasma(xFantasma, zFantasma);
    glBindVertexArray(VAO_Fantasma);
    glDrawArrays(GL_TRIANGLES, 0, numFantasma);
    DEBUG("PaintGL");
}

void MyGLWidget::projectTransform () {
    glm::mat4 Proj;
    float aspect = width() / (float)height();
    float fovV;
    if (angle < 0.05f) angle = 0.05f;
    if (angle > M_PI_2) angle = M_PI_2-0.05f;
    zoomCalcul(angle);
    if (aspect >= 1.0f) fovV = 2.0f * angle;
    else fovV = 2.0f * glm::atan(glm::tan(angle) / aspect);
    if(!camaraActiva) Proj = glm::perspective(fovV, aspect, 0.1f, 100.0f);
    else Proj = glm::perspective(glm::radians(90.0f), aspect, 0.1f, 100.0f);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}


void MyGLWidget::viewTransform () {
    glm::mat4 View(1.0f);
    if(!camaraActiva){
        View = glm::translate(View, glm::vec3(0.0f, 0.0f, -d));
        View = glm::rotate(View, theta, glm::vec3(1.0f, 0.0f, 0.0f));
        View = glm::rotate(View, -psi, glm::vec3(0.0f, 1.0f, 0.0f));
        View = glm::translate(View, -centre);
    }
    else{
        if(rotMorty == 0) View = glm::lookAt(glm::vec3(float(xMorty)+0.5f, 0.75f, -float(zMorty)), glm::vec3(float(xMorty)+0.5f, 0.75f, -float(zMorty)+1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        else if (rotMorty == 90) View = glm::lookAt(glm::vec3(float(xMorty)+0.5f, 0.75f, -float(zMorty)), glm::vec3(float(xMorty)+1.5f, 0.75f, -float(zMorty)), glm::vec3(0.0f, 1.0f, 0.0f));
        else if (rotMorty == 180) View = glm::lookAt(glm::vec3(float(xMorty)+0.5f, 0.75f, -float(zMorty)), glm::vec3(float(xMorty)+0.5f, 0.75f, -float(zMorty)-1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        else View = glm::lookAt(glm::vec3(float(xMorty)+0.5f, 0.75f, -float(zMorty)), glm::vec3(float(xMorty)-0.5f, 0.75f, -float(zMorty)), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::resizeGL(int w, int h){
}

void MyGLWidget::viewTransformMiniMap(){
    glm::mat4 View = glm::lookAt(glm::vec3 (centre.x, centre.y +50.0f, centre.z), centre, glm::vec3(-1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransformMiniMap(){
    float halfX = glm::distance(pMax.x, pMin.x) / 2.0f;
    float halfZ = glm::distance(pMax.z, pMin.z) / 2.0f;

    float vpAspect = float(M+1) / float(N+1);
    if (vpAspect > halfX / halfZ)
        halfX = halfZ * vpAspect;
    else
        halfZ = halfX / vpAspect;

    glm::mat4 Proj = glm::ortho(-halfX, halfX, -halfZ, halfZ, -100.0f, 100.0f);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::startGame(){
    start = true;
    update();
}

void MyGLWidget::reiniciar(){
    reinici();
    startGame();
}

void MyGLWidget::psiObtingut(float psiNou){
    psi = (psiNou/1000.0f)*(M_PI-0.01f);
    update();
}

void MyGLWidget::psiCalcul(float psiNou){
    emit psiEnviat((psiNou/(M_PI-0.01f))*1000.0f);
}

void MyGLWidget::thetaObtingut(float thetaNou){
    theta = (thetaNou/1000.0f)*(M_PI_2-0.01f);
    update();
}

void MyGLWidget::thetaCalcul(float thetaNou){
    emit thetaEnviat((thetaNou/(M_PI_2-0.01f))*1000.0f);
}

void MyGLWidget::zoomObtingut(float zoomNou){
    angle = 0.05+((1000.0f-zoomNou)/1000.0f)*(M_PI_2-0.1f);
    update();
}

void MyGLWidget::zoomCalcul(float zoomNou){
    float t = (zoomNou - 0.05f) / (M_PI_2 - 0.1f);
    float tInvertit = 1.0f - t;
    emit zoomEnviat(tInvertit * 1000.0f);
}

void MyGLWidget::camaraGen(){
    camaraActiva = false;
    update();
}

void MyGLWidget::primeraPers(){
    camaraActiva = true;
    update();
}

void MyGLWidget::rotMonedes(){
    timerActiu = true;
    timer->start(16);
    update();
}

void MyGLWidget::estMonedes(){
    timerActiu = false;
    timer->stop();
    update();
}

void MyGLWidget::reinici(){
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(lab[i][j] == 2){
                xAntMorty = i, xMorty = i, xPredMorty = i;
                zAntMorty = j+1, zMorty = j, zPredMorty = j-1;
            }
            else if(lab[i][j] == 3){
                xAntFantasma = i, xFantasma = i, xPredFantasma = i;
                zAntFantasma = j+1, zFantasma = j, zPredFantasma = j-1;
            }
        }
    }
    rotMorty = 0.0f, rotFantasma = 0.0f;
    generarMonedes();
    monedesRecollides = 0;
    emit comptadorMonedes(monedesRecollides, monedesTotals);
    update();
}

void MyGLWidget::calcularCapsaContenidora(){
    glm::vec3 tTorreOriginal = tamanyTorre();
    float factorEscala = 6.0f / 172.0f;
    glm::vec3 tTorre = tTorreOriginal * factorEscala;
    pMin = glm::vec3(std::numeric_limits<float>::max());
    pMax = glm::vec3(-std::numeric_limits<float>::max());
    bool algunaTorre = false;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(lab[i][j] == 4) {
                algunaTorre = true;
                float posX = float(i);
                float posZ = -float(j);
                posX += 2.0f * factorEscala;
                posZ += 2.0f * factorEscala;
                if (i == 0)      posX -= 2.0f;
                else if (i == 9) posX += 2.0f;
                else if (j == 0) posZ += 2.0f;
                else posZ -= 2.0f;
                float minX_celda = posX;
                float maxX_celda = posX + tTorre.x;
                float minY_celda = 0.0f;
                float maxY_celda = tTorre.y;
                float minZ_celda = posZ - tTorre.z;
                float maxZ_celda = posZ + tTorre.z;
                pMin.x = std::min(pMin.x, minX_celda);
                pMax.x = std::max(pMax.x, maxX_celda);
                pMin.y = std::min(pMin.y, minY_celda);
                pMax.y = std::max(pMax.y, maxY_celda);
                pMin.z = std::min(pMin.z, minZ_celda);
                pMax.z = std::max(pMax.z, maxZ_celda);
            }
        }
    }

    if (!algunaTorre) {
        pMin = glm::vec3(0.0f, 0.0f, -float(M));
        pMax = glm::vec3(float(N), 6.0f, 0.0f);
    }
    centre = (pMin + pMax) / 2.0f;
    radi = glm::distance(pMin, centre);
    float distanciaCamara = glm::distance(centre, ubiCamara);
    if (distanciaCamara > radi) {
        angleIni = glm::asin(radi / distanciaCamara);
    } else {
        angleIni = glm::radians(60.0f);
    }
}

glm::vec3 MyGLWidget::tamanyTorre(){
    if (torre.vertices().empty()) return glm::vec3(0.0f);

    float xmin = torre.vertices()[0], xmax = torre.vertices()[0];
    float ymin = torre.vertices()[1], ymax = torre.vertices()[1];
    float zmin = torre.vertices()[2], zmax = torre.vertices()[2];

    for(unsigned int i = 0; i < torre.vertices().size(); i += 3){
        if(torre.vertices()[i]   < xmin) xmin = torre.vertices()[i];
        if(torre.vertices()[i]   > xmax) xmax = torre.vertices()[i];
        if(torre.vertices()[i+1] < ymin) ymin = torre.vertices()[i+1];
        if(torre.vertices()[i+1] > ymax) ymax = torre.vertices()[i+1];
        if(torre.vertices()[i+2] < zmin) zmin = torre.vertices()[i+2];
        if(torre.vertices()[i+2] > zmax) zmax = torre.vertices()[i+2];
    }
    return glm::vec3(xmax-xmin, ymax-ymin, zmax-zmin);
}

void MyGLWidget::keyPressEvent(QKeyEvent *e){
    makeCurrent();
    switch(e->key()){
    case Qt::Key_C:
        camaraActiva = !camaraActiva;
        emit alternarCamara(camaraActiva);
    break;
    case Qt::Key_Up:
        movimentMorty("Up");
    break;
    case Qt::Key_Right:
        movimentMorty("Right");
    break;
    case Qt::Key_Left:
        movimentMorty("Left");
    break;
    case Qt::Key_Minus:
        angle += 0.1f;
    break;
    case Qt::Key_Plus:
        angle -= 0.1f;
    break;
    }
    update();
}

void MyGLWidget::mousePressEvent(QMouseEvent *event){
    xAnt = event->x();
    yAnt = event->y();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event){
    int deltaX = event->x() - xAnt;
    int deltaY = event->y() - yAnt;

    xAnt = event->x();
    yAnt = event->y();

    if (event->buttons() & Qt::LeftButton){
        psi += deltaX * factorGiro;
        theta -= deltaY * factorGiro;

        psiCalcul(psi);
        thetaCalcul(theta);

        if (psi > M_PI - 0.01f)  psi = M_PI - 0.01f;
        if (psi < -M_PI + 0.01f) psi = -M_PI + 0.01f;

        if (theta > M_PI_2 - 0.01f)  theta = M_PI_2 - 0.01f;
        if (theta < -M_PI_2 + 0.01f) theta = -M_PI_2 + 0.01f;
        update();
    }
    if (event->buttons() & Qt::RightButton){
        angle += deltaY * factorZoom;
        update();
    }
}

glm::vec3 MyGLWidget::puntBaseModel(Model& modelo){
    float xmin = modelo.vertices()[0];
    float xmax = modelo.vertices()[0];
    float ymin = modelo.vertices()[1];
    float zmin = modelo.vertices()[2];
    float zmax = modelo.vertices()[2];
    for(unsigned int i = 0; i<modelo.vertices().size(); i+=3){
        if(modelo.vertices()[i] < xmin) xmin = modelo.vertices()[i];
        if(modelo.vertices()[i] > xmax) xmax = modelo.vertices()[i];
        if(modelo.vertices()[i+1] < ymin) ymin = modelo.vertices()[i+1];
        if(modelo.vertices()[i+2] < zmin) zmin = modelo.vertices()[i+2];
        if(modelo.vertices()[i+2] > zmax) zmax = modelo.vertices()[i+2];
    }
    return glm::vec3((xmax+xmin)/2.0f, ymin, (zmax+zmin)/2.0f);
}

void MyGLWidget::modelTransformMorty(int fil, int col){
    float altOrig = 312.3;
    float altObj = 1.5;
    glm::vec3 puntBase = puntBaseModel(morty);
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(float(fil)+0.5f, 0.1f, -float(col)));
    TG = glm::rotate(TG, glm::radians(rotMorty), glm::vec3(0.0f, 1.0f, 0.0f));
    TG = glm::scale(TG, glm::vec3(altObj/altOrig, altObj/altOrig, altObj/altOrig));
    TG = glm::translate(TG, glm::vec3(-puntBase[0], -puntBase[1], -puntBase[2]));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::movimentMorty(std::string dir){
    if(start){
        if(dir == "Up"){
            if(lab[xPredMorty][zPredMorty] != 1){
                if(lab[xPredMorty][zPredMorty] != 4){
                    xAntMorty = xMorty, zAntMorty = zMorty;
                    xMorty = xPredMorty, zMorty = zPredMorty;
                    movimentFantasma();
                }
                else if(lab[xPredMorty][zPredMorty] == 4 and monedesRecollides == monedesTotals){
                    xMorty = xPredMorty, zMorty = zPredMorty;
                    movimentFantasma();
                    emit guanyat();
                    start = false;
                }
            }
            if((xMorty == xFantasma and zMorty == zFantasma) or (xAntMorty == xFantasma and zAntMorty == zFantasma and xMorty == xAntFantasma and zMorty == zAntFantasma)) emit perdut();
        }
        else if(dir == "Right") rotMorty -= 90.0f;
        else rotMorty += 90.0f;

        if(rotMorty < 0) rotMorty += 360;
        else if (rotMorty >= 360) rotMorty -= 360;

        if(rotMorty == 0.0f){
            xPredMorty = xMorty;
            zPredMorty = zMorty-1;
        }
        else if(rotMorty == 90.0f){
            xPredMorty = xMorty+1;
            zPredMorty = zMorty;
        }
        else if(rotMorty == 180.0f){
            xPredMorty = xMorty;
            zPredMorty = zMorty+1;
        }
        else {
            xPredMorty = xMorty-1;
            zPredMorty = zMorty;
        }

        if(lab[xMorty][zMorty] == 5){
            lab[xMorty][zMorty] = 0;
            ++monedesRecollides;
            emit comptadorMonedes(monedesRecollides, monedesTotals);
            update();
        }
    }
}

void MyGLWidget::modelTransformFantasma(int fil, int col){
    float altOrig = 0.25;
    float altObj = 0.65;
    glm::vec3 puntBase = puntBaseModel(fantasma);
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(float(fil)+0.5f, 0.1f, -float(col)));
    TG = glm::rotate(TG, glm::radians(rotFantasma), glm::vec3(0.0f, 1.0f, 0.0f));
    TG = glm::scale(TG, glm::vec3(altObj/altOrig, altObj/altOrig, altObj/altOrig));
    TG = glm::translate(TG, glm::vec3(-puntBase[0], -puntBase[1], -puntBase[2]));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &TG[0][0]);
}


void MyGLWidget::movimentFantasma(){
    if(lab[xPredFantasma][zPredFantasma] != 1){
        xAntFantasma= xFantasma, zAntFantasma = zFantasma;
        xFantasma = xPredFantasma, zFantasma = zPredFantasma;
    }
    else{
        QVector<float> opcions;
        if(zFantasma > 0 and lab[xFantasma][zFantasma-1] != 1) opcions.append(0.0f);
        if(zFantasma < M and lab[xFantasma][zFantasma+1] != 1) opcions.append(180.0f);
        if(xFantasma > 0 and lab[xFantasma-1][zFantasma] != 1) opcions.append(270.0f);
        if(zFantasma < N and lab[xFantasma+1][zFantasma] != 1) opcions.append(90.0f);
        if (!opcions.isEmpty()) {
            int index = QRandomGenerator::global()->bounded(opcions.size());
            rotFantasma = opcions[index];
        }
    }
    if(rotFantasma == 0.0f){
        xPredFantasma = xFantasma;
        zPredFantasma = zFantasma-1;
    }
    else if(rotFantasma == 90.0f){
        xPredFantasma = xFantasma+1;
        zPredFantasma = zFantasma;
    }
    else if(rotFantasma == 180.0f){
        xPredFantasma = xFantasma;
        zPredFantasma = zFantasma+1;
    }
    else {
        xPredFantasma = xFantasma-1;
        zPredFantasma = zFantasma;
    }
}

void MyGLWidget::generarMonedes(){
    int monedes = 0;
    while(monedes < 10){
        int fil = rand()%10;
        int col = rand()%15;
        if(lab[fil][col] == 0){
            lab[fil][col] = 5;
            ++monedes;
        }
    }
}

void MyGLWidget::modelTransformMoneda(int fil, int col){
    float altOrig = 11;
    float altObj = 0.5;
    glm::vec3 puntBase = puntBaseModel(moneda);
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(float(fil), 0.1f, -float(col)));
    TG = glm::rotate(TG, glm::radians(rotMoneda), glm::vec3(0.0f, 1.0f, 0.0f));
    TG = glm::scale(TG, glm::vec3(altObj/altOrig, altObj/altOrig, altObj/altOrig));
    TG = glm::translate(TG, glm::vec3(-puntBase[0], -puntBase[1], -puntBase[2]));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::rotateCoins() {
    makeCurrent();
    rotMoneda += 2.0f;
    if (rotMoneda >= 360.0f) rotMoneda -= 360.0f;
    update();
}


void MyGLWidget::modelTransformTorre(int fil, int col){
    float altOrig = 172;
    float altObj = 6;
    glm::mat4 TG(1.0f);
    if(fil == 0) TG = glm::translate(TG, glm::vec3(float(fil)-2.0f, 0., -float(col)));
    else if(fil == 9){
        TG = glm::translate(TG, glm::vec3(float(fil)+2.0f, 0., -float(col)));
        TG = glm::rotate(TG, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    else if(col == 0){
        TG = glm::translate(TG, glm::vec3(float(fil), 0., -float(col)+2.0f));
        TG = glm::rotate(TG, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    else{
        TG = glm::translate(TG, glm::vec3(float(fil), 0., -float(col)-2.0f));
        TG = glm::rotate(TG, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    TG = glm::scale(TG, glm::vec3(altObj/altOrig, altObj/altOrig, altObj/altOrig));
    TG = glm::translate(TG, glm::vec3(2, 0, 2));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::dibujarPared(int col, int fila){
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(float(fila), 0.0f, -float(col)));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &TG[0][0]);
    glBindVertexArray(VAO_Cub);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void MyGLWidget::dibujarSuelo(int col, int fila) {
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(float(fila), 0.0f, -float(col)));
    TG = glm::scale(TG, glm::vec3(1.0f, 0.1f, 1.0f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &TG[0][0]);

    glBindVertexArray(VAO_Cub);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void MyGLWidget::crearBuffersModelo(Model& modelo, GLuint& VAO){
    int numVertices = modelo.faces().size() * 3;
    if(&modelo == &morty) numMorty = numVertices;
    else if(&modelo == &fantasma) numFantasma = numVertices;
    else if(&modelo == &moneda) numMoneda = numVertices;
    else if(&modelo == &torre) numTorre = numVertices;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GLuint VBO_Modelo[6];
    glGenBuffers(6, VBO_Modelo);

    // VBO[0]: Posiciones de vértices
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Modelo[0]);
    // Tamaño: numVertices * 3 floats (x,y,z para cada vértice)
    glBufferData(GL_ARRAY_BUFFER, numVertices * 3 * sizeof(float),
                 modelo.VBO_vertices(), GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Modelo[1]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * 3 * sizeof(float), modelo.VBO_normals(), GL_STATIC_DRAW);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normalLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Modelo[2]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * 3 * sizeof(float), modelo.VBO_matamb(), GL_STATIC_DRAW);
    glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(matambLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Modelo[3]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * 3 * sizeof(float), modelo.VBO_matdiff(), GL_STATIC_DRAW);
    glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(matdiffLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Modelo[4]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * 3 * sizeof(float),
                 modelo.VBO_matspec(), GL_STATIC_DRAW);
    glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(matspecLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Modelo[5]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(float), modelo.VBO_matshin(), GL_STATIC_DRAW);
    glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(matshinLoc);

    glBindVertexArray(0);
}

void MyGLWidget::creaBuffersCub ()
{
    // Dades del cub
    // Vèrtexs del cub
    glm::vec3 vertexs[8] = {
        /* 0*/ glm::vec3( 0.0, 0.0, 0.0),  /* 1*/ glm::vec3( 1.0, 0.0, 0.0),
        /* 2*/ glm::vec3( 0.0, 1.0, 0.0),  /* 3*/ glm::vec3( 1.0, 1.0, 0.0),
        /* 4*/ glm::vec3( 0.0, 0.0, 1.0),  /* 5*/ glm::vec3( 1.0, 0.0, 1.0),
        /* 6*/ glm::vec3( 0.0, 1.0, 1.0),  /* 7*/ glm::vec3( 1.0, 1.0, 1.0)
    };

    // VBO amb la posició dels vèrtexs
    glm::vec3 poscub[36] = {  // 12 triangles
        vertexs[0], vertexs[2], vertexs[1],
        vertexs[1], vertexs[2], vertexs[3],
        vertexs[5], vertexs[1], vertexs[7],
        vertexs[1], vertexs[3], vertexs[7],
        vertexs[2], vertexs[6], vertexs[3],
        vertexs[3], vertexs[6], vertexs[7],
        vertexs[0], vertexs[4], vertexs[6],
        vertexs[0], vertexs[6], vertexs[2],
        vertexs[0], vertexs[1], vertexs[4],
        vertexs[1], vertexs[5], vertexs[4],
        vertexs[4], vertexs[5], vertexs[6],
        vertexs[5], vertexs[7], vertexs[6]
    };

    // VBO amb la normal de cada vèrtex
    glm::vec3 normals[6] = {
        /* 0*/ glm::vec3( 1.0, 0.0,  0.0),  /* 1*/ glm::vec3( -1.0, 0.0, 0.0),
        /* 2*/ glm::vec3( 0.0, 1.0,  0.0),  /* 3*/ glm::vec3( 0.0, -1.0, 0.0),
        /* 4*/ glm::vec3( 0.0, 0.0,  1.0),  /* 5*/ glm::vec3( 0.0, 0.0, -1.0)
    };
    glm::vec3 normcub[36] = {
        normals[5], normals[5], normals[5],
        normals[5], normals[5], normals[5],
        normals[0], normals[0], normals[0],
        normals[0], normals[0], normals[0],
        normals[2], normals[2], normals[2],
        normals[2], normals[2], normals[2],
        normals[1], normals[1], normals[1],
        normals[1], normals[1], normals[1],
        normals[3], normals[3], normals[3],
        normals[3], normals[3], normals[3],
        normals[4], normals[4], normals[4],
        normals[4], normals[4], normals[4]
    };

    // inicialitzem el material del cub
    glm::vec3 amb, diff, spec;
    float shin;
    amb = glm::vec3(0.1,0.0,0.0);
    diff = glm::vec3(0.6,0.5,0.5);
    spec = glm::vec3(0.6,0.6,0.6);
    shin = 100;

    // Fem que aquest material afecti a tots els vèrtexs per igual
    glm::vec3 matambcub[36] = {
        amb, amb, amb, amb, amb, amb,
        amb, amb, amb, amb, amb, amb,
        amb, amb, amb, amb, amb, amb,
        amb, amb, amb, amb, amb, amb,
        amb, amb, amb, amb, amb, amb,
        amb, amb, amb, amb, amb, amb
    };
    float a=0.5;
    glm::vec3 diff1 = glm::vec3(0.6,0.0,0.0);
    glm::vec3 matdiffcub[36] = {
        diff, diff, diff1, diff, diff, diff,
        diff, diff, diff1, diff, diff, diff,
        diff*a, diff*a, diff1*a, diff*a, diff*a, diff1*a,
        diff, diff, diff1, diff, diff, diff,
        diff, diff, diff1, diff, diff, diff,
        diff, diff, diff1, diff, diff, diff
    };
    glm::vec3 matspeccub[36] = {
        spec, spec, spec, spec, spec, spec,
        spec, spec, spec, spec, spec, spec,
        spec, spec, spec, spec, spec, spec,
        spec, spec, spec, spec, spec, spec,
        spec, spec, spec, spec, spec, spec,
        spec, spec, spec, spec, spec, spec
    };
    float matshincub[36] = {
        shin, shin, shin, shin, shin, shin,
        shin, shin, shin, shin, shin, shin,
        shin, shin, shin, shin, shin, shin,
        shin, shin, shin, shin, shin, shin,
        shin, shin, shin, shin, shin, shin,
        shin, shin, shin, shin, shin, shin
    };

    // Creació del Vertex Array Object del cub
    glGenVertexArrays(1, &VAO_Cub);
    glBindVertexArray(VAO_Cub);

    GLuint VBO_Cub[6];
    glGenBuffers(6, VBO_Cub);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cub[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(poscub), poscub, GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cub[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normcub), normcub, GL_STATIC_DRAW);

    // Activem l'atribut normalLoc
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normalLoc);

    // En lloc del color, ara passem tots els paràmetres dels materials
    // Buffer de component ambient
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cub[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(matambcub), matambcub, GL_STATIC_DRAW);

    glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(matambLoc);

    // Buffer de component difusa
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cub[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(matdiffcub), matdiffcub, GL_STATIC_DRAW);

    glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(matdiffLoc);

    // Buffer de component especular
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cub[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(matspeccub), matspeccub, GL_STATIC_DRAW);

    glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(matspecLoc);
    // Buffer de component shininness
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cub[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(matshincub), matshincub, GL_STATIC_DRAW);

    glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(matshinLoc);

    glBindVertexArray(0);
}
