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

    BL2GLWidget::initializeGL();
    DEBUG("InitializeGL");
    projectTransform();
    viewTransform();
}

void MyGLWidget::paintGL ( ){
    BL2GLWidget::paintGL();
    DEBUG("PaintGL");
}

void MyGLWidget::carregaShaders(){
    BL2GLWidget::carregaShaders();
    projLoc = glGetUniformLocation(program->programId(), "proj");
    viewLoc = glGetUniformLocation(program->programId(), "view");
}

void MyGLWidget::projectTransform () {
    glm::mat4 Proj = glm::perspective (float(M_PI)/2.0f, 1.0f, 0.4f, 3.0f);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}


void MyGLWidget::viewTransform () {
    glm::mat4 View = glm::lookAt (glm::vec3(0,0,1), glm::vec3(0,0,0),  glm::vec3(0,1,0));
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}
