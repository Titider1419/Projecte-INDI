// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>
#include<utility>

#define CHECK() printOglError(__FILE__, __LINE__, __FUNCTION__)
#define DEBUG(text) std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << ":"<<text<<std::endl;


MyGLWidget::~MyGLWidget() {
}


void MyGLWidget::initializeGL ( ){
    initializeOpenGLFunctions();
    glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
    carregaShaders();
    glEnable (GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    morty.load("/home/andres/UNI/Q4/INDI/labs/projecte/models/Morty.obj");
    fantasma.load("/home/andres/UNI/Q4/INDI/labs/projecte/models/Fantasma.obj");
    moneda.load("/home/andres/UNI/Q4/INDI/labs/projecte/models/Coin.obj");
    torre.load("/home/andres/UNI/Q4/INDI/labs/projecte/models/tower.obj");
    crearBuffersModelo(morty, VAO_Morty);
    crearBuffersModelo(fantasma, VAO_Fantasma);
    crearBuffersModelo(moneda, VAO_Moneda);
    crearBuffersModelo(torre, VAO_Torre);
    creaBuffersCub();
    generarMonedes();
    escala = 1.0f;
    projectTransform();
    viewTransform();
    DEBUG("InitializeGL");
}

void MyGLWidget::paintGL ( ){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    viewTransform();
    projectTransform();
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL Error: " << err << std::endl;
    }
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 15; j++) {
            if(lab[i][j] == 1) dibujarPared(j, i);
            else dibujarSuelo(j, i);
            if(lab[i][j] == 2){
                modelTransformMorty(i, j);
                glBindVertexArray(VAO_Morty);
                glDrawArrays(GL_TRIANGLES, 0, numMorty);
            }
            else if(lab[i][j] == 3){
                modelTransformFantasma(i, j);
                glBindVertexArray(VAO_Fantasma);
                glDrawArrays(GL_TRIANGLES, 0, numFantasma);
            }
            else if(lab[i][j] == 4){
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

    DEBUG("PaintGL");
}

void MyGLWidget::carregaShaders(){
    BL2GLWidget::carregaShaders();
    projLoc = glGetUniformLocation(program->programId(), "proj");
    viewLoc = glGetUniformLocation(program->programId(), "view");
    vertexLoc = glGetAttribLocation(program->programId(), "vertex");
    normalLoc = glGetAttribLocation(program->programId(), "normal");
    matambLoc = glGetAttribLocation(program->programId(), "matamb");
    matdiffLoc = glGetAttribLocation(program->programId(), "matdiff");
    matspecLoc = glGetAttribLocation(program->programId(), "matspec");
    matshinLoc = glGetAttribLocation(program->programId(), "matshin");
}
void MyGLWidget::projectTransform () {
    glm::mat4 Proj;
    float aspect = width() / (float)height();
    if(!camaraActiva) Proj = glm::perspective(glm::radians(90.0f), aspect, 0.1f, 100.0f);
    else Proj = glm::perspective(glm::radians(90.0f), aspect, 0.1f, 100.0f);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}


void MyGLWidget::viewTransform () {
    glm::mat4 View;
    if(!camaraActiva) View = glm::lookAt (glm::vec3(7.5f, 12.0f, 8.0f), glm::vec3(4.5f, 0.0f, -7.0f),  glm::vec3(0.0f, 1.0f, 0.0f));
    else View = glm::lookAt(glm::vec3(8.5f, 0.75f, -11.5f), glm::vec3(8.5f, 0.75f, -11.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::resizeGL(int w, int h){
    projectTransform();
}

void MyGLWidget::keyPressEvent(QKeyEvent *e){
    makeCurrent();
    switch(e->key()){
    case Qt::Key_C:
        camaraActiva = !camaraActiva;
    break;
    }
    update();
}

void MyGLWidget::modelTransformMorty(int fil, int col){
    float altOrig = 312.3;
    float altObj = 1.5;
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(float(fil)+0.5f, 0.1f, -float(col)));
    TG = glm::scale(TG, glm::vec3(altObj/altOrig, altObj/altOrig, altObj/altOrig));
    TG = glm::translate(TG, glm::vec3(-100.0f, 213.0f, 6.0f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &TG[0][0]);
}

glm::vec3 MyGLWidget::puntMinMorty(){
    float xmin = morty.vertices()[0];
    float ymin = morty.vertices()[1];
    float zmin = morty.vertices()[2];
    for(unsigned int i = 0; i<morty.vertices().size(); i+=3){
        if(morty.vertices()[i] < xmin) xmin = morty.vertices()[i];
        if(morty.vertices()[i+1] < ymin) ymin = morty.vertices()[i+1];
        if(morty.vertices()[i+2] < zmin) zmin = morty.vertices()[i+2];
    }
    return glm::vec3(xmin, ymin, zmin);
}

void MyGLWidget::modelTransformFantasma(int fil, int col){
    float altOrig = 0.25;
    float altObj = 0.65;
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(float(fil)+0.5f, 0.1f, -float(col)));
    TG = glm::scale(TG, glm::vec3(altObj/altOrig, altObj/altOrig, altObj/altOrig));
    TG = glm::translate(TG, glm::vec3(-0, -0, -0));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &TG[0][0]);
}

glm::vec3 MyGLWidget::puntMinFantasma(){
    float xmin = fantasma.vertices()[0];
    float ymin = fantasma.vertices()[1];
    float zmin = fantasma.vertices()[2];
    for(unsigned int i = 0; i<fantasma.vertices().size(); i+=3){
        if(fantasma.vertices()[i] < xmin) xmin = fantasma.vertices()[i];
        if(fantasma.vertices()[i+1] < ymin) ymin = fantasma.vertices()[i+1];
        if(fantasma.vertices()[i+2] < zmin) zmin = fantasma.vertices()[i+2];
    }
    return glm::vec3(xmin, ymin, zmin);
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
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(float(fil), 0.1f, -float(col)));
    TG = glm::scale(TG, glm::vec3(altObj/altOrig, altObj/altOrig, altObj/altOrig));
    TG = glm::translate(TG, glm::vec3(0, 5.5, 0.25));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &TG[0][0]);
}

glm::vec3 MyGLWidget::puntMinMoneda(){
    float xmin = moneda.vertices()[0];
    float ymin = moneda.vertices()[1];
    float zmin = moneda.vertices()[2];
    for(unsigned int i = 0; i<moneda.vertices().size(); i+=3){
        if(moneda.vertices()[i] < xmin) xmin = moneda.vertices()[i];
        if(moneda.vertices()[i+1] < ymin) ymin = moneda.vertices()[i+1];
        if(moneda.vertices()[i+2] < zmin) zmin = moneda.vertices()[i+2];
    }
    return glm::vec3(xmin, ymin, zmin);
}

void MyGLWidget::modelTransformTorre(int fil, int col){
    float altOrig = 172;
    float altObj = 6;
    glm::mat4 TG(1.0f);
    if(fil == 0) TG = glm::translate(TG, glm::vec3(float(fil)-1.0f, 0., -float(col)));
    else if(fil == 9){
        TG = glm::translate(TG, glm::vec3(float(fil)+1.0f, 0., -float(col)));
        TG = glm::rotate(TG, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    else if(col == 0){
        TG = glm::translate(TG, glm::vec3(float(fil), 0., -float(col)+1.0f));
        TG = glm::rotate(TG, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    else{
        TG = glm::translate(TG, glm::vec3(float(fil), 0., -float(col)-1.0f));
        TG = glm::rotate(TG, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    TG = glm::scale(TG, glm::vec3(altObj/altOrig, altObj/altOrig, altObj/altOrig));
    TG = glm::translate(TG, glm::vec3(2, 0, 2));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &TG[0][0]);
}

glm::vec3 MyGLWidget::puntMinTorre(){
    float xmin = torre.vertices()[0];
    float ymin = torre.vertices()[1];
    float zmin = torre.vertices()[2];
    for(unsigned int i = 0; i<torre.vertices().size(); i+=3){
        if(torre.vertices()[i] < xmin) xmin = torre.vertices()[i];
        if(torre.vertices()[i+1] < ymin) ymin = torre.vertices()[i+1];
        if(torre.vertices()[i+2] < zmin) zmin = torre.vertices()[i+2];
    }
    return glm::vec3(xmin, ymin, zmin);
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
